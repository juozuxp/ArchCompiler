#include "Arithmetic.h"
#include "../../Components/EnviromentMap.h"
#include "../../Components/CompileMap.h"
#include "../../Utilities/x86_x64Shell.h"
#include "Variable.h"
#include "../Assignables/AsignVariable.h"

List<unsigned char> Arithmetic::Value::Compile(class CompileMap& Enviroment)
{
	List<unsigned char> Compiled = List<unsigned char>(0);
	if (Definition < 0xFF)
	{
		if (Definition == 0)
		{
			unsigned char Shell[] =
			{
				PFX_REXW, XORD_RM_R(LR_R(EAX, EAX), Definition)
			};

			Compiled.Add(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, XORD_RM_R(LR_R(RAX, RAX), Definition),
				MOV_R_B(AL, Definition)
			};

			Compiled.Add(Shell, sizeof(Shell));
		}

		return Compiled;
	}


	if (Definition < 0xFFFF)
	{
		unsigned char Shell[] =
		{
			PFX_REXW, XORD_RM_R(LR_R(RAX, RAX), Definition), // clear the value, fuck knows why it's made like this but it will only clear RAX when it gets overwritten with a value bigger than or equal to 4 bytes
			MOV_R_W(AX, Definition)
		};

		Compiled.Add(Shell, sizeof(Shell));

		return Compiled;
	}


	if (Definition < 0xFFFFFFFF)
	{
		unsigned char Shell[] =
		{
			MOV_R_D(EAX, Definition)
		};

		Compiled.Add(Shell, sizeof(Shell));

		return Compiled;
	}

	unsigned char Shell[] =
	{
		MOV_R_Q(RAX, Definition)
	};

	Compiled.Add(Shell, sizeof(Shell));

	return Compiled;
}

List<unsigned char> Arithmetic::Addition::Compile(class CompileMap& Enviroment)
{
	List<unsigned char> Compiled = List<unsigned char>(0);

	Compiled.Add(Left->Compile(Enviroment));
	
	unsigned char Preserve[] =
	{
		PFX_REXW, MOVD_R_RM(R_LR(RCX, RAX))
	};

	Compiled.Add(Preserve, sizeof(Preserve));

	Compiled.Add(Right->Compile(Enviroment));

	unsigned char Operation[] =
	{
		PFX_REXW, ADDD_R_RM(R_LR(RAX, RCX))
	};

	Compiled.Add(Operation, sizeof(Operation));

	return Compiled;
}

List<unsigned char> Arithmetic::Subtraction::Compile(class CompileMap& Enviroment)
{
	List<unsigned char> Compiled = List<unsigned char>(0);

	Compiled.Add(Left->Compile(Enviroment));

	unsigned char Preserve[] =
	{
		PFX_REXW, MOVD_R_RM(R_LR(RCX, RAX))
	};

	Compiled.Add(Preserve, sizeof(Preserve));

	Compiled.Add(Right->Compile(Enviroment));

	unsigned char Operation[] =
	{
		PFX_REXW, SUBD_R_RM(R_LR(RCX, RAX)),
		PFX_REXW, MOVD_R_RM(R_LR(RAX, RCX))
	};

	Compiled.Add(Operation, sizeof(Operation));

	return Compiled;
}

List<unsigned char> Arithmetic::AVariable::Compile(class CompileMap& Enviroment)
{
	return Origin->CompileRetrieve();
}

void Arithmetic::Parse(EnviromentMap& Enviroment, const char* Expression)
{
	List<char> Deflate = Deflater.Deflate(Expression);

	unsigned long long EqualsIdx = 0;
	for (; EqualsIdx < Deflate.GetCount(); EqualsIdx++)
	{
		if (Deflate[EqualsIdx] == '=')
			break;
	}

	AssignTo = RefObject<AsignVariable>(Enviroment.GetVariable(Deflate, EqualsIdx)).Cast<Assignable>();

	EvaluateArthmetic(Enviroment, Deflate + EqualsIdx + 1);
}

bool Arithmetic::IsArtimetic(const char* Expression)
{
	for (; *Expression; Expression++)
	{
		if (*Expression == '=')
			return true;
	}

	if (LocateOperation(Expression, 0))
		return true;

	return false;
}

List<unsigned char> Arithmetic::Compile(CompileMap& Enviroment)
{
	List<unsigned char> Compiled = Origin->Compile(Enviroment);

	Compiled.Add(AssignTo->Compile(Enviroment));

	return Compiled;
}

const char* Arithmetic::LocateOperation(const char* Expression, const OperationDef** OperationDescription)
{
	for (; *Expression; Expression++)
	{
		for (unsigned long long i = 0; i < ARRAY_COUNT(Operations); i++)
		{
			if (Operations[i].IsOperation(*Expression))
			{
				if (OperationDescription)
					*OperationDescription = &Operations[i];

				return Expression;
			}
		}
	}

	return 0;
}

void Arithmetic::EvaluateArthmetic(EnviromentMap& Enviroment, const char* Expression)
{
	const OperationDef* OperationType;

	RefObject<Operand> First;
	RefObject<Operand> Second;

	const char* LocOperation = LocateOperation(Expression, &OperationType);
	if (IS_NUMBER(Expression))
		First = RefObject<Value>(Value(strtoull(Expression, 0, 10))).Cast<Operand>();
	else
	{
		unsigned long long Length = 0;
		if (LocOperation)
			Length = LocOperation - Expression;

		First = RefObject<AVariable>(AVariable(Enviroment.GetVariable(Expression, Length))).Cast<Operand>();
	}

	if (!LocOperation)
	{
		Origin = First;
		return;
	}

	Expression = LocOperation + 1;
	while (true)
	{
		const OperationDef* NextOperation;

		LocOperation = LocateOperation(Expression, &NextOperation);
		if (IS_NUMBER(Expression))
			Second = RefObject<Value>(Value(strtoull(Expression, 0, 10))).Cast<Operand>();
		else
		{
			unsigned long long Length = 0;
			if (LocOperation)
				Length = LocOperation - Expression;

			Second = RefObject<AVariable>(AVariable(Enviroment.GetVariable(Expression, Length))).Cast<Operand>();
		}

		switch (OperationType->GetType())
		{
		case OperationDef::OperationType_Addition:
		{
			First = RefObject<Addition>(Addition(First, Second)).Cast<Operand>();
		} break;
		case OperationDef::OperationType_Subtraction:
		{
			First = RefObject<Subtraction>(Subtraction(First, Second)).Cast<Operand>();
		} break;
		}

		if (!LocOperation)
			break;

		OperationType = NextOperation;
		Expression = LocOperation + 1;
	}

	Origin = First;
}