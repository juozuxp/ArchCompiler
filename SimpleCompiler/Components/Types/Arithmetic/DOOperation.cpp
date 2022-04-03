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
		default:
		{
			if (Multiplier < 0xFF) // not sure if the multiplier is unsigned, if not, well we'll figure it out
			{
				unsigned char Multiplication[] =
				{
					PFX_REXWBR, IMUL_R_RM_B(LR_R(Register, Register), Multiplier)
				};

				Enviroment.AddCode(Multiplication, sizeof(Multiplication));
			}
			else if (Multiplier < 0xFFFF)
			{
				unsigned char Multiplication[] =
				{
					PFX_REXWBR, IMUL_R_RM_W(LR_R(Register, Register), Multiplier)
				};

				Enviroment.AddCode(Multiplication, sizeof(Multiplication));
			}
			else if (Multiplier < 0xFFFFFFFF)
			{
				unsigned char Multiplication[] =
				{
					PFX_REXWBR, IMUL_R_RM_D(LR_R(Register, Register), Multiplier)
				};

				Enviroment.AddCode(Multiplication, sizeof(Multiplication));
			}
		} break;
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
		default:
		{
			if (Multiplier < 0xFF) // not sure if the multiplier is unsigned, if not, well we'll figure it out
			{
				unsigned char Multiplication[] =
				{
					PFX_REXW, IMUL_R_RM_B(LR_R(Register, Register), Multiplier)
				};

				Enviroment.AddCode(Multiplication, sizeof(Multiplication));
			}
			else if (Multiplier < 0xFFFF)
			{
				unsigned char Multiplication[] =
				{
					PFX_REXW, IMUL_R_RM_W(LR_R(Register, Register), Multiplier)
				};

				Enviroment.AddCode(Multiplication, sizeof(Multiplication));
			}
			else if (Multiplier < 0xFFFFFFFF)
			{
				unsigned char Multiplication[] =
				{
					PFX_REXW, IMUL_R_RM_D(LR_R(Register, Register), Multiplier)
				};

				Enviroment.AddCode(Multiplication, sizeof(Multiplication));
			}
		} break;
		}
	}
}