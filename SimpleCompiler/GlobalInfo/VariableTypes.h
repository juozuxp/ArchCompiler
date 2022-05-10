#pragma once
#include "../Utilities/Skippable.h"

class VariableType
{
public:
	constexpr VariableType()
	{
	}

	constexpr VariableType(const char* Name, unsigned long long Size, bool Signed) : Name(Name), Size(Size), Signed(Signed)
	{
	}

public:
	constexpr const char* GetName() const
	{
		return Name;
	}

	constexpr unsigned long long GetSize() const
	{
		return Size;
	}

	constexpr bool GetSigend() const
	{
		return Signed;
	}

private:
	bool Signed = false;

	const char* Name = 0;
	unsigned long long Size = 0;
};

class VariableTypes
{
public:
	static const VariableType* RetrieveType(const char* Expression);

private:
	constexpr static Skippable Ignorables = Skippable("* ;=");
	constexpr static VariableType Types[] = { VariableType("void", 0, false), VariableType("uchar", 1, false), VariableType("ushort", 2, false), VariableType("uint", 4, false), VariableType("ulong", 8, false), 
											  VariableType("char", 1, true), VariableType("short", 2, true), VariableType("int", 4, true), VariableType("long", 8, true) };
};

