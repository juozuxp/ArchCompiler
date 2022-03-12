#include "Arithmetic.h"
#include "../../Compiler/Enviroments/EnviromentMap.h"
#include "../../Compiler/CompileMap.h"
#include "Variable.h"
#include "../Assignables/AssignVariable.h"
#include "../../Utilities/x86_x64Shell.h"

void Arithmetic::Value::Compile(CompileMap& Enviroment)
{
	if (Definition < 0xFF)
	{
		if (Definition == 0)
		{
			unsigned char Shell[] =
			{
				PFX_REXW, XORD_RM_R(LR_R(EAX, EAX), Definition)
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
			return;
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, XORD_RM_R(LR_R(RAX, RAX), Definition),
				MOV_R_B(AL, Definition)
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
			return;
		}
	}


	if (Definition < 0xFFFF)
	{
		unsigned char Shell[] =
		{
			PFX_REXW, XORD_RM_R(LR_R(RAX, RAX), Definition), // clear the value, fuck knows why it's made like this but it will only clear RAX when it gets overwritten with a value bigger than or equal to 4 bytes
			MOV_R_W(AX, Definition)
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
		return;
	}


	if (Definition < 0xFFFFFFFF)
	{
		unsigned char Shell[] =
		{
			MOV_R_D(EAX, Definition)
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
		return;
	}

	unsigned char Shell[] =
	{
		MOV_R_Q(RAX, Definition)
	};

	Enviroment.AddCode(Shell, sizeof(Shell));
}

void Arithmetic::Addition::Compile(CompileMap& Enviroment)
{
	Left->Compile(Enviroment);

	TransitionSpace->Compile(Enviroment);

	Right->Compile(Enviroment);

	unsigned char Preserve[] =
	{
		PFX_REXW, MOVD_R_RM(R_LR(RBX, RAX)),
	};

	Enviroment.AddCode(Preserve, sizeof(Preserve));

	TransitionSpace->CompileRetrieve(Enviroment);

	unsigned char Operation[] =
	{
		PFX_REXW, ADDD_R_RM(R_LR(RAX, RBX)),
	};

	Enviroment.AddCode(Operation, sizeof(Operation));
}

void Arithmetic::Subtraction::Compile(CompileMap& Enviroment)
{
	Left->Compile(Enviroment);

	TransitionSpace->Compile(Enviroment);

	Right->Compile(Enviroment);

	unsigned char Preserve[] =
	{
		PFX_REXW, MOVD_R_RM(R_LR(RBX, RAX)),
	};

	Enviroment.AddCode(Preserve, sizeof(Preserve));

	TransitionSpace->CompileRetrieve(Enviroment);

	unsigned char Operation[] =
	{
		PFX_REXW, SUBD_R_RM(R_LR(RAX, RBX))
	};

	Enviroment.AddCode(Operation, sizeof(Operation));
}

void Arithmetic::AVariable::Compile(class CompileMap& Enviroment)
{
	Origin->CompileRetrieve(Enviroment);
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

	AssignTo = RefObject<AssignVariable>(Enviroment.GetVariable(Deflate, EqualsIdx)).Cast<Assignable>();

	Origin = EvaluateArthmetic(Enviroment, Deflate + EqualsIdx + 1);
}

void Arithmetic::Parse(class EnviromentMap& Enviroment, const char* Expression, RefObject<Assignable> AssignTo)
{
	this->AssignTo = AssignTo;
	this->Origin = EvaluateArthmetic(Enviroment, Deflater.Deflate(Expression));
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

unsigned short Arithmetic::GetRegisterMask()
{
	return TemporarySpace.RetrieveRegisterMask();
}

unsigned long long Arithmetic::GetStackSize()
{
	return TemporarySpace.RetrieveStackAllocation();
}

void Arithmetic::Compile(CompileMap& Enviroment)
{
	Origin->Compile(Enviroment);
	AssignTo->Compile(Enviroment);
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

const char* Arithmetic::HuntEnclosure(const char* Expression)
{
	Expression++;
	for (; *Expression; Expression++)
	{
		if (*Expression == '(')
			Expression = HuntEnclosure(Expression);

		if (*Expression == ')')
			break;
	}

	return Expression + 1;
}

List<char> Arithmetic::ExtractEnclosure(const char* Expression)
{
	List<char> Result;

	Result.Add(Expression + 1, (HuntEnclosure(Expression) - 1) - (Expression + 1));
	Result.Add('\0');

	return Result;
}

RefObject<Arithmetic::Operand> Arithmetic::EvaluateArthmetic(EnviromentMap& Enviroment, const char* Expression)
{
	const OperationDef* OperationType;

	RefObject<Operand> First;
	RefObject<Operand> Second;

	const char* LocOperation;

	if (*Expression == '(')
	{
		List<char> Enclosure = ExtractEnclosure(Expression);
		First = EvaluateArthmetic(Enviroment, Enclosure);

		Expression += Enclosure.GetCount() - 1 + 2;
		LocOperation = LocateOperation(Expression, &OperationType);
	}
	else
	{
		LocOperation = LocateOperation(Expression, &OperationType);
		if (IS_NUMBER(Expression))
			First = RefObject<Value>(Value(strtoull(Expression, 0, 10))).Cast<Operand>();
		else
		{
			unsigned long long Length = 0;
			if (LocOperation)
				Length = LocOperation - Expression;

			First = RefObject<AVariable>(AVariable(Enviroment.GetVariable(Expression, Length))).Cast<Operand>();
		}
	}

	if (!LocOperation)
		return First;

	Expression = LocOperation + 1;
	while (true)
	{
		const OperationDef* NextOperation;

		if (*Expression == '(')
		{
			List<char> Enclosure = ExtractEnclosure(Expression);
			Second = EvaluateArthmetic(Enviroment, Enclosure);

			Expression += Enclosure.GetCount() - 1 + 2;
			LocOperation = LocateOperation(Expression, &NextOperation);
		}
		else
		{
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
		}

		switch (OperationType->GetType())
		{
		case OperationDef::OperationType_Addition:
		{
			First = RefObject<Addition>(Addition(First, Second, TemporarySpace.CreateAssignable())).Cast<Operand>();
		} break;
		case OperationDef::OperationType_Subtraction:
		{
			First = RefObject<Subtraction>(Subtraction(First, Second, TemporarySpace.CreateAssignable())).Cast<Operand>();
		} break;
		}

		if (!LocOperation)
			break;

		OperationType = NextOperation;
		Expression = LocOperation + 1;
	}

	return First;
}