#pragma once
#include "Transferable.h"
#include "../../Utilities/RefObject.h"
#include "../Types/Variable.h"

class TransferVariable : Transferable
{
public:
	constexpr TransferVariable()
	{
	}

	inline TransferVariable(RefObject<Variable> Variable) : Variable(Variable)
	{
	}

public:
	void CompileAssign(class CompileMap& Enviroment, RegisterType Source);
	void CompileRetrieve(class CompileMap& Enviroment, RegisterType Source);

private:
	RefObject<Variable> Variable;
};