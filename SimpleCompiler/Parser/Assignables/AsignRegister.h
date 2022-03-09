#pragma once
#include "Assignable.h"
#include "../../GlobalInfo/RegisterTypes.h"

class AsignRegister : Assignable
{
public:
	constexpr AsignRegister() : Assignable()
	{
	}

	constexpr AsignRegister(RegisterType Register) : Assignable(), Register(Register)
	{
	}

public:
	List<unsigned char> Compile(class CompileMap& Enviroment);

private:
	RegisterType Register = RegisterType_None;
};

