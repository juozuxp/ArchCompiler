#pragma once
#include "Operand.h"

class Memory : Operand
{
public:

	class Register
	{
	};

	class MemoryRegister
	{
	public:
	private:

	};

	class Relative
	{
	};

public:
	unsigned char PrefixREX();
	unsigned char OperandByte();
	unsigned char OperandFlags();

private:
	

};

