#pragma once
#include "../Utilities/List.h"

class Assembler
{
public:
	constexpr Assembler()
	{
	}

	constexpr Assembler(unsigned long long StackSize) : EnvStackSize(StackSize)
	{
	}

public:
	List<unsigned char> AssembleStart();
	List<unsigned char> AssembleEnd();

private:
	List<unsigned char> CreateStackAlloc();
	List<unsigned char> CreateStackDealloc();

private:
	unsigned long long EnvStackSize = 0;
};