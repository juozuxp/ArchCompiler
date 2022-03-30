#include "WhileLoop.h"
#include "../../Compiler/CompileMap.h"
#include "../Transferable/TransferRegister.h"

#define SHELL_RELATIVITY MainRelativity

#include "../../Utilities/x86_x64Shell.h"

void WhileLoop::PreCompile(CompileMap& Enviroment)
{
	Condition->PreCompile(Enviroment);
	LoopEnviroment->PreCompile(Enviroment);
}

void WhileLoop::Compile(CompileMap& Enviroment)
{
	unsigned long JumpLocation;
	unsigned long MainRelativity;
	unsigned long ConditionLocation;

	ConditionLocation = Enviroment.GetCodeLocation();

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

	LoopEnviroment->Compile(Enviroment);

	MainRelativity = 0;
	unsigned char JumpToCondition[] =
	{
		JMP_RD(ConditionLocation - (Enviroment.GetCodeLocation() + MainRelativity))
	};

	Enviroment.AddCode(JumpToCondition, sizeof(JumpToCondition));

	MainRelativity = 0;
	unsigned char JumpPatch[] =
	{
		JE_RD(Enviroment.GetCodeLocation() - (JumpLocation + MainRelativity))
	};

	Enviroment.PatchCode(JumpLocation, JumpPatch, sizeof(JumpPatch));
}

#undef RAX

unsigned long long WhileLoop::Parse(RefObject<EnviromentMap> Enviroment, const char* Expression)
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

	LoopEnviroment = RefObject<EnviromentMap>(EnviromentMap(Enviroment.Cast<::Enviroment>()));
	LoopEnviroment->Parse(Enviroment::ExtractSubEnviroment(EndIf, &Length), LoopEnviroment.Cast<::Enviroment>());

	return (EndIf - Expression) + Length;
}

bool WhileLoop::IsWhileLoop(const char* Expression)
{
	Expression = Ignorable.Skip(Expression);
	if (strncmp(Expression, CSL_PAIR("while")))
		return false;

	if (!Ignorable.IsSkippable(*(Expression + sizeof("while") - 1)) && *(Expression + sizeof("while") - 1) != '(')
		return false;

	if (!strchr(Expression, '('))
		return false;

	if (!strchr(Expression, ')'))
		return false;

	return true;
}