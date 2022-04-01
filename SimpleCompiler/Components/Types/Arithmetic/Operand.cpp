#include "Operand.h"
#include "../../../Compiler/CompileMap.h"
#include "../../../GlobalInfo/RegisterTypes.h"

unsigned long Operand::GetArithmeticMultiplier(long long Reference)
{
	return 1;
}

void Operand::Compile(CompileMap & Enviroment, RegisterType Source)
{
}

void Operand::CompileRefrence(CompileMap& Enviroment, RegisterType Source)
{
}