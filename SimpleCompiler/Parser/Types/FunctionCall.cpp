#include "FunctionCall.h"
#include "../../Compiler/Enviroments/EnviromentMap.h"
#include "../../Utilities/StrTok.h"
#include "../Assignables/Assignable.h"
#include "../../GlobalInfo/RegisterTypes.h"
#include "../Assignables/AssignRegister.h"
#include "../Assignables/AssignStack.h"
#include "Arithmetic.h"

void FunctionCall::Compile(class CompileMap& Enviroment)
{
	for (RefObject<Arithmetic> Argument : Arguments)
		Argument->Compile(Enviroment);

	Function->CompileCall(Enviroment);
}

void FunctionCall::Parse(EnviromentMap& Enviroment, const char* Expression)
{
	const char* Opening;
	const char* Closing;

	for (; *Expression; Expression++)
	{
		if (!IsIgnorable(*Expression))
			break;
	}

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

RefObject<Assignable> FunctionCall::GetAssignable(unsigned long long Argument)
{
	if (Argument < 4)
	{
		constexpr RegisterType Registers[] = { RegisterType_RCX, RegisterType_RDX, RegisterType_R8, RegisterType_R9 };
		return RefObject<AssignRegister>(AssignRegister(Registers[Argument])).Cast<Assignable>();
	}

	return RefObject<AssignStack>(AssignStack(Argument * 0x8)).Cast<Assignable>();
}