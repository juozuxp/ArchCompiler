#include "TransferVariable.h"
#include "../../GlobalInfo/RegisterTypes.h"
#include "../Types/Variable.h"

unsigned long TransferVariable::GetArithmeticMultiplier(long long Reference)
{
	return Variable->GetArithmeticMultiplier(Reference);
}

void TransferVariable::CompileAssign(CompileMap& Enviroment, RegisterType Source)
{
	Variable->CompileAssign(Enviroment, Source);
}

void TransferVariable::CompileRetrieve(CompileMap& Enviroment, RegisterType Source)
{
	Variable->CompileRetrieve(Enviroment, Source);
}

void TransferVariable::CompileRefrence(CompileMap& Enviroment, RegisterType Source)
{
	Variable->CompileRefrence(Enviroment, Source);
}