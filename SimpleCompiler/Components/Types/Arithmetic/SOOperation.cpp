#include "SOOperation.h"
#include "../../../GlobalInfo/RegisterTypes.h"

unsigned long SOOperation::GetReferenceMultiplier(long long Reference)
{
	return GivenOperand->GetReferenceMultiplier(Reference);
}

void SOOperation::PreCompile(class CompileMap& Enviroment, RegisterType Source)
{
	GivenOperand->PreCompile(Enviroment, Source);
}

void SOOperation::PostCompile(class CompileMap& Enviroment, RegisterType Source)
{
	GivenOperand->PostCompile(Enviroment, Source);
}