#pragma once
#include "Transferable.h"

class TransferValue : Transferable
{
public:
	constexpr TransferValue()
	{
	}

	inline TransferValue(unsigned long long Value) : Value(Value)
	{
	}

public:
	void CompileRetrieve(class CompileMap& Enviroment, RegisterType Source);

private:
	unsigned long long Value = 0;
};