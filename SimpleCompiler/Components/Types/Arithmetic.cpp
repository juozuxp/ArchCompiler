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
			return *(Expression + 1) != '=';
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

void Arithmetic::PostCompile(CompileMap& Enviroment)
{
}

RefObject<Operand> Arithmetic::EvaluateArthmetic(EnviromentMap& Enviroment, const char* Expression)
{
	const OperationDef* OperationType;

	RefObject<Operand> First;
	RefObject<Operand> Second;

	RegisterType TransitionSpace;

	const char* LocOperation;

	if (*Expression == '(')
	{
		List<char> Enclosure = Encapsule.GetEncapSpace(Expression);
		First = EvaluateArthmetic(Enviroment, Enclosure);

		Expression += Enclosure.GetCount() - 1 + 2;
		LocOperation = OperationDefs::LocateOperation(Expression, &OperationType);
	}
	else
	{
		LocOperation = OperationDefs::LocateOperation(Expression, &OperationType);
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

	TransitionSpace = TemporarySpace.GetRegister();

	Expression = LocOperation + OperationType->ExpressionSize();
	while (true)
	{
		const OperationDef* NextOperation;

		if (*Expression == '(')
		{
			List<char> Enclosure = Encapsule.GetEncapSpace(Expression);
			Second = EvaluateArthmetic(Enviroment, Enclosure);

			Expression += Enclosure.GetCount() - 1 + 2;
			LocOperation = OperationDefs::LocateOperation(Expression, &NextOperation);
		}
		else
		{
			LocOperation = OperationDefs::LocateOperation(Expression, &NextOperation);
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
		
		First = OperationType->CreateOperation(First, Second, TransitionSpace);
		if (!LocOperation)
			break;

		OperationType = NextOperation;
		Expression = LocOperation + NextOperation->ExpressionSize();
	}

	return First;
}