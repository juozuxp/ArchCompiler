#pragma once

class Transferable
{
public:
	constexpr Transferable()
	{
	}

public:
	virtual unsigned long GetReferenceMultiplier(long long Reference);

	virtual void PreCompile(class CompileMap& Enviroment, class RegisterType Source);
	virtual void PostCompile(class CompileMap& Enviroment, class RegisterType Source);

	virtual void CompileAssign(class CompileMap& Enviroment, class RegisterType Source);
	virtual void CompileRetrieve(class CompileMap& Enviroment, class RegisterType Source);
	virtual void CompileRefrence(class CompileMap& Enviroment, class RegisterType Source);
};