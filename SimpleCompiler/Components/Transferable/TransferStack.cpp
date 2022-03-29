#include "TransferStack.h"
#include "../../Compiler/CompileMap.h"
#include "../../Utilities/x86_x64Shell.h"

void TransferStack::CompileAssign(CompileMap& Enviroment, RegisterType Source)
{
	if (StackLocation <= 0x7F)
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXWR, MOVD_RM_R(MRSP_BO_R(Source, StackLocation))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_RM_R(MRSP_BO_R(Source, StackLocation))
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
				PFX_REXWR, MOVD_RM_R(MRSP_DO_R(Source, StackLocation))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_RM_R(MRSP_DO_R(Source, StackLocation))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	}
}

void TransferStack::CompileRetrieve(CompileMap& Enviroment, RegisterType Source)
{
	if (StackLocation <= 0x7F)
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXWR, MOVD_R_RM(R_MRSP_BO(Source, StackLocation))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_R_RM(R_MRSP_BO(Source, StackLocation))
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
				PFX_REXWR, MOVD_R_RM(R_MRSP_BO(Source, StackLocation))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_R_RM(R_MRSP_BO(Source, StackLocation))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	}
}