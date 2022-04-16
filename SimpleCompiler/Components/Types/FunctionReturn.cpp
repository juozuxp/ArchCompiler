#include "FunctionReturn.h"
#include "../../Utilities/SimpleUtilities.h"
#include "Arithmetic.h"
#include "../Transferable/TransferRegister.h"
#include "../../GlobalInfo/RegisterTypes.h"
#include "../Enviroments/EnviromentMap.h"
#include "../../Compiler/CompileMap.h"

#define SHELL_RELATIVITY MainRelativity
#include "../../Utilities/x86_x64Shell.h"

void FunctionReturn::PreCompile(CompileMap& Enviroment)
{
	if (Return)
		Return->PreCompile(Enviroment);
}

void FunctionReturn::Compile(CompileMap& Enviroment)
{
	unsigned long MainRelativity;
	
	if (Return)
		Return->Compile(Enviroment);

	if (!Host)
		return;

	MainRelativity = 0;
	unsigned char Jump[] =
	{
		JMP_RD(0)
	};

	AllocatedJump = Enviroment.GetCodeLocation();
	Enviroment.AddCode(Jump, sizeof(Jump));
}

void FunctionReturn::PostCompile(CompileMap& Enviroment)
{
	unsigned long MainRelativity;
	if (Return)
		Return->PostCompile(Enviroment);

	if (!Host)
		return;

	MainRelativity = 0;
	unsigned char Jump[] =
	{
		JMP_RD((Host->GetEnviromentEntry() + Host->GetEnviromentSize()) - (AllocatedJump + MainRelativity))
	};

	Enviroment.PatchCode(AllocatedJump, Jump, sizeof(Jump));
}

#undef RAX

unsigned long long FunctionReturn::Parse(RefObject<EnviromentMap> Enviroment, const char* Expression)
{
	Expression = Ignorables.Skip(Expression);
	Expression += sizeof("return") - 1;
	Expression = Ignorables.Skip(Expression);

	Host = Enviroment->GetBaseEnviroment();

	if (*Expression)
	{
		Return = RefObject<Arithmetic>(Arithmetic());
		Return->Parse(Enviroment, Expression, RefObject<TransferRegister>(TransferRegister(RegisterType::Type_RAX)).Cast<Transferable>());
	}

	return 0;
}

bool FunctionReturn::IsExpression(const char* Expression)
{
	if (strncmp(Expression, CSL_PAIR("return")))
		return false;

	if (!Ignorables.IsSkippable(*(Expression + (sizeof("return") - 1))) && *(Expression + (sizeof("return") - 1)))
		return false;

	return true;
}