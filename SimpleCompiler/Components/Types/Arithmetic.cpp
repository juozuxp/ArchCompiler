#include "Arithmetic.h"
#include "../Enviroments/EnviromentMap.h"
#include "../../Compiler/CompileMap.h"
#include "Variable.h"
#include "../Transferable/TransferVariable.h"
#include "../Transferable/TransferValue.h"
#include "../../Utilities/x86_x64Shell.h"

void Arithmetic::TranferOperator::Compile(CompileMap& Enviroment, RegisterType Source)
{
	this->Source->CompileRetrieve(Enviroment, Source);
}

void Arithmetic::Addition::Compile(CompileMap& Enviroment, RegisterType Source)
{
	Left->Compile(Enviroment, Source);
	Right->Compile(Enviroment, TransitionSpace);

	if (TransitionSpace.IsExtended())
	{
		if (Source.IsExtended())
		{
			unsigned char Operation[] =
			{
				PFX_REXWRB, ADDD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
		else
		{
			unsigned char Operation[] =
			{
				PFX_REXWB, ADDD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
	}
	else
	{
		if (Source.IsExtended())
		{
			unsigned char Operation[] =
			{
				PFX_REXWR, ADDD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
		else
		{
			unsigned char Operation[] =
			{
				PFX_REXW, ADDD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
	}
}

void Arithmetic::Subtraction::Compile(CompileMap& Enviroment, RegisterType Source)
{
	Left->Compile(Enviroment, Source);
	Right->Compile(Enviroment, TransitionSpace);

	if (TransitionSpace.IsExtended())
	{
		if (Source.IsExtended())
		{
			unsigned char Operation[] =
			{
				PFX_REXWRB, SUBD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
		else
		{
			unsigned char Operation[] =
			{
				PFX_REXWB, SUBD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
	}
	else
	{
		if (Source.IsExtended())
		{
			unsigned char Operation[] =
			{
				PFX_REXWR, SUBD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
		else
		{
			unsigned char Operation[] =
			{
				PFX_REXW, SUBD_R_RM(R_LR(Source, TransitionSpace)),
			};

			Enviroment.AddCode(Operation, sizeof(Operation));
		}
	}
}

unsigned long long Arithmetic::Parse(RefObject<EnviromentMap> Enviroment, const char* Expression)
{
	List<char> Deflate = Deflater.Deflate(Expression);

	unsigned long long EqualsIdx = 0;
	for (; EqualsIdx < Deflate.GetCount(); EqualsIdx++)
	{
		if (Deflate[EqualsIdx] == '=')
			break;
	}

	AssignTo = RefObject<TransferVariable>(TransferVariable(Enviroment->GetVariable(Deflate, EqualsIdx))).Cast<Transferable>();

	Origin = EvaluateArthmetic(*Enviroment, Deflate + EqualsIdx + 1);

	return 0;
}

unsigned long long Arithmetic::Parse(RefObject<EnviromentMap> Enviroment, const char* Expression, RefObject<Transferable> AssignTo)
{
	this->AssignTo = AssignTo;
	this->Origin = EvaluateArthmetic(*Enviroment, Deflater.Deflate(Expression));

	return 0;
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

#undef RAX

void Arithmetic::PreCompile(CompileMap& Enviroment)
{
	Enviroment.AddRegisterMask(TemporarySpace.RetrieveRegisterMask());
}

void Arithmetic::Compile(CompileMap& Enviroment)
{
	Origin->Compile(Enviroment, RegisterType::RAX);
	AssignTo->CompileAssign(Enviroment, RegisterType::RAX);
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

const DefinitionValue* Arithmetic::ExtractDefinitionValue(const char* Expression, unsigned long long Length)
{
	if (!Length)
		Length = strlen(Expression);

	for (unsigned long long i = 0; i < ARRAY_COUNT(DefValues); i++)
	{
		if (DefValues[i].IsType(Expression, Length))
			return &DefValues[i];
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

	RegisterType TransferRegister;

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
			First = RefObject<TranferOperator>(RefObject<TransferValue>(TransferValue(strtoull(Expression, 0, 10))).Cast<Transferable>()).Cast<Operand>();
		else
		{
			unsigned long long Length = 0;
			if (LocOperation)
				Length = LocOperation - Expression;
			
			const DefinitionValue* ConstantValue = ExtractDefinitionValue(Expression, Length);
			if (ConstantValue)
				First = RefObject<TranferOperator>(RefObject<TransferValue>(TransferValue(ConstantValue->GetValue())).Cast<Transferable>()).Cast<Operand>();
			else
				First = RefObject<TranferOperator>(RefObject<TransferVariable>(TransferVariable(Enviroment.GetVariable(Expression, Length))).Cast<Transferable>()).Cast<Operand>();
		}
	}

	if (!LocOperation)
		return First;

	TransferRegister = TemporarySpace.GetRegister();

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
				Second = RefObject<TranferOperator>(RefObject<TransferValue>(TransferValue(strtoull(Expression, 0, 10))).Cast<Transferable>()).Cast<Operand>();
			else
			{
				unsigned long long Length = 0;
				if (LocOperation)
					Length = LocOperation - Expression;

				const DefinitionValue* ConstantValue = ExtractDefinitionValue(Expression, Length);
				if (ConstantValue)
					Second = RefObject<TranferOperator>(RefObject<TransferValue>(TransferValue(ConstantValue->GetValue())).Cast<Transferable>()).Cast<Operand>();
				else
					Second = RefObject<TranferOperator>(RefObject<TransferVariable>(TransferVariable(Enviroment.GetVariable(Expression, Length))).Cast<Transferable>()).Cast<Operand>();
			}
		}

		switch (OperationType->GetType())
		{
		case OperationDef::OperationType_Addition:
		{
			First = RefObject<Addition>(Addition(First, Second, TransferRegister)).Cast<Operand>();
		} break;
		case OperationDef::OperationType_Subtraction:
		{
			First = RefObject<Subtraction>(Subtraction(First, Second, TransferRegister)).Cast<Operand>();
		} break;
		}

		if (!LocOperation)
			break;

		OperationType = NextOperation;
		Expression = LocOperation + 1;
	}

	return First;
}