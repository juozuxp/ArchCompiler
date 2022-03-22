#include "FunctionCall.h"
#include "../../Compiler/Enviroments/EnviromentMap.h"
#include "../../Utilities/StrTok.h"
#include "../Transferable/Transferable.h"
#include "../../GlobalInfo/RegisterTypes.h"
#include "../Transferable/TransferRegister.h"
#include "../Transferable/TransferStack.h"
#include "Arithmetic.h"

void FunctionCall::Compile(class CompileMap& Enviroment)
{
	for (RefObject<Arithmetic> Argument : Arguments)
		Argument->Compile(Enviroment);

	Function->CompileCall(Enviroment);
}

unsigned long long FunctionCall::GetCallingStackSize()
{
	return (Arguments.GetCount() * 0x8) < 0x20 ? 0x20 : (Arguments.GetCount() * 0x8);
}

void FunctionCall::Parse(EnviromentMap& Enviroment, const char* Expression)
{
	const char* Opening;
	const char* Closing;

	Expression = Ignorables.Skip(Expression);

	Opening = strchr(Expression, '(');
	Closing = strrchr(Opening, ')');

	Function = Enviroment.GetVariable(Expression, Opening - Expression);
	for (char* Token : StrTok(Opening + 1, Closing - (Opening + 1), ","))
	{
		RefObject<Arithmetic> Argument;

		Argument = RefObject<Arithmetic>(Arithmetic());
		Argument->Parse(Enviroment, Token, GetAssignable(Arguments.GetCount()));

		Arguments.Add(Argument);
	}
}

bool FunctionCall::IsFunctionCall(const char* Expression)
{
	const char* Opening;

	Opening = strchr(Expression, '(');
	if (!Opening)
		return false;

	if (!strrchr(Opening, ')'))
		return false;

	if (strchr(Expression, '='))
		return false;

	return true;
}

RefObject<Transferable> FunctionCall::GetAssignable(unsigned long long Argument)
{
	if (Argument < 4)
	{
		constexpr RegisterType Registers[] = { RegisterType::RCX, RegisterType::RDX, RegisterType::R8, RegisterType::R9 };
		return RefObject<TransferRegister>(TransferRegister(Registers[Argument])).Cast<Transferable>();
	}

	return RefObject<TransferStack>(TransferStack(Argument * 0x8)).Cast<Transferable>();
}