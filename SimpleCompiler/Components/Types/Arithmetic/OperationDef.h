#pragma once
#include <string.h>
#include "../../../Utilities/SimpleUtilities.h"

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

	constexpr OperationDef(OperationType Type, const char* SymbolSet, unsigned long long SetLength) : Type(Type), SymbolSet(SymbolSet), SetLength(SetLength)
	{
	}

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

	constexpr OperationType GetType() const
	{
		return Type;
	}

	constexpr unsigned long long ExpressionSize() const
	{
		return SetLength;
	}

private:
	const char* SymbolSet = 0;
	unsigned long long SetLength = 0;

	OperationType Type = OperationType_None;
};