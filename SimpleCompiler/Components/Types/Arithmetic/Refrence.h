#pragma once
#include "SOOperation.h"
#include "../../../Utilities/RefObject.h"

class Refrence : public SOOperation
{
public:
	constexpr Refrence()
	{
	}

	inline Refrence(RefObject<Operand> Operand) : SOOperation(Operand)
	{
	}

public:
	unsigned long GetReferenceMultiplier(long long Reference);

public:
	static RefObject<class Operand> CreateOperator(RefObject<class Operand> Operand);

public:
	void Compile(class CompileMap& Enviroment, class RegisterType Source);
};