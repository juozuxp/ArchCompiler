#pragma once
#include "Operand.h"
#include "../../../Utilities/RefObject.h"

class SOOperation : public Operand // Single operand operation, feels better to just simplify it to SO
{
public:
	constexpr SOOperation()
	{
	}

public:
	unsigned long GetReferenceMultiplier(long long Reference);

	void PreCompile(class CompileMap& Enviroment, class RegisterType Source);
	void PostCompile(class CompileMap& Enviroment, class RegisterType Source);

protected:
	inline SOOperation(RefObject<Operand> Operand) : GivenOperand(Operand)
	{
	}

protected:
	RefObject<Operand> GivenOperand;
};