#pragma once
#include "DOOperation.h"

class Subtraction : public DOOperation
{
public:
	constexpr Subtraction()
	{
	}

	inline Subtraction(RefObject<Operand> Left, RefObject<Operand> Right, RegisterType TransitionSpace) : DOOperation(Left, Right, TransitionSpace)
	{
	}

public:
	static RefObject<class Operand> CreateOperator(RefObject<class Operand> First, RefObject<class Operand> Second, class RegisterType TransitionSpace);

public:
	void Compile(class CompileMap& Enviroment, RegisterType Source);
};