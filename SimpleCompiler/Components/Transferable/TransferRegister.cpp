#include "TransferRegister.h"
#include "../../Compiler/CompileMap.h"
#include "../../Utilities/x86_x64Shell.h"

void TransferRegister::CompileAssign(CompileMap& Enviroment, RegisterType Source)
{
	if (Register == Source)
		return;

	if (Register.IsExtended())
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXWBR, MOVD_RM_R(LR_R(Register, Source))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXWB, MOVD_RM_R(LR_R(Register, Source))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	}
	else
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXWR, MOVD_RM_R(LR_R(Register, Source))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_RM_R(LR_R(Register, Source))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	}
}

void TransferRegister::CompileRetrieve(CompileMap& Enviroment, RegisterType Source)
{
	if (Register == Source)
		return;

	if (Register.IsExtended())
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXWRB, MOVD_R_RM(R_LR(Source, Register))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXWB, MOVD_R_RM(R_LR(Source, Register))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	}
	else
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXWR, MOVD_R_RM(R_LR(Source, Register))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_R_RM(R_LR(Source, Register))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	}
}