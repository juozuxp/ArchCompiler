#pragma once
#include "SOOperation.h"
#include "../../../Utilities/RefObject.h"

class Derefrence : public SOOperation
{
public:
	constexpr Derefrence()
	{
	}

	inline Derefrence(RefObject<Operand> Operand) : SOOperation(Operand)
	{
	}

public:
	static RefObject<class Operand> CreateOperator(RefObject<class Operand> Operand);

public:
	void Compile(class CompileMap& Enviroment, class RegisterType Source);
};