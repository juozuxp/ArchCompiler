#pragma once
#include "../../Utilities/List.h"

class Assignable
{
public:
	constexpr Assignable()
	{
	}

public:
	virtual void Compile(class CompileMap& Enviroment)
	{
	}

	virtual void CompileRetrieve(class CompileMap& Enviroment)
	{
	}
};