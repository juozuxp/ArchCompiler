#pragma once
#include "Operation.h"

class Subtraction : Operation
{
public:
	constexpr Subtraction()
	{
	}

	inline Subtraction(RefObject<Operand> Left, RefObject<Operand> Right, RegisterType TransitionSpace) : Operation(Left, Right, TransitionSpace)
	{
	}

public:
	void Compile(class CompileMap& Enviroment, RegisterType Source);
};