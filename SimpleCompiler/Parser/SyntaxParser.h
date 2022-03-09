#pragma once
#include "../Utilities/List.h"
#include "../Utilities/RefObject.h"
#include "Types/ParserElement.h"
#include "../Components/EnviromentMap.h"
#include "../Utilities/Deflatable.h"
#include "../Components/FileEnviromentMap.h"

class SyntaxParser
{
private:
	enum ParserExpression
	{
		ParserExpression_None,
		ParserExpression_TypeDefinition,
		ParserExpression_ArithmeticOperation,
		ParserExpression_FunctionCall
	};

public:
	constexpr SyntaxParser()
	{
	}

	SyntaxParser(const char* Enviroment);

public:
	RefObject<FileEnviromentMap> ParseEnviroment();

private:
	static ParserExpression ResolveExpressionType(const char* Expression);
	static RefObject<EnviromentMap> ParseSubEnviroment(const char* Expression, RefObject<Enviroment> Enviroment);

	static List<char> ExtractSubEnviroment(const char* Enviroment);
	static List<char> DeflateEnviroment(const char* Enviroment);

private:
	List<char> DeflatedEnv;

private:
	static constexpr Deflatable Deflater = Deflatable("\r\n");
};