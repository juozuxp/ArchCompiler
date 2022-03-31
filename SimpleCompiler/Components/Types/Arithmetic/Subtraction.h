#pragma once
#include "Operation.h"

class Subtraction : public Operation
{
public:
	constexpr Subtraction()
	{
	}

	inline Subtraction(RefObject<Operand> Left, RefObject<Operand> Right, RegisterType TransitionSpace) : Operation(Left, Right, TransitionSpace)
	{
	}

public:
	static RefObject<class Operand> CreateOperator(RefObject<class Operand> First, RefObject<class Operand> Second, class RegisterType TransitionSpace);

public:
	void Compile(class CompileMap& Enviroment, RegisterType Source);
};