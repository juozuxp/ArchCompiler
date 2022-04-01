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

void Derefrence::Compile(CompileMap& Enviroment, RegisterType Source)
{
	GivenOperand->Compile(Enviroment, Source);
	switch (GivenOperand->GetReferenceMultiplier(0))
	{
	/*case 1:
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXBR, XORD_RM_R(LR_R(Source, Source)),
				PFX_REXBR, MOVD_R_RM(R_MR(Source, Source))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, XORD_RM_R(LR_R(Source, Source)),
				MOVD_R_RM(R_MR(Source, Source))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}

	case 2:
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXBR, XORD_RM_R(LR_R(Source, Source)),
				PFX_REXBR, MOVD_R_RM(R_MR(Source, Source))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, XORD_RM_R(LR_R(Source, Source)),
				MOVD_R_RM(R_MR(Source, Source))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}*/

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