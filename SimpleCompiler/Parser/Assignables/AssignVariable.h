#pragma once
#include "Assignable.h"
#include "../../Utilities/RefObject.h"
#include "../Types/Variable.h"

class AssignVariable : Assignable
{
public:
	constexpr AssignVariable()
	{
	}

	inline AssignVariable(RefObject<Variable> Variable) : Variable(Variable)
	{
	}

public:
	void Compile(class CompileMap& Enviroment);

private:
	RefObject<Variable> Variable;
};

