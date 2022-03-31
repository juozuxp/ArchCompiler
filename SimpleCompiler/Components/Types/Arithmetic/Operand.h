#pragma once

class Operand
{
public:
	constexpr Operand()
	{
	}

public:
	virtual void Compile(class CompileMap& Enviroment, class RegisterType Source);
};