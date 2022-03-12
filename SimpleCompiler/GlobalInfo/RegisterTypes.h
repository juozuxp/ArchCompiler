#pragma once

enum RegisterType // hardcoded due to x86_x64shell volitility
{
	RegisterType_RAX = 0,
	RegisterType_RCX = 1,
	RegisterType_RDX = 2,
	RegisterType_RBX = 3,
	RegisterType_RSP = 4, // Just a bad idea to specify anywhere, you'll most likely end up corrupting the execution
	RegisterType_RBP = 5, // Not recomended for pointer use
	RegisterType_RSI = 6,
	RegisterType_RDI = 7,

	RegisterType_x64Extend = (1 << 3),

	RegisterType_R8 = 0 | RegisterType_x64Extend,
	RegisterType_R9 = 1 | RegisterType_x64Extend,
	RegisterType_R10 = 2 | RegisterType_x64Extend,
	RegisterType_R11 = 3 | RegisterType_x64Extend,
	RegisterType_R12 = 4 | RegisterType_x64Extend, // Increadibly volatile with dereferencing, requires multiple bytes to use, not recomended
	RegisterType_R13 = 5 | RegisterType_x64Extend, // Less volatile, but still has an annoying trate of dereferencing
	RegisterType_R14 = 6 | RegisterType_x64Extend,
	RegisterType_R15 = 7 | RegisterType_x64Extend,

	RegisterType_Invalid = (unsigned char)~0,
	RegisterType_None = RegisterType_Invalid
};

enum RegisterMask
{
	RegisterMask_None = 0,

	RegisterMask_RAX = (1 << 0),
	RegisterMask_RCX = (1 << 1),
	RegisterMask_RDX = (1 << 2),
	RegisterMask_RBX = (1 << 3),
	RegisterMask_RSP = (1 << 4), // Just a bad idea to specify anywhere, you'll most likely end up corrupting the execution
	RegisterMask_RBP = (1 << 5), // Not recomended for pointer use
	RegisterMask_RSI = (1 << 6),
	RegisterMask_RDI = (1 << 7),

	RegisterMask_R8 = (1 << 8),
	RegisterMask_R9 = (1 << 9),
	RegisterMask_R10 = (1 << 10),
	RegisterMask_R11 = (1 << 11),
	RegisterMask_R12 = (1 << 12), // Increadibly volatile with dereferencing, requires multiple bytes to use, not recomended
	RegisterMask_R13 = (1 << 13), // Less volatile, but still has an annoying trate of dereferencing
	RegisterMask_R14 = (1 << 14),
	RegisterMask_R15 = (1 << 15),
};