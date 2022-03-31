#include "Subtraction.h"
#include "../../../Compiler/CompileMap.h"
#include "../../../Utilities/x86_x64Shell.h"

void Subtraction::Compile(CompileMap& Enviroment, RegisterType Source)
{
	Left->Compile(Enviroment, Source);
	Right->Compile(Enviroment, TransitionSpace);

	if (TransitionSpace.IsExtended())
	{
		if (Source.IsExtended())
		{
			unsigned char Operation[] =
			{
				PFX_REXWRB, SUBD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
		else
		{
			unsigned char Operation[] =
			{
				PFX_REXWB, SUBD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
	}
	else
	{
		if (Source.IsExtended())
		{
			unsigned char Operation[] =
			{
				PFX_REXWR, SUBD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
		else
		{
			unsigned char Operation[] =
			{
				PFX_REXW, SUBD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
	}
}

RefObject<Operand> Subtraction::CreateOperator(RefObject<Operand> First, RefObject<Operand> Second, RegisterType TransitionSpace)
{
	return RefObject<Subtraction>(Subtraction(First, Second, TransitionSpace)).Cast<Operand>();
}