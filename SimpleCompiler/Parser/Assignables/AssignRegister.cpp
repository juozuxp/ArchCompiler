#include "AssignRegister.h"
#include "../../Compiler/CompileMap.h"
#include "../../Utilities/x86_x64Shell.h"

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

void AssignRegister::CompileRetrieve(CompileMap& Enviroment)
{
	if (Register == RegisterType_RAX)
		return;

	if (Register & RegisterType_x64Extend)
	{
		unsigned char Shell[] =
		{
			PFX_REXWR, MOVD_RM_R(LR_R(RAX, Register & (RegisterType_x64Extend - 1)))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			PFX_REXW, MOVD_RM_R(LR_R(RAX, Register))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
}