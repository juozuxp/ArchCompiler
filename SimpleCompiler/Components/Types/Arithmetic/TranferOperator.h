#pragma once
#include "Operand.h"
#include "../../../Utilities/RefObject.h"

class TranferOperator : public Operand
{
public:
	constexpr TranferOperator()
	{
	}

	inline TranferOperator(RefObject<class Transferable> Source) : Source(Source)
	{
	}

public:
	unsigned long GetReferenceMultiplier(long long Reference);

	void Compile(class CompileMap& Enviroment, RegisterType Source);
	void CompileRefrence(class CompileMap& Enviroment, class RegisterType Source);

private:
	RefObject<class Transferable> Source;
};