#include "Operand.h"
#include "../../../Compiler/CompileMap.h"
#include "../../../GlobalInfo/RegisterTypes.h"

unsigned long Operand::GetReferenceMultiplier(long long Reference)
{
	return 0;
}

void Operand::Compile(CompileMap & Enviroment, RegisterType Source)
{
}

void Operand::CompileRefrence(CompileMap& Enviroment, RegisterType Source)
{
}