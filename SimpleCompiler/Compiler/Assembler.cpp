#include "Assembler.h"
#include "../Utilities/x86_x64Shell.h"

List<unsigned char> Assembler::AssembleStart()
{
	return CreateStackAlloc();
}

List<unsigned char> Assembler::AssembleEnd()
{
	List<unsigned char> Code = CreateStackDealloc();

	unsigned char Return[] =
	{
		RETN
	};

	Code.Add(Return, sizeof(Return));
	return Code;
}

List<unsigned char> Assembler::CreateStackAlloc()
{
	List<unsigned char> Stacker = List<unsigned char>(0);

	if (!EnvStackSize)
		return Stacker;

	if (EnvStackSize > 0x7F)
	{
		unsigned char Shell[] =
		{
			PFX_REXW, SUB_RM_D(LR(RSP), EnvStackSize)
		};

		Stacker.Add(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			PFX_REXW, SUBD_RM_B(LR(RSP), EnvStackSize)
		};

		Stacker.Add(Shell, sizeof(Shell));
	}

	return Stacker;
}

List<unsigned char> Assembler::CreateStackDealloc()
{
	List<unsigned char> Stacker = List<unsigned char>(0);

	if (!EnvStackSize)
		return Stacker;

	if (EnvStackSize > 0x7F)
	{
		unsigned char Shell[] =
		{
			PFX_REXW, ADD_RM_D(LR(RSP), EnvStackSize)
		};

		Stacker.Add(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			PFX_REXW, ADDD_RM_B(LR(RSP), EnvStackSize)
		};

		Stacker.Add(Shell, sizeof(Shell));
	}

	return Stacker;
}