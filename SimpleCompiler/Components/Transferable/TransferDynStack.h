#pragma once
#include "Transferable.h"

class TransferDynStack : Transferable
{
public:
	constexpr TransferDynStack()
	{
	}

public:
	void CompileAssign(class CompileMap& Enviroment, RegisterType Source);
	void CompileRetrieve(class CompileMap& Enviroment, RegisterType Source);

private:
	unsigned long long LocationInStack = ~0;
};