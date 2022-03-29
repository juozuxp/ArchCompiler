#pragma once
#include "Variable.h"

class LocalVariable : public Variable
{
public:
	constexpr LocalVariable()
	{
	}

	inline LocalVariable(const char* Expression) : Variable(Expression)
	{
	}

public:
	void PreCompile(class CompileMap& Enviroment);
	void Compile(class CompileMap& Enviroment);

	void CompileCall(class CompileMap& Enviroment);
	void CompileAssign(class CompileMap& Enviroment, RegisterType Source);
	void CompileRetrieve(class CompileMap& Enviroment, RegisterType Source);

protected:
	unsigned long long StackPosition = 0;
};