#pragma once
#include "../Utilities/x86_x64Shell.h"

class Registers
{
public:
	constexpr Registers()
	{
	}

	constexpr unsigned char GetProfile()
	{
		return WholeProfile;
	}

	constexpr void ResetProfile()
	{
		Profile = 0;
	}

	constexpr unsigned char GetRegister()
	{
		return Volatile[Profile++];
	}

private:
	unsigned char Profile = 0;
	unsigned char WholeProfile = 0;

private:
	static constexpr unsigned char Volatile[] = { RBX, RSI, RDI, RBP };
};