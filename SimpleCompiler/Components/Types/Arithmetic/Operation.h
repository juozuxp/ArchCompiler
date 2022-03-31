#pragma once
#include "Operand.h"
#include "../../../Utilities/RefObject.h"
#include "../../../GlobalInfo/RegisterTypes.h"

class Operation : public Operand
{
public:
	constexpr Operation()
	{
	}

protected:
	inline Operation(RefObject<Operand> Left, RefObject<Operand> Right, RegisterType TransitionSpace) : Left(Left), Right(Right), TransitionSpace(TransitionSpace)
	{
	}

protected:
	RefObject<Operand> Left;
	RefObject<Operand> Right;
	RegisterType TransitionSpace;
};