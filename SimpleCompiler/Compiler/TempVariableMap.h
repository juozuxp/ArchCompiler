#pragma once
#include "../GlobalInfo/RegisterTypes.h"
#include "../Utilities/RefObject.h"

class TempVariableMap
{
public:
	constexpr TempVariableMap()
	{
	}

public:
	constexpr RegisterType GetRegister()
	{
		return VolatileRegisters[RegisterUseMask++];
	}

public:
	constexpr unsigned short RetrieveRegisterMask()
	{
		if (!RegisterUseMask)
			return RegisterMask_None;

		return VolatileRegisterMasks[RegisterUseMask - 1];
	}
	
	constexpr void Merge(TempVariableMap& Other)
	{
		if (RegisterUseMask < Other.RegisterUseMask)
			RegisterUseMask = Other.RegisterUseMask;
	}

private:
	unsigned char RegisterUseMask = 0;

private:
	static constexpr RegisterType VolatileRegisters[] = { RegisterType::RBX, RegisterType::RSI, RegisterType::RDI, RegisterType::RBP, RegisterType::R10, RegisterType::R11, RegisterType::R12, RegisterType::R13, RegisterType::R14, RegisterType::R15 };
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