#include "DOOperation.h"
#include "../../../Utilities/x86_x64Shell.h"
#include "../../../Compiler/CompileMap.h"

unsigned long DOOperation::GetReferenceMultiplier(long long Reference)
{
	return Left->GetReferenceMultiplier(Reference) < Right->GetReferenceMultiplier(Reference) ? Right->GetReferenceMultiplier(Reference) : Left->GetReferenceMultiplier(Reference);
}

void DOOperation::CompileArithmeticMultiplier(CompileMap& Enviroment, RegisterType Register)
{
	unsigned long Multiplier = Left->GetReferenceMultiplier(0);
	if (TransitionSpace.IsExtended())
	{
		switch (Multiplier)
		{
		case 0:
		case 1:
		{
		} break;
		case 2:
		{
			unsigned char Multiplication[] =
			{
				PFX_REXWB, SHLD_RM_1(LR(Register))
			};

			Enviroment.AddCode(Multiplication, sizeof(Multiplication));
		} break;
		case 4:
		{
			unsigned char Multiplication[] =
			{
				PFX_REXWB, SHLD_RM_B(LR(Register), 2)
			};

			Enviroment.AddCode(Multiplication, sizeof(Multiplication));
		} break;
		case 8:
		{
			unsigned char Multiplication[] =
			{
				PFX_REXWB, SHLD_RM_B(LR(Register), 3)
			};

			Enviroment.AddCode(Multiplication, sizeof(Multiplication));
		} break;
		/*default:
		{
			unsigned char Multiplication[] =
			{
				MOV_R_D(EAX, Multiplier / 8),
				PFX_REXWB, SHLD_RM_B(LR(EAX), 3)
				PFX_REXWB
			};
		} break;*/ // not yet finished, will have to consider a few things before I can finish this
		}
	}
	else
	{
		switch (Multiplier)
		{
		case 0:
		case 1:
		{
		} break;
		case 2:
		{
			unsigned char Multiplication[] =
			{
				PFX_REXW, SHLD_RM_1(LR(TransitionSpace))
			};

			Enviroment.AddCode(Multiplication, sizeof(Multiplication));
		} break;
		case 4:
		{
			unsigned char Multiplication[] =
			{
				PFX_REXW, SHLD_RM_B(LR(TransitionSpace), 2)
			};

			Enviroment.AddCode(Multiplication, sizeof(Multiplication));
		} break;
		case 8:
		{
			unsigned char Multiplication[] =
			{
				PFX_REXW, SHLD_RM_B(LR(TransitionSpace), 3)
			};

			Enviroment.AddCode(Multiplication, sizeof(Multiplication));
		} break;
		/*default:
		{
			unsigned char Multiplication[] =
			{
				MOV_R_D(EAX, Multiplier / 8),
				PFX_REXWB, SHLD_RM_B(LR(EAX), 3)
				PFX_REXWB
			};
		} break;*/ // not yet finished, will have to consider a few things before I can finish this
		}
	}
}