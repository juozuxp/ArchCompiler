#include "Arithmetic.h"
#include "../Enviroments/EnviromentMap.h"
#include "../../Compiler/CompileMap.h"
#include "Variable.h"
#include "../Transferable/TransferVariable.h"
#include "../Transferable/TransferValue.h"
#include "../Transferable/TransferDynStack.h"
#include "../Transferable/TransferFunction.h"

#include "Arithmetic/OperationDef.h"
#include "Arithmetic/TranferOperator.h"
#include "../Types/String.h"

unsigned long long Arithmetic::Parse(RefObject<EnviromentMap> Enviroment, const char* Expression)
{
	RefObject<Variable> Variable;

	const char* VariableName;

	Expression = Skipper.Skip(Expression);

	VariableName = Expression;
	for (; *Expression; Expression++)
	{
		if (*Expression == '=' || Skipper.IsSkippable(*Expression))
			break;
	}

	Variable = Enviroment->GetVariable(VariableName, Expression - VariableName);

	Signed = Variable->GetSigniage() | (1 << 1);
	AssignTo = RefObject<TransferVariable>(TransferVariable(Variable)).Cast<Transferable>();

	for (; *Expression; Expression++)
	{
		if (*Expression == '=')
			break;
	}

	Origin = EvaluateArthmetic(*Enviroment, Expression + 1);

	return 0;
}

unsigned long long Arithmetic::Parse(RefObject<EnviromentMap> Enviroment, const char* Expression, RefObject<Transferable> AssignTo)
{
	this->AssignTo = AssignTo;
	this->Origin = EvaluateArthmetic(*Enviroment, Expression);

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

	Origin->PreCompile(Enviroment, RegisterType::Type_RAX);
	AssignTo->PreCompile(Enviroment, RegisterType::Type_RAX);

	for (Pair<RefObject<Transferable>, RefObject<Transferable>>& Transfer : PriorityTransfers)
	{
		Transfer.First->PreCompile(Enviroment, RegisterType::Type_RAX);
		Transfer.Second->PreCompile(Enviroment, RegisterType::Type_RAX);
	}
}

void Arithmetic::Compile(CompileMap& Enviroment)
{
	for (Pair<RefObject<Transferable>, RefObject<Transferable>>& Transfer : PriorityTransfers)
	{
		Transfer.First->CompileRetrieve(Enviroment, RegisterType::Type_RAX);
		Transfer.Second->CompileAssign(Enviroment, RegisterType::Type_RAX);
	}

	if (Signed & 1)
		Origin->CompileSigned(Enviroment, RegisterType::Type_RAX);
	else
		Origin->Compile(Enviroment, RegisterType::Type_RAX);

	AssignTo->CompileAssign(Enviroment, RegisterType::Type_RAX);
}

void Arithmetic::PostCompile(CompileMap& Enviroment)
{
	Origin->PostCompile(Enviroment, RegisterType::Type_RAX);
	AssignTo->PostCompile(Enviroment, RegisterType::Type_RAX);

	for (Pair<RefObject<Transferable>, RefObject<Transferable>>& Transfer : PriorityTransfers)
	{
		Transfer.First->PostCompile(Enviroment, RegisterType::Type_RAX);
		Transfer.Second->PostCompile(Enviroment, RegisterType::Type_RAX);
	}
}

RefObject<Operand> Arithmetic::EvaluateOperand(RefObject<EnviromentMap> Enviroment, const char** Expression, const DualOperation** ResultingOperation)
{
	const SingularOperation* Singular;

	*Expression = Skipper.Skip(*Expression);
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

	RefObject<Variable> ResultVariable;

	const char* LocOperation;
	const char* Expresive;

	Expresive = Skipper.Skip(*Expression);

	LocOperation = OperationDefs::LocateDualOperation(Expresive, ResultingOperation);
	*Expression = LocOperation;

	if (IS_NUMBER(Expresive))
		return RefObject<TranferOperator>(RefObject<TransferValue>(TransferValue(strtoull(Expresive, 0, 10))).Cast<Transferable>()).Cast<Operand>();
	else if (*Expresive == '\"')
		return RefObject<TranferOperator>(RefObject<TransferVariable>(TransferVariable(Enviroment->GetString(Expresive + 1, StringEncap.GetEncapEnd(Expresive) - (Expresive + 1)).Cast<Variable>())).Cast<Transferable>()).Cast<Operand>();

	unsigned long long Length = 0;
	if (LocOperation)
	{
		for (LocOperation--;; LocOperation--)
		{
			if (!Skipper.IsSkippable(*LocOperation))
				break;
		}

		Length = LocOperation - Expresive + 1;
	}
	else
	{
		Length = strlen(Expresive);
		LocOperation = Expresive + Length;
		for (LocOperation--;; LocOperation--, Length--)
		{
			if (!Skipper.IsSkippable(*LocOperation))
				break;
		}
	}

	unsigned long long ConstantValue;
	if (Enviroment->GetConstantValue(&ConstantValue, Expresive, Length))
		return RefObject<TranferOperator>(RefObject<TransferValue>(TransferValue(ConstantValue)).Cast<Transferable>()).Cast<Operand>();

	bool IsFunctionCall = false;

	for (unsigned long long i = 0; i < Length; i++)
	{
		if (Expresive[i] == '(')
		{
			IsFunctionCall = true;
			break;
		}
	}

	if (!IsFunctionCall)
	{
		for (const char* RunExpression = Expresive + Length; *RunExpression; RunExpression++)
		{
			if (!Skipper.IsSkippable(*RunExpression))
			{
				if (*RunExpression != '(')
					break;

				IsFunctionCall = true;
				break;
			}
		}
	}

	if (IsFunctionCall)
	{
		RefObject<Transferable> TransitionSpace;
		RefObject<Transferable> TransferValue;

		TransitionSpace = RefObject<TransferDynStack>(TransferDynStack()).Cast<Transferable>();
		TransferValue = RefObject<TransferFunction>(TransferFunction(Enviroment, Expresive)).Cast<Transferable>();

		PriorityTransfers.Add(Pair<RefObject<Transferable>, RefObject<Transferable>>(TransferValue, TransitionSpace));

		return RefObject<TranferOperator>(TranferOperator(TransitionSpace)).Cast<Operand>();
	}

	ResultVariable = Enviroment->GetVariable(Expresive, Length);
	if (!(Signed & (1 << 1)))
		Signed = ResultVariable->GetSigniage() | (1 << 1);

	return RefObject<TranferOperator>(RefObject<TransferVariable>(TransferVariable(ResultVariable)).Cast<Transferable>()).Cast<Operand>();
}

RefObject<Operand> Arithmetic::EvaluateArthmetic(RefObject<EnviromentMap> Enviroment, const char* Expression)
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