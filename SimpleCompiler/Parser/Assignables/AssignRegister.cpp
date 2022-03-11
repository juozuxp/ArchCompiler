#include "AssignRegister.h"
#include "../../Compiler/CompileMap.h"

void AssignRegister::Compile(CompileMap& Enviroment)
{
	if (Register == RegisterType_RAX)
		return;

	if (Register & RegisterType_x64Extend)
	{
		unsigned char Shell[] =
		{
			PFX_REXWB, MOVD_RM_R(LR_R(Register & (RegisterType_x64Extend - 1), RAX))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			PFX_REXW, MOVD_RM_R(LR_R(Register, RAX))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
}