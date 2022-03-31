#include "Derefrence.h"
#include "../../../Compiler/CompileMap.h"
#include "../../../GlobalInfo/RegisterTypes.h"
#include "../../../Utilities/x86_x64Shell.h"

RefObject<Operand> Derefrence::CreateOperator(RefObject<Operand> Operand)
{
	return RefObject<Derefrence>(Derefrence(Operand)).Cast<::Operand>();
}

void Derefrence::Compile(CompileMap& Enviroment, RegisterType Source)
{
	GivenOperand->Compile(Enviroment, Source);
	if (Source.IsExtended())
	{
		unsigned char Shell[] =
		{
			PFX_REXWBR, MOVD_R_RM(R_MR(Source, Source))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			PFX_REXW, MOVD_R_RM(R_MR(Source, Source))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
}