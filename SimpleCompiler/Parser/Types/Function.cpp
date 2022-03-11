#include "Function.h"
#include "../../GlobalInfo/VariableTypes.h"
#include "../../Utilities/StrTok.h"
#include "../../Compiler/Enviroments/EnviromentMap.h"
#include "../../Compiler/CompileMap.h"
#include "Argument.h"

#define SHELL_RELATIVITY MainRelativity
#include "../../Utilities/x86_x64Shell.h"

Function::Function(const char* Expression) : Variable(Expression)
{
	ExtractArguments(Expression);
}

void Function::ExtractArguments(const char* Expression)
{
	List<char> IsolateExpression;
	const char* LocatedEnd;

	Expression = strstr(Expression, "(") + 1;
	if (!Expression)
		return;

	LocatedEnd = strstr(Expression, ")");
	if (!LocatedEnd)
		return;

	IsolateExpression.Add(Expression, LocatedEnd - Expression);
	IsolateExpression.Add('\0');

	for (char* Token : StrTok(IsolateExpression, ","))
		Arguments.Add(RefObject<Argument>(Argument(Token, Arguments.GetCount())));
}

void Function::BindEnviroment(RefObject<EnviromentMap> Enviroment)
{
	this->Enviroment = Enviroment;
	for (RefObject<Argument> Argument : Arguments)
		Enviroment->AddVariableNoCompile(Argument.Cast<Variable>());
}

void Function::Compile(CompileMap& Enviroment)
{
	Enviroment.SetStack(this->Enviroment->EstimateStackSize());

	CreateEntry(Enviroment);
	this->Enviroment->Compile(Enviroment);
	CreateExit(Enviroment);
}

bool Function::IsFunctionDefinition(const char* Expression)
{
	const VariableType* Type = VariableTypes::RetrieveType(Expression);
	if (!Type)
		return false;

	for (Expression += strlen(Type->GetName()); IsIgnorable(*Expression); Expression++);
	for (; *Expression && !IsIgnorable(*Expression); Expression++)
	{
		if (*Expression == '(')
			return true;
	}

	return false;
}

unsigned long long Function::GetDefinitionLength(const char* Expression)
{
	for (unsigned long long i = 0; *Expression; Expression++, i++)
	{
		if (*Expression == ')')
			return i + 1;
	}

	return 0;
}

void Function::CompileCall(CompileMap& Enviroment)
{
	unsigned long long MainRelativity;

	MainRelativity = 0;
	unsigned char Shell[] =
	{
		CALL_RD(this->Enviroment->RelativeLocation - (Enviroment.GetRelativeLocation() + MainRelativity))
	};

	Enviroment.AddCode(Shell, sizeof(Shell));
}

void Function::CreateEntry(CompileMap& Enviroment)
{
	unsigned long long MainRelativity;

	for (RefObject<Argument> Argument : Arguments)
		Argument->Compile(Enviroment);

	MainRelativity = 0;
	if (Enviroment.GetStackSize() > 0x7F)
	{
		unsigned char Shell[] =
		{
			PFX_REXW, SUB_RM_D(LR(RSP), Enviroment.GetStackSize())
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			PFX_REXW, SUBD_RM_B(LR(RSP), Enviroment.GetStackSize())
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
}

void Function::CreateExit(CompileMap& Enviroment)
{
	unsigned long long MainRelativity;

	MainRelativity = 0;
	if (Enviroment.GetStackSize() > 0x7F)
	{
		unsigned char Shell[] =
		{
			PFX_REXW, ADD_RM_D(LR(RSP), Enviroment.GetStackSize()),
			RETN
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			PFX_REXW, ADDD_RM_B(LR(RSP), Enviroment.GetStackSize()),
			RETN
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
}