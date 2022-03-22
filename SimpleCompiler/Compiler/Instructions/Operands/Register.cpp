#include "Register.h"
#include "../Instruction.h"

unsigned char Register::PrefixREX()
{
	unsigned char REX = 0;

	switch (Type / 16)
	{
	case 0:
		if ((Type % 16) >= 4)
			REX |= Instruction::Prefix_REX;
	case 3:
		REX |= Instruction::Prefix_REXW;
	}

	if (Type % 16 >= 8)
		REX |= Instruction::Prefix_REXR;

	return REX;
}