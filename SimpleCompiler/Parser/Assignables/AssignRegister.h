#pragma once
#include "Assignable.h"
#include "../../GlobalInfo/RegisterTypes.h"

class AssignRegister : Assignable
{
public:
	constexpr AssignRegister() : Assignable()
	{
	}

	constexpr AssignRegister(RegisterType Register) : Assignable(), Register(Register)
	{
	}

public:
	void Compile(class CompileMap& Enviroment);

private:
	RegisterType Register = RegisterType_None;
};

