#include "AssignStack.h"
#include "../../Compiler/CompileMap.h"
#include "../../Utilities/x86_x64Shell.h"

void AssignStack::Compile(CompileMap& Enviroment)
{
	if (StackLocation <= 0x7F)
	{
		unsigned char Shell[] =
		{
			PFX_REXW, MOVD_RM_R(MRSP_BO_R(RAX, StackLocation))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
		return;
	}

	unsigned char Shell[] =
	{
		PFX_REXW, MOVD_RM_R(MRSP_DO_R(RAX, StackLocation))
	};

	Enviroment.AddCode(Shell, sizeof(Shell));
}