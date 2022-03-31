#pragma once
#include "../Utilities/SimpleUtilities.h"

class GlobalConstant
{
public:
	constexpr GlobalConstant()
	{
	}

	constexpr GlobalConstant(unsigned long long Value, const char* Name, unsigned long long Length) : Name(Name), Value(Value), Length(Length)
	{
	}

public:
	constexpr unsigned long long GetValue() const
	{
		return Value;
	}

	constexpr const char* GetName() const
	{
		return Name;
	}

	constexpr unsigned long long GetNameLength() const
	{
		return Length;
	}

private:
	const char* Name = 0;
	unsigned long long Value = 0;
	unsigned long long Length = 0;
};

class GlobalConstants
{
public:
	static constexpr GlobalConstant Constants[] = { GlobalConstant(0, CSL_PAIR("false")), GlobalConstant(1, CSL_PAIR("true")) };
};