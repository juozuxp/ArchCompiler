#include "LocalVariable.h"
#include "../../Utilities/SimpleUtilities.h"
#include "../../Components/EnviromentMap.h"
#include "../../Components/CompileMap.h"
#include "../../Utilities/x86_x64Shell.h"

List<unsigned char> LocalVariable::CompileAssign()
{
	List<unsigned char> Compiled = List<unsigned char>(0);
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

			Compiled.Add(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				MOVB_RM_R(MRSP_BO_R(AL, StackPosition)),
			};

			Compiled.Add(Shell, sizeof(Shell));
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

			Compiled.Add(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_WORD, MOVD_RM_R(MRSP_BO_R(AX, StackPosition)),
			};

			Compiled.Add(Shell, sizeof(Shell));
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

			Compiled.Add(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				MOVD_RM_R(MRSP_BO_R(EAX, StackPosition)),
			};

			Compiled.Add(Shell, sizeof(Shell));
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

			Compiled.Add(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_RM_R(MRSP_BO_R(RAX, StackPosition)),
			};

			Compiled.Add(Shell, sizeof(Shell));
		}
	} break;
	}

	return Compiled;
}

List<unsigned char> LocalVariable::CompileRetrieve()
{
	List<unsigned char> Compiled = List<unsigned char>(0);
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

			Compiled.Add(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, XORD_RM_R(LR_R(RAX, RAX)),
				MOVB_R_RM(R_MRSP_DO(AL, StackPosition)),
			};

			Compiled.Add(Shell, sizeof(Shell));
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

			Compiled.Add(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, XORD_RM_R(LR_R(RAX, RAX)),
				PFX_WORD, MOVD_R_RM(R_MRSP_DO(AX, StackPosition)),
			};

			Compiled.Add(Shell, sizeof(Shell));
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

			Compiled.Add(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				MOVD_R_RM(R_MRSP_DO(EAX, StackPosition)),
			};

			Compiled.Add(Shell, sizeof(Shell));
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

			Compiled.Add(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_R_RM(R_MRSP_DO(RAX, StackPosition)),
			};

			Compiled.Add(Shell, sizeof(Shell));
		}
	} break;
	}

	return Compiled;
}

List<unsigned char> LocalVariable::Compile(CompileMap& Enviroment)
{
	StackPosition = Enviroment.AllocateLocalVariable(VariableSize);
	return List<unsigned char>();
}