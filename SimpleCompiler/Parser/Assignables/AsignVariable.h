#pragma once
#include "Assignable.h"
#include "../../Utilities/RefObject.h"
#include "../Types/Variable.h"

class AsignVariable : Assignable
{
public:
	constexpr AsignVariable()
	{
	}

	inline AsignVariable(RefObject<Variable> Variable) : Variable(Variable)
	{
	}

public:
	List<unsigned char> Compile(class CompileMap& Enviroment);

private:
	RefObject<Variable> Variable;
};

