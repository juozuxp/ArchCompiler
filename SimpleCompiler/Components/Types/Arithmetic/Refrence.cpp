#include "Refrence.h"
#include "../../../GlobalInfo/RegisterTypes.h"

unsigned long Refrence::GetReferenceMultiplier(long long Reference)
{
	return GivenOperand->GetReferenceMultiplier(Reference - 1);
}

RefObject<Operand> Refrence::CreateOperator(RefObject<Operand> Operand)
{
	return RefObject<Refrence>(Refrence(Operand)).Cast<::Operand>();
}

void Refrence::Compile(CompileMap& Enviroment, RegisterType Source)
{
	GivenOperand->CompileRefrence(Enviroment, Source);
}