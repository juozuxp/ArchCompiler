#pragma once
#include "../../Utilities/List.h"

class Transition // Will come with more complex compilations
{
public:
	constexpr Transition()
	{
	}

	inline Transition(List<unsigned char> Instruction) : Instruction(Instruction)
	{
	}

public:
	virtual void Compile(class CompileMap& Enviroment)
	{
	}

private:
	List<unsigned char> Instruction;
};