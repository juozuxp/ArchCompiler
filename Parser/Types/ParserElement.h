#pragma once
#include "../../Utilities/List.h"

class ParserElement
{
public:
	constexpr ParserElement()
	{
	}

public:
	virtual unsigned long long GetStackSize()
	{
		return 0;
	}

	virtual List<unsigned char> Compile(class CompileMap& Enviroment)
	{
		return List<unsigned char>();
	}

	virtual void Parse(class EnviromentMap& Enviroment, const char* Expression)
	{
	}
};