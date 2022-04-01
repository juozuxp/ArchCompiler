#include "TranferOperator.h"
#include "../../../GlobalInfo/RegisterTypes.h"
#include "../../Transferable/Transferable.h"

unsigned long TranferOperator::GetArithmeticMultiplier(long long Reference)
{
	return this->Source->GetArithmeticMultiplier(Reference);
}

void TranferOperator::Compile(CompileMap& Enviroment, RegisterType Source)
{
	this->Source->CompileRetrieve(Enviroment, Source);
}

void TranferOperator::CompileRefrence(CompileMap& Enviroment, RegisterType Source)
{
	this->Source->CompileRefrence(Enviroment, Source);
}