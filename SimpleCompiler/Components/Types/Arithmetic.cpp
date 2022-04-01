#include "Arithmetic.h"
#include "../Enviroments/EnviromentMap.h"
#include "../../Compiler/CompileMap.h"
#include "Variable.h"
#include "../Transferable/TransferVariable.h"
#include "../Transferable/TransferValue.h"

#include "Arithmetic/OperationDef.h"
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

RefObject<Operand> Arithmetic::EvaluateOperand(EnviromentMap& Enviroment, const char** Expression, const DualOperation** ResultingOperation)
{
	const SingularOperation* Singular;

	Singular = OperationDefs::LocateSingularOperation(*Expression);
	if (Singular)
	{
		*Expression += Singular->ExpressionSize();
		return Singular->CreateOperation(EvaluateOperand(Enviroment, Expression, ResultingOperation));
	}
	else if (**Expression == '(')
	{
		RefObject<Operand> Result;

		List<char> Enclosure = Encapsule.GetEncapSpace(*Expression);
		Result = EvaluateArthmetic(Enviroment, Enclosure);

		(*Expression) += Enclosure.GetCount() - 1 + 2;
		*Expression = OperationDefs::LocateDualOperation(*Expression, ResultingOperation);

		return Result;
	}

	const char* LocOperation;
	const char* Expresive;

	Expresive = *Expression;

	LocOperation = OperationDefs::LocateDualOperation(Expresive, ResultingOperation);
	*Expression = LocOperation;

	if (IS_NUMBER(Expresive))
		return RefObject<TranferOperator>(RefObject<TransferValue>(TransferValue(strtoull(Expresive, 0, 10))).Cast<Transferable>()).Cast<Operand>();

	unsigned long long Length = 0;
	if (LocOperation)
		Length = LocOperation - Expresive;

	unsigned long long ConstantValue;
	if (Enviroment.GetConstantValue(&ConstantValue, Expresive, Length))
		return RefObject<TranferOperator>(RefObject<TransferValue>(TransferValue(ConstantValue)).Cast<Transferable>()).Cast<Operand>();

	return RefObject<TranferOperator>(RefObject<TransferVariable>(TransferVariable(Enviroment.GetVariable(Expresive, Length))).Cast<Transferable>()).Cast<Operand>();
}

RefObject<Operand> Arithmetic::EvaluateArthmetic(EnviromentMap& Enviroment, const char* Expression)
{
	const DualOperation* OperationType;

	RefObject<Operand> First;
	RefObject<Operand> Second;

	RegisterType TransitionSpace;

	const char* LocOperation;

	LocOperation = Expression;
	First = EvaluateOperand(Enviroment, &LocOperation, &OperationType);
	if (!LocOperation)
		return First;

	TransitionSpace = TemporarySpace.GetRegister();

	Expression = LocOperation + OperationType->ExpressionSize();
	while (true)
	{
		const DualOperation* NextOperation;

		LocOperation = Expression;
		Second = EvaluateOperand(Enviroment, &LocOperation, &NextOperation);

		First = OperationType->CreateOperation(First, Second, TransitionSpace);
		if (!LocOperation)
			break;

		OperationType = NextOperation;
		Expression = LocOperation + NextOperation->ExpressionSize();
	}

	return First;
}