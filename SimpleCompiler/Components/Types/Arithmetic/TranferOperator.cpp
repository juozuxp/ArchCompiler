#include "TranferOperator.h"
#include "../../../GlobalInfo/RegisterTypes.h"
#include "../../Transferable/Transferable.h"

unsigned long TranferOperator::GetReferenceMultiplier(long long Reference)
{
	return this->Source->GetReferenceMultiplier(Reference);
}

void TranferOperator::Compile(class CompileMap& Enviroment, RegisterType Source)
{
	this->Source->CompileRetrieve(Enviroment, Source);
}

void TranferOperator::PreCompile(class CompileMap& Enviroment, RegisterType Source)
{
	this->Source->PreCompile(Enviroment, Source);
}

void TranferOperator::PostCompile(class CompileMap& Enviroment, RegisterType Source)
{
	this->Source->PostCompile(Enviroment, Source);
}

void TranferOperator::CompileRefrence(CompileMap& Enviroment, RegisterType Source)
{
	this->Source->CompileRefrence(Enviroment, Source);
}