#pragma once

class RegisterType // hardcoded due to x86_x64shell volitility
{
public:
	enum Type : unsigned char
	{
		Type_RAX = 0,
		Type_RCX = 1,
		Type_RDX = 2,
		Type_RBX = 3,
		Type_RSP = 4, // Just a bad idea to specify anywhere, you'll most likely end up corrupting the execution
		Type_RBP = 5, // Not recomended for pointer use
		Type_RSI = 6,
		Type_RDI = 7,

		x64Extend = (1 << 3),

		Type_R8 = 0 | x64Extend,
		Type_R9 = 1 | x64Extend,
		Type_R10 = 2 | x64Extend,
		Type_R11 = 3 | x64Extend,
		Type_R12 = 4 | x64Extend, // Increadibly volatile with dereferencing, requires multiple bytes to use, not recomended
		Type_R13 = 5 | x64Extend, // Less volatile, but still has an annoying trate of dereferencing
		Type_R14 = 6 | x64Extend,
		Type_R15 = 7 | x64Extend,

		Invalid = ~0,
		None = Invalid
	};

public:
	constexpr RegisterType()
	{
	}

	constexpr RegisterType(Type Value) : Value(Value)
	{
	}

public:
	operator unsigned char() const
	{
		return Value & (x64Extend - 1);
	}

	constexpr bool operator==(Type Value) const
	{
		return this->Value == Value;
	}

	constexpr bool operator!=(Type Value) const
	{
		return !operator==(Value);
	}

	constexpr bool operator==(RegisterType Value) const
	{
		return this->Value == Value.Value;
	}

	constexpr bool operator!=(RegisterType Value) const
	{
		return !operator==(Value);
	}

	constexpr Type GetType() const
	{
		return Value;
	}

	constexpr bool IsExtended() const
	{
		return Value & x64Extend;
	}

private:
	Type Value = None;
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