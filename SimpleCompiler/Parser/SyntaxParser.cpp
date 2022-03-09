#include "SyntaxParser.h"
#include "Types/ParserElement.h"
#include "../Utilities/RefObject.h"
#include "Types/Variable.h"
#include "Types/LocalVariable.h"
#include "Types/Arithmetic.h"
#include "Types/Function.h"

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
			RunDeflate += Function::GetDefinitionLength(RunDeflate);
			Enviroment->AddEnviroment(ParseSubEnviroment(ExtractSubEnviroment(RunDeflate), Enviroment.Cast<::Enviroment>()));

			break;
		}
	}

	return Enviroment;
}

RefObject<EnviromentMap> SyntaxParser::ParseSubEnviroment(const char* Expression, RefObject<Enviroment> Parent)
{
	RefObject<EnviromentMap> Enviroment = RefObject<EnviromentMap>(EnviromentMap(Parent.Cast<::Enviroment>()));
	List<char> EnviromentCopy = List<char>(0);

	EnviromentCopy.Add(Expression, strlen(Expression) + 1);
	for (char* Token = strtok(EnviromentCopy, ";"); Token; Token = strtok(0, ";"))
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
		};
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

List<char> SyntaxParser::ExtractSubEnviroment(const char* Enviroment)
{
	List<char> Evaluated = List<char>(0);

	while (*Enviroment)
	{
		if (*Enviroment != '\t')
			break;

		const char* Start = Enviroment + 1;

		unsigned long long Length = 0;
		for (Enviroment++; *Enviroment; Enviroment++, Length++)
		{
			if (*Enviroment != '\t')
				break;
		}

		for (; *Enviroment && *Enviroment != '\t'; Enviroment++, Length++)
		{
			if (*Enviroment == ';')
			{
				Enviroment++;
				Length++;
				break;
			}
		}

		Evaluated.Add(Start, Length);
	}

	Evaluated.Add('\0');
	return Evaluated;
}