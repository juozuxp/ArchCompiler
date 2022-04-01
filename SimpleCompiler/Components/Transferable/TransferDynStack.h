#pragma once
#include "Transferable.h"

class TransferDynStack : public Transferable
{
public:
	constexpr TransferDynStack()
	{
	}

public:
	void CompileAssign(class CompileMap& Enviroment, class RegisterType Source);
	void CompileRetrieve(class CompileMap& Enviroment, class RegisterType Source);

private:
	unsigned long long LocationInStack = ~0;
};