#pragma once

class Operand
{
public:
	constexpr Operand()
	{
	}

public:
	virtual unsigned long GetReferenceMultiplier(long long Reference);

	virtual void Compile(class CompileMap& Enviroment, class RegisterType Source);
	virtual void CompileRefrence(class CompileMap& Enviroment, class RegisterType Source);
};