#pragma once

class Operand
{
public:
	constexpr Operand()
	{
	}

public:
	virtual unsigned long GetReferenceMultiplier(long long Reference);

	virtual void PreCompile(class CompileMap& Enviroment, class RegisterType Source);
	virtual void Compile(class CompileMap& Enviroment, class RegisterType Source);
	virtual void CompileSigned(class CompileMap& Enviroment, class RegisterType Source);
	virtual void PostCompile(class CompileMap& Enviroment, class RegisterType Source);

	virtual void CompileRefrence(class CompileMap& Enviroment, class RegisterType Source);
};