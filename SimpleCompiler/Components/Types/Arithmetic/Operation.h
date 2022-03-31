#pragma once
#include "Operand.h"
#include "../../../Utilities/RefObject.h"
#include "../../../GlobalInfo/RegisterTypes.h"
#include "OperationDef.h"

class Operation : public Operand
{
public:
	constexpr Operation()
	{
	}

public:
	static const char* LocateOperation(const char* Expression, const OperationDef** OperationDescription);

protected:
	inline Operation(RefObject<Operand> Left, RefObject<Operand> Right, RegisterType TransitionSpace) : Left(Left), Right(Right), TransitionSpace(TransitionSpace)
	{
	}

protected:
	RefObject<Operand> Left;
	RefObject<Operand> Right;
	RegisterType TransitionSpace;

private:
	static constexpr OperationDef Operations[] = { OperationDef(OperationDef::OperationType_Addition, CSL_PAIR("+")), OperationDef(OperationDef::OperationType_Subtraction, CSL_PAIR("-")), OperationDef(OperationDef::OperationType_Division, CSL_PAIR("/")),
												   OperationDef(OperationDef::OperationType_Multiplication, CSL_PAIR("*")), OperationDef(OperationDef::OperationType_Modulus, CSL_PAIR("%")), OperationDef(OperationDef::OperationType_LogicOr, CSL_PAIR("|")),
												   OperationDef(OperationDef::OperationType_LogicXor, CSL_PAIR("^")), OperationDef(OperationDef::OperationType_LogicAnd, CSL_PAIR("&")), OperationDef(OperationDef::OperationType_LogicAnd, CSL_PAIR("&")),
												   OperationDef(OperationDef::OperationType_And, CSL_PAIR("&&")), OperationDef(OperationDef::OperationType_Or,CSL_PAIR("||")), OperationDef(OperationDef::OperationType_Less, CSL_PAIR("<")),
												   OperationDef(OperationDef::OperationType_Over, CSL_PAIR(">")), OperationDef(OperationDef::OperationType_LessOrEqual, CSL_PAIR("<=")), OperationDef(OperationDef::OperationType_OverOrEqual, CSL_PAIR(">=")),
												   OperationDef(OperationDef::OperationType_Equal, CSL_PAIR("==")), OperationDef(OperationDef::OperationType_NotEqual, CSL_PAIR("!=")) };
};