#include "SyntaxParser.h"
#include "Types/ParserElement.h"
#include "../Utilities/RefObject.h"
#include "../Utilities/StrTok.h"
#include "Types/Variable.h"
#include "Types/LocalVariable.h"
#include "Types/Arithmetic.h"
#include "Types/Function.h"
#include "Types/FunctionCall.h"

SyntaxParser::SyntaxParser(const char* Enviroment)
{
	DeflatedEnv = Deflater.Deflate(Enviroment);
}

RefObject<FileEnviromentMap> SyntaxParser::ParseEnviroment()
{
	RefObject<FileEnviromentMap> Enviroment = RefObject<FileEnviromentMap>(FileEnviromentMap());
	for (const char* RunDeflate = DeflatedEnv; *RunDeflate;)
	{
		if (Function::IsFunctionDefinition(RunDeflate))
		{
			RefObject<Function> Function;
			unsigned long long SubLength;

			Function = RefObject<::Function>(::Function(RunDeflate));
			Enviroment->AddFunction(Function);

			RunDeflate += Function::GetDefinitionLength(RunDeflate);
			Function->BindEnviroment(ParseSubEnviroment(ExtractSubEnviroment(RunDeflate, &SubLength), Enviroment.Cast<::Enviroment>()));

			RunDeflate += SubLength;
		}
		else
			break;
	}

	return Enviroment;
}

RefObject<EnviromentMap> SyntaxParser::ParseSubEnviroment(const char* Expression, RefObject<Enviroment> Parent)
{
	RefObject<EnviromentMap> Enviroment = RefObject<EnviromentMap>(EnviromentMap(Parent.Cast<::Enviroment>()));

	for (char* Token : StrTok(Expression, ";"))
	{
		RefObject<ParserElement> Object;

		switch (ResolveExpressionType(Token))
		{
		case ParserExpression_TypeDefinition:
		{
			RefObject<LocalVariable> Variable = RefObject<LocalVariable>(LocalVariable(Token));
			
			Enviroment->AddVariable(Variable.Cast<::Variable>());

			Variable->Parse(*Enviroment, Token);
		} break;
		case ParserExpression_ArithmeticOperation:
		{
			RefObject<Arithmetic> Expression = RefObject<Arithmetic>(Arithmetic());

			Enviroment->AddParsed(Expression.Cast<ParserElement>());

			Expression->Parse(*Enviroment, Token);
		} break;
		case ParserExpression_FunctionCall:
		{
			RefObject<FunctionCall> Expression = RefObject<FunctionCall>(FunctionCall());

			Enviroment->AddParsed(Expression.Cast<ParserElement>());

			Expression->Parse(*Enviroment, Token);
		} break;
		};
	}

	return Enviroment;
}

SyntaxParser::ParserExpression SyntaxParser::ResolveExpressionType(const char* Expression)
{
	if (Variable::IsVariable(Expression))
		return ParserExpression_TypeDefinition;

	if (Arithmetic::IsArtimetic(Expression))
		return ParserExpression_ArithmeticOperation;

	if (FunctionCall::IsFunctionCall(Expression))
		return ParserExpression_FunctionCall;

	return ParserExpression_None;
}

List<char> SyntaxParser::DeflateEnviroment(const char* Enviroment)
{
	List<char> Deflated = List<char>(0);

	Deflated.Add(Enviroment, strlen(Enviroment) + 1);

	for (unsigned long long i = 0; i < Deflated.GetCount(); i++)
	{
		if (Deflated[i] == '\r' || Deflated[i] == '\n')
		{
			Deflated.RemoveIndex(i);
			i--;
			continue;
		}
	}

	return Deflated;
}

List<char> SyntaxParser::ExtractSubEnviroment(const char* Enviroment, unsigned long long* Length)
{
	List<char> Evaluated = List<char>(0);

	const char* RunEnviroment = Enviroment;
	while (*RunEnviroment)
	{
		if (*RunEnviroment != '\t')
			break;

		const char* Start = RunEnviroment + 1;

		unsigned long long Length = 0;
		for (RunEnviroment++; *RunEnviroment; RunEnviroment++, Length++)
		{
			if (*RunEnviroment != '\t')
				break;
		}

		for (; *RunEnviroment && *RunEnviroment != '\t'; RunEnviroment++, Length++)
		{
			if (*RunEnviroment == ';')
			{
				RunEnviroment++;
				Length++;
				break;
			}
		}

		Evaluated.Add(Start, Length);
	}

	if (Length)
		*Length = RunEnviroment - Enviroment;

	Evaluated.Add('\0');
	return Evaluated;
}