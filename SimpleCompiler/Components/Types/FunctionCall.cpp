#include "FunctionCall.h"
#include "../Enviroments/EnviromentMap.h"
#include "../../Utilities/StrTok.h"
#include "../Transferable/Transferable.h"
#include "../../GlobalInfo/RegisterTypes.h"
#include "../Transferable/TransferRegister.h"
#include "../Transferable/TransferStack.h"
#include "../../Compiler/CompileMap.h"
#include "Arithmetic.h"

void FunctionCall::Compile(CompileMap& Enviroment)
{
	for (RefObject<Arithmetic> Argument : Arguments)
		Argument->Compile(Enviroment);

	Function->CompileCall(Enviroment);
}

void FunctionCall::PreCompile(CompileMap& Enviroment)
{
	for (RefObject<Arithmetic> Argument : Arguments)
		Argument->PreCompile(Enviroment);

	Enviroment.AllocTempStack((Arguments.GetCount() * 0x8) < 0x20 ? 0x20 : (Arguments.GetCount() * 0x8));
}

void FunctionCall::PostCompile(CompileMap& Enviroment)
{
	for (RefObject<Arithmetic> Argument : Arguments)
		Argument->PostCompile(Enviroment);
}

unsigned long long FunctionCall::Parse(RefObject<EnviromentMap> Enviroment, const char* Expression)
{
	const char* Opening;
	const char* Closing;

	Expression = Ignorables.Skip(Expression);

	Opening = strchr(Expression, '(');
	Closing = Encapsule.GetEncapEnd(Opening);

	Function = Enviroment->GetVariable(Expression, Opening - Expression);
	for (char* Token : StrTok(Opening + 1, Closing - (Opening + 1), ","))
	{
		RefObject<Arithmetic> Argument;

		Argument = RefObject<Arithmetic>(Arithmetic());
		Argument->Parse(Enviroment, Token, GetTranferable(Arguments.GetCount()));

		Arguments.Add(Argument);
	}

	return 0;
}

bool FunctionCall::IsFunctionCall(const char* Expression)
{
	const char* Opening;

	Opening = strchr(Expression, '(');
	if (!Opening)
		return false;

	if (!strchr(Opening, ')'))
		return false;

	if (strchr(Expression, '='))
		return false;

	return true;
}

RefObject<Transferable> FunctionCall::GetTranferable(unsigned long long Argument)
{
	if (Argument < 4)
	{
		constexpr RegisterType Registers[] = { RegisterType::Type_RCX, RegisterType::Type_RDX, RegisterType::Type_R8, RegisterType::Type_R9 };
		return RefObject<TransferRegister>(TransferRegister(Registers[Argument])).Cast<Transferable>();
	}

	return RefObject<TransferStack>(TransferStack(Argument * 0x8)).Cast<Transferable>();
}