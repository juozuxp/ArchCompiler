#include "TransferFunction.h"
#include "../../GlobalInfo/RegisterTypes.h"
#include "../../Compiler/CompileMap.h"
#include "../../Utilities/x86_x64Shell.h"
#include "../Enviroments/EnviromentMap.h"

TransferFunction::TransferFunction(RefObject<EnviromentMap> Enviroment, const char* Expression)
{
	CallObject = RefObject<FunctionCall>(FunctionCall());
	CallObject->Parse(Enviroment, Expression);
}

unsigned long TransferFunction::GetReferenceMultiplier(long long Reference)
{
	return 0;
}

void TransferFunction::PreCompile(CompileMap& Enviroment, RegisterType Source)
{
	CallObject->PreCompile(Enviroment);
}

void TransferFunction::PostCompile(CompileMap& Enviroment, RegisterType Source)
{
	CallObject->PostCompile(Enviroment);
}

void TransferFunction::CompileRetrieve(CompileMap& Enviroment, RegisterType Source)
{
	CallObject->Compile(Enviroment); // We simply compile this thing, since it's end product will endup in RAX naturally

	if (Source == RegisterType::Type_RAX)
		return;

	if (Source.IsExtended())
	{
		unsigned char Shell[] =
		{
			PFX_REXWB, MOVD_RM_R(LR_R(Source, RAX))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			PFX_REXW, MOVD_RM_R(LR_R(Source, RAX))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
}