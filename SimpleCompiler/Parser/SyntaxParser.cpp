#include "SyntaxParser.h"
#include "Types/ParserElement.h"
#include "../Utilities/RefObject.h"
#include "Types/Variable.h"
#include "Types/LocalVariable.h"
#include "Types/Arithmetic.h"

SyntaxParser::SyntaxParser(const char* Enviroment)
{
	DeflatedEnv = Deflater.Deflate(Enviroment);
}

EnviromentMap SyntaxParser::ParseEnviroment()
{
	EnviromentMap Enviroment = EnviromentMap();
	List<char> DeflateCopy = DeflatedEnv;

	for (char* Token = strtok(DeflateCopy, ";"); Token; Token = strtok(0, ";"))
	{
		RefObject<ParserElement> Object;

		switch (ResolveExpressionType(Token))
		{
		case ParserExpression_TypeDefinition:
		{
			RefObject<LocalVariable> Variable = RefObject<LocalVariable>(LocalVariable(Token));
			
			Enviroment.AddVariable(Variable.Cast<::Variable>());

			Variable->Parse(Enviroment, Token);
		} break;
		case ParserExpression_ArithmeticOperation:
		{
			RefObject<Arithmetic> Expression = RefObject<Arithmetic>(Arithmetic());

			Enviroment.AddParsed(Expression.Cast<ParserElement>());

			Expression->Parse(Enviroment, Token);
		};
		};
	}

	return Enviroment;
}

ParserExpression SyntaxParser::ResolveExpressionType(const char* Expression)
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