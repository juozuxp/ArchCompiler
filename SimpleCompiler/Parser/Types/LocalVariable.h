#pragma once
#include "Variable.h"

class LocalVariable : public Variable
{
public:
	constexpr LocalVariable()
	{
	}

	LocalVariable(const char* Expression) : Variable(Expression)
	{
	}

public:
	unsigned long long GetStackSize()
	{
		return this->VariableSize;
	}

public:
	void CompileAssign(class CompileMap& Enviroment);
	void CompileRetrieve(class CompileMap& Enviroment);

public:
	void Compile(class CompileMap& Enviroment);

private:
	unsigned long long StackPosition = 0;
};