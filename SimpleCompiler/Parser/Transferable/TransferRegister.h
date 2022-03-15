#pragma once
#include "Transferable.h"
#include "../../GlobalInfo/RegisterTypes.h"

class TransferRegister : Transferable
{
public:
	constexpr TransferRegister() : Transferable()
	{
	}

	constexpr TransferRegister(RegisterType Register) : Transferable(), Register(Register)
	{
	}

public:
	void CompileAssign(class CompileMap& Enviroment, RegisterType Source);
	void CompileRetrieve(class CompileMap& Enviroment, RegisterType Source);

private:
	RegisterType Register = RegisterType::None;
};

