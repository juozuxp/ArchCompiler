#pragma once
#include "LocalVariable.h"

class Argument : public LocalVariable
{
public:
	constexpr Argument() 
	{
	}

	inline Argument(const char* Expression, unsigned long long Index) : LocalVariable(Expression), Index(Index)
	{
	}

public:
	void Compile(class CompileMap& Enviroment);

private:
	unsigned long long Index = 0;
};