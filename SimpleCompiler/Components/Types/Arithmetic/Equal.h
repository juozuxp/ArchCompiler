#pragma once
#include "DOOperation.h"

class Equal : public DOOperation
{
public:
	constexpr Equal()
	{
	}

	inline Equal(RefObject<Operand> Left, RefObject<Operand> Right, RegisterType TransitionSpace) : DOOperation(Left, Right, TransitionSpace)
	{
	}

public:
	static RefObject<class Operand> CreateOperator(RefObject<class Operand> First, RefObject<class Operand> Second, class RegisterType TransitionSpace);

public:
	void Compile(class CompileMap& Enviroment, RegisterType Source);
};