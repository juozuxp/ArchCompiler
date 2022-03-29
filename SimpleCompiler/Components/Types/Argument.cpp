#include "Argument.h"
#include "../../Compiler/CompileMap.h"
#include "../../Utilities/x86_x64Shell.h"

void Argument::PreCompile(CompileMap& Enviroment)
{
}

void Argument::Compile(CompileMap& Enviroment)
{
	constexpr unsigned char Register[] =
	{
		RCX,
		RDX,
		R8,
		R9
	};

	StackPosition = Enviroment.GetCollectiveStack() + 0x8 * (Index + 1);
	if (Index < 2)
	{
		unsigned char Shell[] =
		{
			PFX_REXW, MOVD_RM_R(MRSP_BO_R(Register[Index], 0x8 * (Index + 1)))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
		return;
	}
	else if (Index < 4)
	{
		unsigned char Shell[] =
		{
			PFX_REXWR, MOVD_RM_R(MRSP_BO_R(Register[Index], 0x8 * (Index + 1)))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
		return;
	}
}