#include "LocalVariable.h"
#include "../../Utilities/SimpleUtilities.h"
#include "../Enviroments/EnviromentMap.h"
#include "../../Compiler/CompileMap.h"
#include "Arithmetic.h"
#include "../../Utilities/x86_x64Shell.h"

void LocalVariable::CompileAssign(CompileMap& Enviroment, RegisterType Source)
{
	switch (GetVariableSize())
	{
	case 1:
	{
		if (StackPosition < 0x7F)
		{
			if (Source.IsExtended())
			{
				unsigned char Shell[] =
				{
					PFX_REXR, MOVB_RM_R(MRSP_BO_R(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					MOVB_RM_R(MRSP_BO_R(Source, StackPosition)),
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
					PFX_REXR, MOVB_RM_R(MRSP_DO_R(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					MOVB_RM_R(MRSP_DO_R(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
		}
	} break;
	case 2:
	{
		if (StackPosition < 0x7F)
		{
			if (Source.IsExtended())
			{

				unsigned char Shell[] =
				{
					PFX_REXR, PFX_WORD, MOVD_RM_R(MRSP_BO_R(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					PFX_WORD, MOVD_RM_R(MRSP_BO_R(Source, StackPosition)),
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
					PFX_REXR, PFX_WORD, MOVD_RM_R(MRSP_DO_R(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					PFX_WORD, MOVD_RM_R(MRSP_DO_R(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
		}
	} break;
	case 4:
	{
		if (StackPosition < 0x7F)
		{
			if (Source.IsExtended())
			{

				unsigned char Shell[] =
				{
					PFX_REXR, MOVD_RM_R(MRSP_BO_R(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					MOVD_RM_R(MRSP_BO_R(Source, StackPosition)),
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
					PFX_REXR, MOVD_RM_R(MRSP_DO_R(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					MOVD_RM_R(MRSP_DO_R(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
		}
	} break;
	case 8:
	{
		if (StackPosition < 0x7F)
		{
			if (Source.IsExtended())
			{

				unsigned char Shell[] =
				{
					PFX_REXWR, MOVD_RM_R(MRSP_BO_R(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					PFX_REXW, MOVD_RM_R(MRSP_BO_R(Source, StackPosition)),
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
					PFX_REXWR, MOVD_RM_R(MRSP_DO_R(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					PFX_REXW, MOVD_RM_R(MRSP_DO_R(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
		}
	} break;
	}
}

void LocalVariable::CompileRetrieve(CompileMap& Enviroment, RegisterType Source)
{
	switch (GetVariableSize())
	{
	case 1:
	{
		if (StackPosition < 0x7F)
		{
			if (Source.IsExtended())
			{
				unsigned char Shell[] =
				{
					PFX_REXBR, XORD_RM_R(LR_R(Source, Source)),
					PFX_REXR, MOVB_R_RM(R_MRSP_BO(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					XORD_RM_R(LR_R(Source, Source)),
					MOVB_R_RM(R_MRSP_BO(Source, StackPosition)),
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
					PFX_REXBR, XORD_RM_R(LR_R(Source, Source)),
					PFX_REXR, MOVB_R_RM(R_MRSP_DO(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					XORD_RM_R(LR_R(Source, Source)),
					MOVB_R_RM(R_MRSP_DO(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
		}
	} break;
	case 2:
	{
		if (StackPosition < 0x7F)
		{
			if (Source.IsExtended())
			{

				unsigned char Shell[] =
				{
					PFX_REXBR, XORD_RM_R(LR_R(Source, Source)),
					PFX_REXR, PFX_WORD, MOVD_R_RM(R_MRSP_BO(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					XORD_RM_R(LR_R(Source, Source)),
					PFX_WORD, MOVD_R_RM(R_MRSP_BO(Source, StackPosition)),
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
					PFX_REXBR, XORD_RM_R(LR_R(Source, Source)),
					PFX_REXR, PFX_WORD, MOVD_R_RM(R_MRSP_DO(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					XORD_RM_R(LR_R(Source, Source)),
					PFX_WORD, MOVD_R_RM(R_MRSP_DO(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
		}
	} break;
	case 4:
	{
		if (StackPosition < 0x7F)
		{
			if (Source.IsExtended())
			{

				unsigned char Shell[] =
				{
					PFX_REXR, MOVD_R_RM(R_MRSP_BO(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					MOVD_R_RM(R_MRSP_BO(Source, StackPosition)),
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
					PFX_REXR, MOVD_R_RM(R_MRSP_DO(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					MOVD_R_RM(R_MRSP_DO(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
		}
	} break;
	case 8:
	{
		if (StackPosition < 0x7F)
		{
			if (Source.IsExtended())
			{

				unsigned char Shell[] =
				{
					PFX_REXWR, MOVD_R_RM(R_MRSP_BO(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					PFX_REXW, MOVD_R_RM(R_MRSP_BO(Source, StackPosition)),
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
					PFX_REXWR, MOVD_R_RM(R_MRSP_DO(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					PFX_REXW, MOVD_R_RM(R_MRSP_DO(Source, StackPosition)),
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
		}
	} break;
	}
}

void LocalVariable::CompileRefrence(CompileMap& Enviroment, RegisterType Source)
{
	if (StackPosition < 0x7F)
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXWR, LEAD_R_M(R_MRSP_BO(Source, StackPosition))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, LEAD_R_M(R_MRSP_BO(Source, StackPosition))
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
				PFX_REXWR, LEAD_R_M(R_MRSP_DO(Source, StackPosition))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, LEAD_R_M(R_MRSP_DO(Source, StackPosition))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	}
}

void LocalVariable::PreCompile(CompileMap& Enviroment)
{
	if (Assigner)
		Assigner->PreCompile(Enviroment);
	
	Enviroment.AllocConstStack(GetVariableSize());
}

void LocalVariable::Compile(CompileMap& Enviroment)
{
	StackPosition = Enviroment.AllocConstStack(GetVariableSize());
	if (Assigner)
		Assigner->Compile(Enviroment);
}

void LocalVariable::CompileCall(CompileMap& Enviroment)
{
	if (StackPosition < 0x7F)
	{
		unsigned char Shell[] =
		{
			CALLQ_RM(MRSP_BO(StackPosition))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			CALLQ_RM(MRSP_DO(StackPosition))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
}