#include "AssignDynStack.h"
#include "../../Compiler/CompileMap.h"
#include "../../Utilities/x86_x64Shell.h"

void AssignDynStack::Compile(class CompileMap& Enviroment)
{
	if (LocationInStack == ~0)
		LocationInStack = Enviroment.AllocateLocalVariable(0x8);

	if (LocationInStack <= 0x7F)
	{
		unsigned char Shell[] =
		{
			PFX_REXW, MOVD_RM_R(MRSP_BO_R(RAX, LocationInStack))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
		return;
	}

	unsigned char Shell[] =
	{
		PFX_REXW, MOVD_RM_R(MRSP_DO_R(RAX, LocationInStack))
	};

	Enviroment.AddCode(Shell, sizeof(Shell));
}

void AssignDynStack::CompileRetrieve(class CompileMap& Enviroment)
{
	if (LocationInStack == ~0)
		LocationInStack = Enviroment.AllocateLocalVariable(0x8);

	if (LocationInStack <= 0x7F)
	{
		unsigned char Shell[] =
		{
			PFX_REXW, MOVD_R_RM(R_MRSP_BO(RAX, LocationInStack))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
		return;
	}

	unsigned char Shell[] =
	{
		PFX_REXW, MOVD_RM_R(R_MRSP_BO(RAX, LocationInStack))
	};

	Enviroment.AddCode(Shell, sizeof(Shell));
}