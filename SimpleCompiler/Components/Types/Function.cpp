#include "Function.h"
#include "../../GlobalInfo/VariableTypes.h"
#include "../../Utilities/StrTok.h"
#include "../Enviroments/EnviromentMap.h"
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

void Function::PreCompile(CompileMap& Enviroment)
{
	this->Enviroment->PreCompile(Enviroment);
	for (RefObject<Argument> Argument : Arguments)
		Argument->PreCompile(Enviroment);
}

void Function::Compile(CompileMap& Enviroment)
{
	RelativeLocation = Enviroment.GetCodeLocation();

	CompileEntry(Enviroment);

	this->Enviroment->Compile(Enviroment);

	CompileExit(Enviroment);
}

void Function::PostCompile(CompileMap& Enviroment)
{
	this->Enviroment->PostCompile(Enviroment);
}

bool Function::IsFunctionDefinition(const char* Expression)
{
	const VariableType* Type = VariableTypes::RetrieveType(Expression);
	if (!Type)
		return false;

	Expression = Ignorable.Skip(Expression + strlen(Type->GetName()));
	for (; *Expression && !Ignorable.IsSkippable(*Expression); Expression++)
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
		CALL_RD(RelativeLocation - (Enviroment.GetCodeLocation() + MainRelativity))
	};

	Enviroment.AddCode(Shell, sizeof(Shell));
}

void Function::CompileRetrieve(CompileMap& Enviroment, RegisterType Source)
{
	unsigned long long MainRelativity;

	if (Source.IsExtended())
	{
		MainRelativity = 0;
		unsigned char Shell[] =
		{
			PFX_REXWR, LEAD_R_M(R_REL_DO(Source, RelativeLocation - (Enviroment.GetCodeLocation() + MainRelativity)))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
	else
	{
		MainRelativity = 0;
		unsigned char Shell[] =
		{
			PFX_REXW, LEAD_R_M(R_REL_DO(Source, RelativeLocation - (Enviroment.GetCodeLocation() + MainRelativity)))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
}

void Function::CompileRegisterBackups(CompileMap& Enviroment)
{
	unsigned long long MainRelativity;

	MainRelativity = 0;
	for (unsigned short i = 0; i < 16; i++)
	{
		if (!(Enviroment.GetRegisterMask() & (1 << i)))
			continue;

		if (i & (1 << 3))
		{
			unsigned char Shell[] =
			{
				PFX_REXB, PUSHQ_R(i & ((1 << 3) - 1))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
			continue;
		}

		unsigned char Shell[] =
		{
			PUSHQ_R(i)
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
}

void Function::CompileRegisterRestores(CompileMap& Enviroment)
{
	unsigned long long MainRelativity;

	MainRelativity = 0;
	for (unsigned short i = 15;; i--)
	{
		if (!(Enviroment.GetRegisterMask() & (1 << i)))
		{
			if (i == 0)
				break;

			continue;
		}

		if (i & (1 << 3))
		{
			unsigned char Shell[] =
			{
				PFX_REXB, POPQ_R(i & ((1 << 3) - 1))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				POPQ_R(i)
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}

		if (i == 0)
			break;
	}
}

void Function::CompileEntry(CompileMap& Enviroment)
{
	unsigned long long MainRelativity;

	for (RefObject<Argument> Argument : Arguments)
		Argument->Compile(Enviroment);

	CompileRegisterBackups(Enviroment);

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

void Function::CompileExit(CompileMap& Enviroment)
{
	unsigned long long MainRelativity;

	MainRelativity = 0;
	if (Enviroment.GetStackSize() > 0x7F)
	{
		unsigned char Shell[] =
		{
			PFX_REXW, ADD_RM_D(LR(RSP), Enviroment.GetStackSize())
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			PFX_REXW, ADDD_RM_B(LR(RSP), Enviroment.GetStackSize())
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}

	CompileRegisterRestores(Enviroment);
	Enviroment.AddCode(RETN);
}