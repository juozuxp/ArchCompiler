#pragma once

class Operand
{
public:
	enum Flags
	{
		Flags_None,

		Flags_Size_Byte = (1 << 0),
		Flags_Size_Word = (1 << 1),
		Flags_Size_Dword = (1 << 2),
		Flags_Size_Qword = (1 << 3),

		Flags_Type_M = (1 << 4),
		Flags_Type_R = (1 << 5),
	};

public:
	constexpr Operand()
	{
	}

public:
	virtual unsigned char OperandByte()
	{
		return 0;
	}

	virtual unsigned char PrefixREX() // REX prefix byte
	{
		return 0;
	}

	virtual unsigned char OperandFlags()
	{
		return 0;
	}
	
private:

};

