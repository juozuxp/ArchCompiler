#pragma once
#include "../Utilities/List.h"
#include "../Utilities/RefObject.h"
#include "Types/ParserElement.h"
#include "../Components/EnviromentMap.h"
#include "../Utilities/Deflatable.h"

enum ParserExpression
{
	ParserExpression_None,
	ParserExpression_TypeDefinition,
	ParserExpression_ArithmeticOperation,
	ParserExpression_FunctionCall
};

class SyntaxParser
{
public:
	SyntaxParser(const char* Enviroment);

public:
	EnviromentMap ParseEnviroment();

private:
	static ParserExpression ResolveExpressionType(const char* Expression);

	static List<char> DeflateEnviroment(const char* Enviroment);

private:
	List<char> DeflatedEnv;

private:
	static constexpr Deflatable Deflater = Deflatable("\r\n");
};