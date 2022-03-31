#pragma once
#include <string.h>
#include "../../../Utilities/RefObject.h"
#include "../../../Utilities/SimpleUtilities.h"

#include "Equal.h"
#include "Addition.h"
#include "Subtraction.h"

class OperationDef // this absolutely insists on being defined outside the parent class, holy fuck kms
{
public:
	enum OperationType
	{
		OperationType_None,
		OperationType_Addition,
		OperationType_Subtraction,
		OperationType_Division,
		OperationType_Multiplication,
		OperationType_Modulus,
		OperationType_LogicXor,
		OperationType_LogicAnd,
		OperationType_LogicOr,

		OperationType_And, // Conditional operations (yes arithmatic is gonna be conditional, this is way better than doing something simple and mundain)
		OperationType_Or,
		OperationType_Less,
		OperationType_Over,
		OperationType_LessOrEqual,
		OperationType_OverOrEqual,
		OperationType_Equal,
		OperationType_NotEqual
	};

public:
	constexpr OperationDef()
	{
	}

	constexpr OperationDef(RefObject<class Operand>(*CreateOperator)(RefObject<class Operand> First, RefObject<class Operand> Second, class RegisterType TransitionSpace), const char* SymbolSet, unsigned long long SetLength) : CreateOperator(CreateOperator), SymbolSet(SymbolSet), SetLength(SetLength)
	{
	}

public:
	RefObject<class Operand> CreateOperation(RefObject<class Operand> First, RefObject<class Operand> Second, class RegisterType TransitionSpace) const;

public:
	inline bool IsOperation(const char* SymbolSet) const
	{
		return !strncmp(this->SymbolSet, SymbolSet, SetLength);
	}

	inline bool IsBetterFit(const OperationDef* Operation, const char* SymbolSet) const
	{
		if (SetLength <= Operation->SetLength)
			return false;

		return IsOperation(SymbolSet);
	}

	constexpr unsigned long long ExpressionSize() const
	{
		return SetLength;
	}

private:
	const char* SymbolSet = 0;
	unsigned long long SetLength = 0;

	RefObject<class Operand>(*CreateOperator)(RefObject<class Operand> First, RefObject<class Operand> Second, class RegisterType TransitionSpace) = 0;
};

class OperationDefs
{
public:
	static const char* LocateOperation(const char* Expression, const OperationDef** OperationDescription);

private:
	static constexpr OperationDef Operations[] = { OperationDef(Addition::CreateOperator, CSL_PAIR("+")), OperationDef(Subtraction::CreateOperator, CSL_PAIR("-")), OperationDef(0, CSL_PAIR("/")),
												   OperationDef(0, CSL_PAIR("*")), OperationDef(0, CSL_PAIR("%")), OperationDef(0, CSL_PAIR("|")),
												   OperationDef(0, CSL_PAIR("^")), OperationDef(0, CSL_PAIR("&")), OperationDef(0, CSL_PAIR("&")),
												   OperationDef(0, CSL_PAIR("&&")), OperationDef(0, CSL_PAIR("||")), OperationDef(0, CSL_PAIR("<")),
												   OperationDef(0, CSL_PAIR(">")), OperationDef(0, CSL_PAIR("<=")), OperationDef(0, CSL_PAIR(">=")),
												   OperationDef(Equal::CreateOperator, CSL_PAIR("==")), OperationDef(0, CSL_PAIR("!=")) };
};