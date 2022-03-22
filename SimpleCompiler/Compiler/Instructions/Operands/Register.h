#pragma once
#include "Operand.h"

class Register : Operand
{
public:
	enum Type
	{
		Type_RAX,
		Type_RCX,
		Type_RDX,
		Type_RBX,
		Type_RSP,
		Type_RBP,
		Type_RSI,
		Type_RDI,

		Type_R8,
		Type_R9,
		Type_R10,
		Type_R11,
		Type_R12,
		Type_R13,
		Type_R14,
		Type_R15,

		Type_EAX,
		Type_ECX,
		Type_EDX,
		Type_EBX,
		Type_ESP,
		Type_EBP,
		Type_ESI,
		Type_EDI,

		Type_R8D,
		Type_R9D,
		Type_R10D,
		Type_R11D,
		Type_R12D,
		Type_R13D,
		Type_R14D,
		Type_R15D,

		Type_AX,
		Type_CX,
		Type_DX,
		Type_BX,
		Type_SP,
		Type_BP,
		Type_SI,
		Type_DI,

		Type_R8W,
		Type_R9W,
		Type_R10W,
		Type_R11W,
		Type_R12W,
		Type_R13W,
		Type_R14W,
		Type_R15W,

		Type_AL,
		Type_CL,
		Type_DL,
		Type_BL,
		Type_SPL,
		Type_BPL,
		Type_SIL,
		Type_DIL,

		Type_R8B,
		Type_R9B,
		Type_R10B,
		Type_R11B,
		Type_R12B,
		Type_R13B,
		Type_R14B,
		Type_R15B
	};

public:
	constexpr Register()
	{
	}

	constexpr Register(Type Register) : Type(Register)
	{
	}

public:
	unsigned char OperandFlags()
	{
		unsigned char Flags = Flags_Type_R;
		switch (Type / 16)
		{
		case 0:
		{
			Flags |= Flags_Size_Byte;
		} break;
		case 1:
		{
			Flags |= Flags_Size_Word;
		} break;
		case 2:
		{
			Flags |= Flags_Size_Dword;
		} break;
		case 3:
		{
			Flags |= Flags_Size_Qword;
		} break;
		}

		return Flags;
	}

	unsigned char OperandByte()
	{
		return Type % 8;
	}

	unsigned char PrefixREX();

private:
	Type Type = Type_RAX;
};