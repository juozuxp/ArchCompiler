#include "TransferVariable.h"

void TransferVariable::CompileAssign(CompileMap& Enviroment, RegisterType Source)
{
	Variable->CompileAssign(Enviroment, Source);
}

void TransferVariable::CompileRetrieve(CompileMap& Enviroment, RegisterType Source)
{
	Variable->CompileRetrieve(Enviroment, Source);
}