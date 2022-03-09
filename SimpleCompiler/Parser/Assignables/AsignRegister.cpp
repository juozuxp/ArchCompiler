#include "AsignRegister.h"

List<unsigned char> AsignRegister::Compile(class CompileMap& Enviroment)
{
	if (Register == RegisterType_RAX)
		return List<unsigned char>();

	List<unsigned char> Compiled = List<unsigned char>(0);
	if (Register & RegisterType_x64Extend)
	{
		unsigned char Shell[] =
		{
			PFX_REXWB, MOVD_RM_R(LR_R(Register & (RegisterType_x64Extend - 1), RAX))
		};

		Compiled.Add(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			PFX_REXW, MOVD_RM_R(LR_R(Register, RAX))
		};

		Compiled.Add(Shell, sizeof(Shell));
	}

	return Compiled;
}