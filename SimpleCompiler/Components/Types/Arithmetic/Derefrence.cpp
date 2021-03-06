#include "Derefrence.h"
#include "../../../Compiler/CompileMap.h"
#include "../../../GlobalInfo/RegisterTypes.h"
#include "../../../Utilities/x86_x64Shell.h"

unsigned long Derefrence::GetReferenceMultiplier(long long Reference)
{
	return GivenOperand->GetReferenceMultiplier(Reference + 1);
}

RefObject<Operand> Derefrence::CreateOperator(RefObject<Operand> Operand)
{
	return RefObject<Derefrence>(Derefrence(Operand)).Cast<::Operand>();
}

void Derefrence::Compile(CompileMap& Enviroment, RegisterType Source) // A reminder to fix this to work with RBP, R12, R13, those will cuck this up pretty bad :P
{
	GivenOperand->Compile(Enviroment, Source);
	switch (GivenOperand->GetReferenceMultiplier(0))
	{
	case 1:
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXBR, MOVB_R_RM(R_MR(Source, Source)),
				SHLD_RM_B(LR(Source), 24),
				SHRD_RM_B(LR(Source), 24)
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				MOVB_R_RM(R_MR(Source, Source)),
				SHLD_RM_B(LR(Source), 24),
				SHRD_RM_B(LR(Source), 24)
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	case 2:
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXBR, PFX_WORD, MOVD_R_RM(R_MR(Source, Source)),
				SHLD_RM_B(LR(Source), 16),
				SHRD_RM_B(LR(Source), 16)
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_WORD, MOVD_R_RM(R_MR(Source, Source)),
				SHLD_RM_B(LR(Source), 16),
				SHRD_RM_B(LR(Source), 16)
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	case 4:
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXBR, MOVD_R_RM(R_MR(Source, Source))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				MOVD_R_RM(R_MR(Source, Source))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	default:
	{
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
	} break;
	}
}