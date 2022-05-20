#include "TransferVariable.h"
#include "../../GlobalInfo/RegisterTypes.h"
#include "../Types/Variable.h"

unsigned long TransferVariable::GetReferenceMultiplier(long long Reference)
{
	return Variable->GetReferenceMultiplier(Reference);
}

void TransferVariable::CompileAssign(CompileMap& Enviroment, RegisterType Source)
{
	Variable->CompileAssign(Enviroment, Source, Dimension);
}

void TransferVariable::CompileRetrieve(CompileMap& Enviroment, RegisterType Source)
{
	Variable->CompileRetrieve(Enviroment, Source);
}

void TransferVariable::CompileRefrence(CompileMap& Enviroment, RegisterType Source)
{
	Variable->CompileRefrence(Enviroment, Source);
}