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
	void AssembleEnd(class CompileMap& Enviroment);
	void AssembleStart(class CompileMap& Enviroment);

private:
	void CreateStackAlloc(class CompileMap& Enviroment);
	void CreateStackDealloc(class CompileMap& Enviroment);

private:
	unsigned long long EnvStackSize = 0;
};