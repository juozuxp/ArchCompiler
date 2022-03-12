#include "LocalVariable.h"
#include "../../Utilities/SimpleUtilities.h"
#include "../../Compiler/Enviroments/EnviromentMap.h"
#include "../../Compiler/CompileMap.h"
#include "Arithmetic.h"
#include "../../Utilities/x86_x64Shell.h"

void LocalVariable::CompileAssign(CompileMap& Enviroment)
{
	switch (VariableSize)
	{
	case 1:
	{
		if (StackPosition < 0x7F)
		{
			unsigned char Shell[] =
			{
				MOVB_RM_R(MRSP_BO_R(AL, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				MOVB_RM_R(MRSP_BO_R(AL, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	case 2:
	{
		if (StackPosition < 0x7F)
		{
			unsigned char Shell[] =
			{
				PFX_WORD, MOVD_RM_R(MRSP_BO_R(AX, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_WORD, MOVD_RM_R(MRSP_BO_R(AX, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	case 4:
	{
		if (StackPosition < 0x7F)
		{
			unsigned char Shell[] =
			{
				MOVD_RM_R(MRSP_BO_R(EAX, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				MOVD_RM_R(MRSP_BO_R(EAX, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	case 8:
	{
		if (StackPosition < 0x7F)
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_RM_R(MRSP_BO_R(RAX, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_RM_R(MRSP_BO_R(RAX, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	}
}

void LocalVariable::CompileRetrieve(CompileMap& Enviroment)
{
	switch (VariableSize)
	{
	case 1:
	{
		if (StackPosition < 0x7F)
		{
			unsigned char Shell[] =
			{
				PFX_REXW, XORD_RM_R(LR_R(RAX, RAX)),
				MOVB_R_RM(R_MRSP_BO(AL, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, XORD_RM_R(LR_R(RAX, RAX)),
				MOVB_R_RM(R_MRSP_DO(AL, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	case 2:
	{
		if (StackPosition < 0x7F)
		{
			unsigned char Shell[] =
			{
				PFX_REXW, XORD_RM_R(LR_R(RAX, RAX)),
				PFX_WORD, MOVD_R_RM(R_MRSP_BO(AX, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, XORD_RM_R(LR_R(RAX, RAX)),
				PFX_WORD, MOVD_R_RM(R_MRSP_DO(AX, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	case 4:
	{
		if (StackPosition < 0x7F)
		{
			unsigned char Shell[] =
			{
				MOVD_R_RM(R_MRSP_BO(EAX, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				MOVD_R_RM(R_MRSP_DO(EAX, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	case 8:
	{
		if (StackPosition < 0x7F)
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_R_RM(R_MRSP_BO(RAX, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_R_RM(R_MRSP_DO(RAX, StackPosition)),
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	}
}

void LocalVariable::Compile(CompileMap& Enviroment)
{
	StackPosition = Enviroment.AllocateLocalVariable(VariableSize);
	if (this->Assigner)
		this->Assigner->Compile(Enviroment);
}