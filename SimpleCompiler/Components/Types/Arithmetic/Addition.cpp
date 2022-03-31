#include "Addition.h"
#include "../../../Compiler/CompileMap.h"
#include "../../../Compiler/TempVariableMap.h"
#include "../../../Utilities/x86_x64Shell.h"

void Addition::Compile(CompileMap& Enviroment, RegisterType Source)
{
	Left->Compile(Enviroment, Source);
	Right->Compile(Enviroment, TransitionSpace);

	if (TransitionSpace.IsExtended())
	{
		if (Source.IsExtended())
		{
			unsigned char Operation[] =
			{
				PFX_REXWRB, ADDD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
		else
		{
			unsigned char Operation[] =
			{
				PFX_REXWB, ADDD_R_RM(R_LR(Source, TransitionSpace)),
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
				PFX_REXWR, ADDD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
		else
		{
			unsigned char Operation[] =
			{
				PFX_REXW, ADDD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
	}
}

RefObject<Operand> Addition::CreateOperator(RefObject<Operand> First, RefObject<Operand> Second, RegisterType TransitionSpace)
{
	return RefObject<Addition>(Addition(First, Second, TransitionSpace)).Cast<Operand>();
}