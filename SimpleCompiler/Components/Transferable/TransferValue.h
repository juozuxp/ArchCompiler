#pragma once
#include "Transferable.h"

class TransferValue : public Transferable
{
public:
	constexpr TransferValue()
	{
	}

	inline TransferValue(unsigned long long Value) : Value(Value)
	{
	}

public:
	void CompileRetrieve(class CompileMap& Enviroment, class RegisterType Source);

private:
	unsigned long long Value = 0;
};