#include "TransferDynStack.h"
#include "../../Compiler/CompileMap.h"
#include "../../Utilities/x86_x64Shell.h"

void TransferDynStack::PreCompile(CompileMap& Enviroment, RegisterType Source)
{
	if (LocationInStack & (1ull << 63))
	{
		Enviroment.AllocTempStack(0x8);
		LocationInStack ^= 1ull << 63;
	}
}

void TransferDynStack::CompileAssign(CompileMap& Enviroment, RegisterType Source)
{
	if (LocationInStack == ((1ull << 63u) - 1ull))
		LocationInStack = Enviroment.AllocTempStack(0x8);

	if (LocationInStack < 0x7F)
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXWR, MOVD_RM_R(MRSP_BO_R(Source, LocationInStack)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_RM_R(MRSP_BO_R(Source, LocationInStack)),
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
				PFX_REXWR, MOVD_RM_R(MRSP_DO_R(Source, LocationInStack)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_RM_R(MRSP_DO_R(Source, LocationInStack)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	}
}

void TransferDynStack::CompileRetrieve(CompileMap& Enviroment, RegisterType Source)
{
	if (LocationInStack == ((1ull << 63u) - 1ull))
		LocationInStack = Enviroment.AllocTempStack(0x8);

	if (LocationInStack < 0x7F)
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXWR, MOVD_R_RM(R_MRSP_BO(Source, LocationInStack)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_R_RM(R_MRSP_BO(Source, LocationInStack)),
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
				PFX_REXWR, MOVD_R_RM(R_MRSP_DO(Source, LocationInStack)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_R_RM(R_MRSP_DO(Source, LocationInStack)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	}
}