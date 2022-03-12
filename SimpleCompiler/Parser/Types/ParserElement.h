#pragma once
#include "../../Utilities/List.h"

class ParserElement
{
public:
	constexpr ParserElement()
	{
	}

public:
	virtual unsigned short GetRegisterMask()
	{
		return 0;
	}

	virtual unsigned long long GetStackSize()
	{
		return 0;
	}

	virtual unsigned long long GetCallingStackSize()
	{
		return 0;
	}

	virtual void Compile(class CompileMap& Enviroment)
	{
	}

	virtual void Parse(class EnviromentMap& Enviroment, const char* Expression)
	{
	}
};