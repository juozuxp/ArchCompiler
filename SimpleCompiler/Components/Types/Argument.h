#pragma once
#include "LocalVariable.h"

class Argument : LocalVariable
{
public:
	constexpr Argument() 
	{
	}

	inline Argument(const char* Expression, unsigned long long Index) : LocalVariable(Expression), Index(Index)
	{
	}

public:
	unsigned long long GetStackSize()
	{
		return 0;
	}

	void Compile(class CompileMap& Enviroment);

private:
	unsigned long long Index = 0;
};