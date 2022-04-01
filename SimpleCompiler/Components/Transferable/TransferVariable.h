#pragma once
#include "Transferable.h"
#include "../../Utilities/RefObject.h"

class TransferVariable : public Transferable
{
public:
	constexpr TransferVariable()
	{
	}

	inline TransferVariable(RefObject<class Variable> Variable) : Variable(Variable)
	{
	}

public:
	unsigned long GetReferenceMultiplier(long long Reference);

	void CompileAssign(class CompileMap& Enviroment, class RegisterType Source);
	void CompileRetrieve(class CompileMap& Enviroment, class RegisterType Source);
	void CompileRefrence(class CompileMap& Enviroment, class RegisterType Source);

private:
	RefObject<class Variable> Variable;
};