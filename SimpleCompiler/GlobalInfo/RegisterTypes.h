#pragma once
#include "../Utilities/x86_x64Shell.h"

enum RegisterType
{
	RegisterType_RAX = RAX,
	RegisterType_RCX = RCX,
	RegisterType_RDX = RDX,
	RegisterType_RBX = RBX,
	RegisterType_RSP = RSP, // Just a bad idea to specify anywhere, you'll most likely end up corrupting the execution
	RegisterType_RBP = RBP, // Not recomended for pointer use
	RegisterType_RSI = RSI,
	RegisterType_RDI = RDI,

	RegisterType_x64Extend = (1 << 3),

	RegisterType_R8 = R8 | (1 << 3),
	RegisterType_R9 = R9 | (1 << 3),
	RegisterType_R10 = R10 | (1 << 3),
	RegisterType_R11 = R11 | (1 << 3),
	RegisterType_R12 = R12 | (1 << 3), // Increadibly volatile with dereferencing, requires multiple bytes to use, not recomended
	RegisterType_R13 = R13 | (1 << 3), // Less volatile, but still has an annoying trate of dereferencing
	RegisterType_R14 = R14 | (1 << 3),
	RegisterType_R15 = R15 | (1 << 3),

	RegisterType_Invalid = (unsigned char)~0,
	RegisterType_None = RegisterType_Invalid
};