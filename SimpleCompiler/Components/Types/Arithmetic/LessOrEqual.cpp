#include "LessOrEqual.h"
#include "../../../Compiler/CompileMap.h"
#include "../../../Compiler/TempVariableMap.h"
#include "../../../Utilities/x86_x64Shell.h"

void LessOrEqual::Compile(CompileMap& Enviroment, RegisterType Source)
{
	Left->Compile(Enviroment, Source);
	Right->Compile(Enviroment, TransitionSpace);

	if (TransitionSpace.IsExtended())
	{
		if (Source.IsExtended())
		{
			unsigned char Operation[] =
			{
				PFX_REXWRB, CMPD_R_RM(R_LR(Source, TransitionSpace)),
				PFX_REXB, MOV_RM_D(LR(Source), 0),
				PFX_REXB, SETBE_RM(LR(Source))
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
		else
		{
			unsigned char Operation[] =
			{
				PFX_REXWB, CMPD_R_RM(R_LR(Source, TransitionSpace)),
				MOV_RM_D(LR(Source), 0),
				PFX_REX, SETBE_RM(LR(Source))
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
				PFX_REXB, SETBE_RM(LR(Source))
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
		else
		{
			unsigned char Operation[] =
			{
				PFX_REXW, CMPD_R_RM(R_LR(Source, TransitionSpace)),
				MOV_RM_D(LR(Source), 0),
				PFX_REX, SETBE_RM(LR(Source))
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
	}
}

void LessOrEqual::CompileSigned(CompileMap& Enviroment, RegisterType Source)
{
	Left->CompileSigned(Enviroment, Source);
	Right->CompileSigned(Enviroment, TransitionSpace);

	if (TransitionSpace.IsExtended())
	{
		if (Source.IsExtended())
		{
			unsigned char Operation[] =
			{
				PFX_REXWRB, CMPD_R_RM(R_LR(Source, TransitionSpace)),
				PFX_REXB, MOV_RM_D(LR(Source), 0),
				PFX_REXB, SETLE_RM(LR(Source))
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
		else
		{
			unsigned char Operation[] =
			{
				PFX_REXWB, CMPD_R_RM(R_LR(Source, TransitionSpace)),
				MOV_RM_D(LR(Source), 0),
				PFX_REX, SETLE_RM(LR(Source))
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
				PFX_REXB, SETLE_RM(LR(Source))
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
		else
		{
			unsigned char Operation[] =
			{
				PFX_REXW, CMPD_R_RM(R_LR(Source, TransitionSpace)),
				MOV_RM_D(LR(Source), 0),
				PFX_REX, SETLE_RM(LR(Source))
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
	}
}

RefObject<Operand> LessOrEqual::CreateOperator(RefObject<Operand> First, RefObject<Operand> Second, RegisterType TransitionSpace)
{
	return RefObject<LessOrEqual>(LessOrEqual(First, Second, TransitionSpace)).Cast<Operand>();
}