#pragma once

class VariableType
{
public:
	constexpr VariableType()
	{
	}

	constexpr VariableType(const char* Name, unsigned long long Size) : Name(Name), Size(Size)
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

private:
	const char* Name = 0;
	unsigned long long Size = 0;
};

class VariableTypes
{
public:
	static const VariableType* RetrieveType(const char* Expression);

private:
	static bool IsIgnorable(char Character);

private:
	constexpr static const char* Ignorables = "* ;=";
	constexpr static VariableType Types[] = { VariableType("void", 0), VariableType("uchar", 1), VariableType("ushort", 2), VariableType("uint", 4), VariableType("ulong", 8) };
};

