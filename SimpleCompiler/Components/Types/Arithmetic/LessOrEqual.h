#pragma once
#include "DOOperation.h"

class LessOrEqual : DOOperation
{
public:
	constexpr LessOrEqual()
	{
	}

	inline LessOrEqual(RefObject<Operand> Left, RefObject<Operand> Right, RegisterType TransitionSpace) : DOOperation(Left, Right, TransitionSpace)
	{
	}

public:
	static RefObject<class Operand> CreateOperator(RefObject<class Operand> First, RefObject<class Operand> Second, class RegisterType TransitionSpace);

public:
	void Compile(class CompileMap& Enviroment, RegisterType Source);
	void CompileSigned(class CompileMap& Enviroment, class RegisterType Source);
};

