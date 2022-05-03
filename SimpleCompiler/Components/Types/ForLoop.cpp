#include "ForLoop.h"
#include "LocalVariable.h"
#include "../Transferable/TransferRegister.h"
#include "../../Utilities/StrTok.h"
#include "../../Compiler/CompileMap.h"

#define SHELL_RELATIVITY MainRelativity

#include "../../Utilities/x86_x64Shell.h"


void ForLoop::PreCompile(CompileMap& Enviroment)
{
	PreLoop->PreCompile(Enviroment);
	Condition->PreCompile(Enviroment);
	ForEachCycle->PreCompile(Enviroment);

	LoopEnviroment->PreCompile(Enviroment);
}

void ForLoop::Compile(CompileMap& Enviroment)
{
	unsigned long JumpLocation;
	unsigned long MainRelativity;
	unsigned long ConditionLocation;

	PreLoop->Compile(Enviroment);

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
	ForEachCycle->Compile(Enviroment);

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

void ForLoop::PostCompile(class CompileMap& Enviroment)
{
	PreLoop->PostCompile(Enviroment);
	Condition->PostCompile(Enviroment);
	ForEachCycle->PostCompile(Enviroment);

	LoopEnviroment->PostCompile(Enviroment);
}

unsigned long long ForLoop::Parse(RefObject<EnviromentMap> Enviroment, const char* Expression)
{
	List<char> SubString;

	unsigned long long Length;

	unsigned char Stage;

	const char* StartFor;
	const char* EndFor;

	StartFor = strchr(Expression, '(');
	EndFor = Encapsulable.GetEncapEnd(StartFor) + 1;

	LoopEnviroment = RefObject<EnviromentMap>(EnviromentMap(Enviroment.Cast<::Enviroment>()));

	Stage = 0;
	for (const char* Token : StrTok(StartFor + 1, (EndFor - 1) - (StartFor + 1), ";", sizeof(";") - 1))
	{
		switch (Stage)
		{
		case 0:
		{
			if (Variable::IsVariable(Token))
			{
				PreLoop = RefObject<LocalVariable>(LocalVariable(Token)).Cast<TypeElement>();

				LoopEnviroment->AddVariableNoCompile(PreLoop.Cast<Variable>());

				PreLoop->Parse(LoopEnviroment, Token);

				break;
			}

			PreLoop = RefObject<Arithmetic>(Arithmetic()).Cast<TypeElement>();
			PreLoop->Parse(LoopEnviroment, Token);
		} break;
		case 1:
		{
			Condition = RefObject<Arithmetic>(Arithmetic());
			Condition->Parse(LoopEnviroment, Token, RefObject<TransferRegister>(TransferRegister(RegisterType::Type_RAX)).Cast<Transferable>());
		} break;
		case 2:
		{
			ForEachCycle = RefObject<Arithmetic>(Arithmetic());
			ForEachCycle->Parse(LoopEnviroment, Token);
		} break;
		}

		Stage++;
	}

	LoopEnviroment->Parse(Enviroment::ExtractSubEnviroment(EndFor, &Length), LoopEnviroment.Cast<::Enviroment>());

	return (EndFor - Expression) + Length;
}

bool ForLoop::IsExpression(const char* Expression)
{
	Expression = Ignorable.Skip(Expression);
	if (strncmp(Expression, CSL_PAIR("for")))
		return false;

	if (!Ignorable.IsSkippable(*(Expression + sizeof("for") - 1)) && *(Expression + sizeof("for") - 1) != '(')
		return false;

	if (!strchr(Expression, '('))
		return false;

	if (!strchr(Expression, ')'))
		return false;

	return true;
}

unsigned long ForLoop::ExpressionLength(const char* Expression)
{
	const char* StartFor;

	StartFor = strchr(Expression, '(');

	return (Encapsulable.GetEncapEnd(StartFor) + 1) - Expression;
}