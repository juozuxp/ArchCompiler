#pragma once
#include "ParserElement.h"

class Variable : public ParserElement
{
public:
	constexpr Variable()
	{
	}

	Variable(const char* Expression);

public:
	constexpr const char* GetVariableName()
	{
		return VariableName;
	}

public:
	void Parse(class EnviromentMap& Enviroment, const char* Expression);

public:
	virtual List<unsigned char> CompileAssign()
	{
		return List<unsigned char>();
	}

	virtual List<unsigned char> CompileRetrieve()
	{
		return List<unsigned char>();
	}

public:
	static bool IsVariable(const char* Expression);
	
protected:
	static List<char> ExtractName(const char* Expression);

protected:
	List<char> VariableName;
	unsigned long long VariableSize = 0;
};