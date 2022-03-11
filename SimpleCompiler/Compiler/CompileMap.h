#pragma once
#include "../Utilities/List.h"

class CompileMap
{
public:
	constexpr CompileMap()
	{
	}

public:
	inline void AddCode(List<unsigned char> Code)
	{
		CompiledCode.Add(Code);
	}

	inline void AddCode(const unsigned char* Code, unsigned long long Size)
	{
		CompiledCode.Add(Code, Size);
	}

	inline List<unsigned char> GetCode()
	{
		return CompiledCode;
	}

public:
	constexpr void SetStack(unsigned long long Size)
	{
		StackSize = Size;
	}

	constexpr unsigned long long AllocateLocalVariable(unsigned long long Size)
	{
		return StackSize -= Size;
	}

	constexpr unsigned long long GetRelativeLocation()
	{
		return CompiledCode.GetCount();
	}

private:
	List<unsigned char> CompiledCode;

	unsigned long long StackSize = 0;
};