#pragma once
#include "Operation.h"

class Addition : public Operation
{
public:
	constexpr Addition()
	{
	}

	inline Addition(RefObject<Operand> Left, RefObject<Operand> Right, RegisterType TransitionSpace) : Operation(Left, Right, TransitionSpace)
	{
	}

public:
	void Compile(class CompileMap& Enviroment, RegisterType Source);
};