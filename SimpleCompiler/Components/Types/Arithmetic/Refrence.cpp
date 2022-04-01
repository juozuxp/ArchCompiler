#include "Refrence.h"
#include "../../../GlobalInfo/RegisterTypes.h"

unsigned long Refrence::GetArithmeticMultiplier(long long Reference)
{
	return GivenOperand->GetArithmeticMultiplier(Reference - 1);
}

RefObject<Operand> Refrence::CreateOperator(RefObject<Operand> Operand)
{
	return RefObject<Refrence>(Refrence(Operand)).Cast<::Operand>();
}

void Refrence::Compile(CompileMap& Enviroment, RegisterType Source)
{
	GivenOperand->CompileRefrence(Enviroment, Source);
}