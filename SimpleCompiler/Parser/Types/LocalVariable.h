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
	List<unsigned char> CompileAssign();
	List<unsigned char> CompileRetrieve();

public:
	List<unsigned char> Compile(class CompileMap& Enviroment);

private:
	unsigned long long StackPosition = 0;
};