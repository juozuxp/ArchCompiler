#pragma once
#include "Operand.h"
#include "../../../Utilities/RefObject.h"
#include "../../../GlobalInfo/RegisterTypes.h"

class DOOperation : public Operand // Dual operand operation, feels better to just simplify it to DO
{
public:
	constexpr DOOperation()
	{
	}

public:
	unsigned long GetArithmeticMultiplier(long long Reference);

protected:
	inline DOOperation(RefObject<Operand> Left, RefObject<Operand> Right, RegisterType TransitionSpace) : Left(Left), Right(Right), TransitionSpace(TransitionSpace)
	{
	}

protected:
	void CompileArithmeticMultiplier(class CompileMap& Enviroment, class RegisterType Register);

protected:
	RefObject<Operand> Left;
	RefObject<Operand> Right;
	RegisterType TransitionSpace;
};