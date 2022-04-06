#pragma once
#include "Variable.h"

class StaticVariable : public Variable
{
public:
	constexpr StaticVariable() : Variable()
	{
	}

	inline StaticVariable(const char* Expression) : Variable(Expression)
	{
	}

public:
	void Compile(class CompileMap& Enviroment);
	void PreCompile(class CompileMap& Enviroment);

	void CompileCall(class CompileMap& Enviroment);
	void CompileAssign(class CompileMap& Enviroment, class RegisterType Source);
	void CompileRetrieve(class CompileMap& Enviroment, class RegisterType Source);
	void CompileRefrence(class CompileMap& Enviroment, class RegisterType Source);

protected:
	unsigned long long DataPosition = 0;
};