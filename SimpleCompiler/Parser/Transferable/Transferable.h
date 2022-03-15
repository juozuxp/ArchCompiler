#pragma once
#include "../../Utilities/List.h"
#include "../../GlobalInfo/RegisterTypes.h"

class Transferable
{
public:
	constexpr Transferable()
	{
	}

public:
	virtual void CompileAssign(class CompileMap& Enviroment, RegisterType Source)
	{
	}

	virtual void CompileRetrieve(class CompileMap& Enviroment, RegisterType Source)
	{
	}
};