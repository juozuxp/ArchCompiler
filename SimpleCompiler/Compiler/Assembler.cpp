#include "Assembler.h"
#include "../Utilities/x86_x64Shell.h"
#include "CompileMap.h"

void Assembler::AssembleStart(CompileMap& Enviroment)
{
	CreateStackAlloc(Enviroment);
}

void Assembler::AssembleEnd(CompileMap& Enviroment)
{
	CreateStackDealloc(Enviroment);

	unsigned char Return[] =
	{
		RETN
	};

	Enviroment.AddCode(Return, sizeof(Return));
}

void Assembler::CreateStackAlloc(CompileMap& Enviroment)
{
	if (!EnvStackSize)
		return;

	if (EnvStackSize > 0x7F)
	{
		unsigned char Shell[] =
		{
			PFX_REXW, SUB_RM_D(LR(RSP), EnvStackSize)
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			PFX_REXW, SUBD_RM_B(LR(RSP), EnvStackSize)
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
}

void Assembler::CreateStackDealloc(CompileMap& Enviroment)
{
	if (!EnvStackSize)
		return;

	if (EnvStackSize > 0x7F)
	{
		unsigned char Shell[] =
		{
			PFX_REXW, ADD_RM_D(LR(RSP), EnvStackSize)
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			PFX_REXW, ADDD_RM_B(LR(RSP), EnvStackSize)
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
}