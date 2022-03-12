#pragma once
#include "../GlobalInfo/RegisterTypes.h"
#include "../Parser/Assignables/Assignable.h"
#include "../Utilities/RefObject.h"

class TempVariableMap
{
public:
	constexpr TempVariableMap()
	{
	}

	constexpr TempVariableMap(unsigned char StartMask, unsigned long long StartStack) : RegisterUseMask(StartMask), StackAllocation(StartStack)
	{
	}

public:
	RefObject<Assignable> CreateAssignable();

public:
	constexpr unsigned short RetrieveRegisterMask()
	{
		if (!RegisterUseMask)
			return RegisterMask_None;

		return VolatileRegisterMasks[RegisterUseMask - 1];
	}

	constexpr unsigned long long RetrieveStackAllocation()
	{
		return StackAllocation;
	}

private:
	unsigned char RegisterUseMask = 0;
	unsigned long long StackAllocation = 0;

private:
	static constexpr RegisterType VolatileRegisters[] = { RegisterType_RBX, RegisterType_RSI, RegisterType_RDI, RegisterType_RBP, RegisterType_R10, RegisterType_R11, RegisterType_R12, RegisterType_R13, RegisterType_R14, RegisterType_R15 };
	static constexpr unsigned short VolatileRegisterMasks[] = { RegisterMask_RBX, 
																RegisterMask_RBX | RegisterMask_RSI, 
																RegisterMask_RBX | RegisterMask_RSI | RegisterMask_RDI,
																RegisterMask_RBX | RegisterMask_RSI | RegisterMask_RDI | RegisterMask_RBP,
																RegisterMask_RBX | RegisterMask_RSI | RegisterMask_RDI | RegisterMask_RBP | RegisterMask_R10,
																RegisterMask_RBX | RegisterMask_RSI | RegisterMask_RDI | RegisterMask_RBP | RegisterMask_R10 | RegisterMask_R11,
																RegisterMask_RBX | RegisterMask_RSI | RegisterMask_RDI | RegisterMask_RBP | RegisterMask_R10 | RegisterMask_R11 | RegisterMask_R12, 
																RegisterMask_RBX | RegisterMask_RSI | RegisterMask_RDI | RegisterMask_RBP | RegisterMask_R10 | RegisterMask_R11 | RegisterMask_R12 | RegisterMask_R13, 
																RegisterMask_RBX | RegisterMask_RSI | RegisterMask_RDI | RegisterMask_RBP | RegisterMask_R10 | RegisterMask_R11 | RegisterMask_R12 | RegisterMask_R13 | RegisterMask_R14, 
																RegisterMask_RBX | RegisterMask_RSI | RegisterMask_RDI | RegisterMask_RBP | RegisterMask_R10 | RegisterMask_R11 | RegisterMask_R12 | RegisterMask_R13 | RegisterMask_R14 | RegisterMask_R15 };
};