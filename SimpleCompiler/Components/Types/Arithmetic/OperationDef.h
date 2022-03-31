#pragma once
#include <string.h>
#include "../../../Utilities/RefObject.h"
#include "../../../Utilities/SimpleUtilities.h"

#include "Equal.h"
#include "Addition.h"
#include "Subtraction.h"
#include "Derefrence.h"

class OperationDefinition
{
public:
	constexpr OperationDefinition()
	{
	}

	constexpr OperationDefinition(const char* SymbolSet, unsigned long long SetLength) : SymbolSet(SymbolSet), SetLength(SetLength)
	{
	}

public:
	inline bool IsOperation(const char* SymbolSet) const
	{
		return !strncmp(this->SymbolSet, SymbolSet, SetLength);
	}

	inline bool IsBetterFit(const OperationDefinition* Operation, const char* SymbolSet) const
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
};

class DualOperation : public OperationDefinition
{
public:
	enum OperationType // More of a suggestion list now
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
	constexpr DualOperation()
	{
	}

	constexpr DualOperation(RefObject<class Operand>(*CreateOperator)(RefObject<class Operand> First, RefObject<class Operand> Second, class RegisterType TransitionSpace), const char* SymbolSet, unsigned long long SetLength) : OperationDefinition(SymbolSet, SetLength), CreateOperator(CreateOperator)
	{
	}

public:
	RefObject<class Operand> CreateOperation(RefObject<class Operand> First, RefObject<class Operand> Second, class RegisterType TransitionSpace) const;

private:
	RefObject<class Operand>(*CreateOperator)(RefObject<class Operand> First, RefObject<class Operand> Second, class RegisterType TransitionSpace) = 0;
};

class SingularOperation : public OperationDefinition
{
public:
	enum OperationType // More of a suggestion list now
	{
		OperationType_None,
		OperationType_Not,
		OperationType_Dereference,
		OperationType_LogicNot
	};

public:
	constexpr SingularOperation()
	{
	}

	constexpr SingularOperation(RefObject<class Operand>(*CreateOperator)(RefObject<class Operand> Operand), const char* SymbolSet, unsigned long long SetLength) : OperationDefinition(SymbolSet, SetLength), CreateOperator(CreateOperator)
	{
	}

public:
	RefObject<class Operand> CreateOperation(RefObject<class Operand> Operand) const;

private:
	RefObject<class Operand>(*CreateOperator)(RefObject<class Operand> Operand) = 0;
};

class OperationDefs
{
public:
	static const SingularOperation* LocateSingularOperation(const char* Expression);
	static const char* LocateDualOperation(const char* Expression, const DualOperation** OperationDescription);

private:
	static constexpr DualOperation DualOperations[] = { DualOperation(Addition::CreateOperator, CSL_PAIR("+")), DualOperation(Subtraction::CreateOperator, CSL_PAIR("-")), DualOperation(0, CSL_PAIR("/")),
												   DualOperation(0, CSL_PAIR("*")), DualOperation(0, CSL_PAIR("%")), DualOperation(0, CSL_PAIR("|")),
												   DualOperation(0, CSL_PAIR("^")), DualOperation(0, CSL_PAIR("&")), DualOperation(0, CSL_PAIR("&")),
												   DualOperation(0, CSL_PAIR("&&")), DualOperation(0, CSL_PAIR("||")), DualOperation(0, CSL_PAIR("<")),
												   DualOperation(0, CSL_PAIR(">")), DualOperation(0, CSL_PAIR("<=")), DualOperation(0, CSL_PAIR(">=")),
												   DualOperation(Equal::CreateOperator, CSL_PAIR("==")), DualOperation(0, CSL_PAIR("!=")) };

	static constexpr SingularOperation SingularOperations[] = { SingularOperation(0, CSL_PAIR("!")), SingularOperation(0, CSL_PAIR("~")), SingularOperation(Derefrence::CreateOperator, CSL_PAIR("*"))};
};