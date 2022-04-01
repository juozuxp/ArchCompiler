#pragma once
#include "Transferable.h"

class TransferStack : public Transferable
{
public:
	constexpr TransferStack()
	{
	}

	constexpr TransferStack(unsigned long long StackOffset) : StackLocation(StackOffset)
	{
	}

public:
	void CompileAssign(class CompileMap& Enviroment, class RegisterType Source);
	void CompileRetrieve(class CompileMap& Enviroment, class RegisterType Source);

private:
	unsigned long long StackLocation = 0;
};