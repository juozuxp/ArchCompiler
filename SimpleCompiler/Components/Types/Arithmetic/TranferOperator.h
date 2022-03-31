#pragma once
#include "Operand.h"
#include "../../../Utilities/RefObject.h"
#include "../../Transferable/Transferable.h"

class TranferOperator : public Operand
{
public:
	constexpr TranferOperator()
	{
	}

	inline TranferOperator(RefObject<Transferable> Source) : Source(Source)
	{
	}

public:
	void Compile(class CompileMap& Enviroment, RegisterType Source);

private:
	RefObject<Transferable> Source;
};