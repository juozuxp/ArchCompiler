#include "Arithmetic.h"
#include "../Enviroments/EnviromentMap.h"
#include "../../Compiler/CompileMap.h"
#include "Variable.h"
#include "../Transferable/TransferVariable.h"
#include "../Transferable/TransferValue.h"

#include "Arithmetic/OperationDef.h"
#include "Arithmetic/Operation.h"
#include "Arithmetic/Equal.h"
#include "Arithmetic/Addition.h"
#include "Arithmetic/Subtraction.h"
#include "Arithmetic/TranferOperator.h"

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

	return false;
}

void Arithmetic::PreCompile(CompileMap& Enviroment)
{
	Enviroment.AddRegisterMask(TemporarySpace.RetrieveRegisterMask());
}

void Arithmetic::Compile(CompileMap& Enviroment)
{
	Origin->Compile(Enviroment, RegisterType::RAX);
	AssignTo->CompileAssign(Enviroment, RegisterType::RAX);
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

RefObject<Operand> Arithmetic::EvaluateArthmetic(EnviromentMap& Enviroment, const char* Expression)
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
		LocOperation = Operation::LocateOperation(Expression, &OperationType);
	}
	else
	{
		LocOperation = Operation::LocateOperation(Expression, &OperationType);
		if (IS_NUMBER(Expression))
			First = RefObject<TranferOperator>(RefObject<TransferValue>(TransferValue(strtoull(Expression, 0, 10))).Cast<Transferable>()).Cast<Operand>();
		else
		{
			unsigned long long Length = 0;
			if (LocOperation)
				Length = LocOperation - Expression;

			unsigned long long ConstantValue;
			if (Enviroment.GetConstantValue(&ConstantValue, Expression, Length))
				First = RefObject<TranferOperator>(RefObject<TransferValue>(TransferValue(ConstantValue)).Cast<Transferable>()).Cast<Operand>();
			else
				First = RefObject<TranferOperator>(RefObject<TransferVariable>(TransferVariable(Enviroment.GetVariable(Expression, Length))).Cast<Transferable>()).Cast<Operand>();
		}
	}

	if (!LocOperation)
		return First;

	TransferRegister = TemporarySpace.GetRegister();

	Expression = LocOperation + OperationType->ExpressionSize();
	while (true)
	{
		const OperationDef* NextOperation;

		if (*Expression == '(')
		{
			List<char> Enclosure = ExtractEnclosure(Expression);
			Second = EvaluateArthmetic(Enviroment, Enclosure);

			Expression += Enclosure.GetCount() - 1 + 2;
			LocOperation = Operation::LocateOperation(Expression, &NextOperation);
		}
		else
		{
			LocOperation = Operation::LocateOperation(Expression, &NextOperation);
			if (IS_NUMBER(Expression))
				Second = RefObject<TranferOperator>(RefObject<TransferValue>(TransferValue(strtoull(Expression, 0, 10))).Cast<Transferable>()).Cast<Operand>();
			else
			{
				unsigned long long Length = 0;
				if (LocOperation)
					Length = LocOperation - Expression;

				unsigned long long ConstantValue;
				if (Enviroment.GetConstantValue(&ConstantValue, Expression, Length))
					Second = RefObject<TranferOperator>(RefObject<TransferValue>(TransferValue(ConstantValue)).Cast<Transferable>()).Cast<Operand>();
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
		case OperationDef::OperationType_Equal:
		{
			First = RefObject<Equal>(Equal(First, Second, TransferRegister)).Cast<Operand>();
		} break;
		}

		if (!LocOperation)
			break;

		OperationType = NextOperation;
		Expression = LocOperation + NextOperation->ExpressionSize();
	}

	return First;
}