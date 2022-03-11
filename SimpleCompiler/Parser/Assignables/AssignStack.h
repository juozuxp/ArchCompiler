#pragma once
#include "Assignable.h"

class AssignStack : Assignable
{
public:
	constexpr AssignStack()
	{
	}

	constexpr AssignStack(unsigned long long StackOffset) : StackLocation(StackOffset)
	{
	}

public:
	void Compile(class CompileMap& Enviroment);

private:
	unsigned long long StackLocation = 0;
};