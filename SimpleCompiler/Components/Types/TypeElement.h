#pragma once
#include "../../Utilities/List.h"

class TypeElement
{
public:
	constexpr TypeElement()
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

	virtual unsigned long long Parse(class EnviromentMap& Enviroment, const char* Expression)
	{
		return 0;
	}
};