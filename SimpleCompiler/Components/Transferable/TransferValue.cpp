#include "TransferValue.h"
#include "../../Compiler/CompileMap.h"
#include "../../Utilities/x86_x64Shell.h"

void TransferValue::CompileRetrieve(CompileMap& Enviroment, RegisterType Source)
{
	if (Value < 0xFF)
	{
		if (Value == 0)
		{
			if (Source.IsExtended())
			{
				unsigned char Shell[] =
				{
					PFX_REXWRB, XORD_RM_R(LR_R(Source, Source))
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					PFX_REXW, XORD_RM_R(LR_R(Source, Source))
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}

			return;
		}
		else
		{
			if (Source.IsExtended())
			{
				unsigned char Shell[] =
				{
					PFX_REXWBR, XORD_RM_R(LR_R(Source, Source)),
					PFX_REXB, MOV_R_B(Source, Value)
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					PFX_REXW, XORD_RM_R(LR_R(Source, Source)),
					PFX_REX, MOV_R_B(Source, Value)
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}

			return;
		}
	}

	if (Value < 0xFFFF) // clear the value, fuck knows why it's made like this but it will only clear RAX when it gets overwritten with a value bigger than or equal to 4 bytes
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXWBR, XORD_RM_R(LR_R(Source, Source)),
				PFX_REXB, MOV_R_W(Source, Value)
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, XORD_RM_R(LR_R(Source, Source)),
				MOV_R_W(Source, Value)
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}

		return;
	}

	if (Value < 0xFFFFFFFF)
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXB, MOV_R_D(Source, Value)
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				MOV_R_D(Source, Value)
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}

		return;
	}

	if (Source.IsExtended())
	{
		unsigned char Shell[] =
		{
			PFX_REXB | MOV_R_Q(Source, Value)
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			MOV_R_Q(Source, Value)
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
}