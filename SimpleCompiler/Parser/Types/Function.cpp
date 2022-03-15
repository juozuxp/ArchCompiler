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
	unsigned long long StackSize;
	unsigned short RegisterMask;
	bool ShouldAlign;

	StackSize = this->Enviroment->EstimateStackSize();
	RegisterMask = this->Enviroment->EstimateRegisterUsage();

	StackSize = (StackSize + ((1 << 3) - 1)) & ~((1 << 3) - 1); // Stack alignment, making sure that it's 8 byte alligned

	ShouldAlign = true;
	for (unsigned short i = 0; i < 16; i++)
	{
		if (RegisterMask & (1 << i))
			ShouldAlign != ShouldAlign;
	}

	if (ShouldAlign)
		StackSize |= (1 << 3); // Stack alignment, making sure the 16 byte missalignment is fixed

	Enviroment.SetStack(StackSize);

	CreateEntry(Enviroment, RegisterMask);
	this->Enviroment->Compile(Enviroment);
	CreateExit(Enviroment, RegisterMask);
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

void Function::CompileRetrieve(CompileMap& Enviroment, RegisterType Source)
{
	unsigned long long MainRelativity;

	if (Source.IsExtended())
	{
		MainRelativity = 0;
		unsigned char Shell[] =
		{
			PFX_REXWR, LEAD_R_M(R_REL_DO(Source, this->Enviroment->RelativeLocation - (Enviroment.GetRelativeLocation() + MainRelativity)))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
	else
	{
		MainRelativity = 0;
		unsigned char Shell[] =
		{
			PFX_REXW, LEAD_R_M(R_REL_DO(Source, this->Enviroment->RelativeLocation - (Enviroment.GetRelativeLocation() + MainRelativity)))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
}

void Function::CompileRegisterBackups(class CompileMap& Enviroment, unsigned short Mask)
{
	unsigned long long MainRelativity;

	MainRelativity = 0;
	for (unsigned short i = 0; i < 16; i++)
	{
		if (!(Mask & (1 << i)))
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

void Function::CompileRegisterRestores(class CompileMap& Enviroment, unsigned short Mask)
{
	unsigned long long MainRelativity;

	MainRelativity = 0;
	for (unsigned short i = 15;; i--)
	{
		if (!(Mask & (1 << i)))
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

void Function::CreateEntry(CompileMap& Enviroment, unsigned short RegisterMask)
{
	unsigned long long MainRelativity;

	CompileRegisterBackups(Enviroment, RegisterMask);

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

void Function::CreateExit(CompileMap& Enviroment, unsigned short RegisterMask)
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

	CompileRegisterRestores(Enviroment, RegisterMask);
	Enviroment.AddCode(RETN);
}