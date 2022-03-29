#include "Conditional.h"
#include <string.h>
#include "../Enviroments/Enviroment.h"
#include "../Transferable/TransferRegister.h"
#include "../Enviroments/EnviromentMap.h"
#include "../../Compiler/CompileMap.h"

#define SHELL_RELATIVITY MainRelativity

#include "../../Utilities/x86_x64Shell.h"

void Conditional::PreCompile(CompileMap& Enviroment)
{
	Condition->PreCompile(Enviroment);
}

void Conditional::Compile(CompileMap& Enviroment)
{
	unsigned long JumpLocation;
	unsigned long MainRelativity;

	Condition->Compile(Enviroment);

	JumpLocation = 0;
	MainRelativity = 0;
	unsigned char Conditional[] =
	{
		PFX_REXW, TESTD_RM_R(LR_R(RAX, RAX)),
		R_CP(JumpLocation, JE_RD(0))
	};

	JumpLocation += Enviroment.GetCodeLocation();
	Enviroment.AddCode(Conditional, sizeof(Conditional));

	SubEnviroment->Compile(Enviroment);

	MainRelativity = 0;
	unsigned char JumpPatch[] =
	{
		JE_RD(Enviroment.GetCodeLocation() - (JumpLocation + MainRelativity))
	};

	Enviroment.PatchCode(JumpLocation, JumpPatch, sizeof(JumpPatch));
}

#undef RAX

unsigned long long Conditional::Parse(RefObject<EnviromentMap> Enviroment, const char* Expression)
{
	List<char> SubString;

	unsigned long long Length;

	const char* StartIf;
	const char* EndIf;

	StartIf = strchr(Expression, '(');
	EndIf = Encapsulable.GetEncapEnd(StartIf) + 1;

	SubString.Add(StartIf + 1, EndIf - StartIf - 2);
	SubString.Add('\0');

	Condition = RefObject<Arithmetic>(Arithmetic());
	Condition->Parse(Enviroment, SubString, RefObject<TransferRegister>(TransferRegister(RegisterType::RAX)).Cast<Transferable>());

	SubEnviroment = RefObject<EnviromentMap>(EnviromentMap(Enviroment.Cast<::Enviroment>()));
	SubEnviroment->Parse(Enviroment::ExtractSubEnviroment(EndIf, &Length), SubEnviroment.Cast<::Enviroment>());

	return (EndIf - Expression) + Length;
}

bool Conditional::IsConditional(const char* Expression)
{
	Expression = Ignorable.Skip(Expression);
	if (strncmp(Expression, "if", sizeof("if") - 1))
		return false;

	if (!Ignorable.IsSkippable(*(Expression + sizeof("if") - 1)))
		return false;

	if (!strchr(Expression, '('))
		return false;

	if (!strchr(Expression, ')'))
		return false;

	return true;
}