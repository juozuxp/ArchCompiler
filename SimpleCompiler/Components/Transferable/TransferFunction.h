#pragma once
#include "Transferable.h"
#include "../Types/FunctionCall.h"

class TransferFunction : public Transferable
{
public:
	constexpr TransferFunction()
	{
	}

	TransferFunction(RefObject<class EnviromentMap> Enviroment, const char* Expression);

public:
	unsigned long GetReferenceMultiplier(long long Reference);

	void PreCompile(class CompileMap& Enviroment, class RegisterType Source);
	void PostCompile(class CompileMap& Enviroment, class RegisterType Source);

	void CompileRetrieve(class CompileMap& Enviroment, class RegisterType Source);

private:
	RefObject<FunctionCall> CallObject;
};