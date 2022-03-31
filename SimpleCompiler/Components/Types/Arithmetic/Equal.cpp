#include "Equal.h"
#include "../../../Compiler/CompileMap.h"
#include "../../../Compiler/TempVariableMap.h"
#include "../../../Utilities/x86_x64Shell.h"

void Equal::Compile(CompileMap& Enviroment, RegisterType Source)
{
	unsigned long MainRelativity;
	unsigned long JumpRelativity;

	Left->Compile(Enviroment, Source);
	Right->Compile(Enviroment, TransitionSpace);

	MainRelativity = 0;
	if (TransitionSpace.IsExtended())
	{
		if (Source.IsExtended())
		{
			unsigned char Operation[] =
			{
				PFX_REXWRB, CMPD_R_RM(R_LR(Source, TransitionSpace)),
				PFX_REXB, MOV_RM_D(LR(Source), 0),
				PFX_REXB, SETE_RM(LR(Source))
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
		else
		{
			unsigned char Operation[] =
			{
				PFX_REXWB, CMPD_R_RM(R_LR(Source, TransitionSpace)),
				MOV_RM_D(LR(Source), 0),
				PFX_REX, SETE_RM(LR(Source))
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
	}
	else
	{
		if (Source.IsExtended())
		{
			unsigned char Operation[] =
			{
				PFX_REXWR, CMPD_R_RM(R_LR(Source, TransitionSpace)),
				PFX_REXB, MOV_RM_D(LR(Source), 0),
				PFX_REXB, SETE_RM(LR(Source))
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
		else
		{
			unsigned char Operation[] =
			{
				PFX_REXW, CMPD_R_RM(R_LR(Source, TransitionSpace)),
				MOV_RM_D(LR(Source), 0),
				PFX_REX, SETE_RM(LR(Source))
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
	}
}

RefObject<Operand> Equal::CreateOperator(RefObject<Operand> First, RefObject<Operand> Second, RegisterType TransitionSpace)
{
	return RefObject<Equal>(Equal(First, Second, TransitionSpace)).Cast<Operand>();
}