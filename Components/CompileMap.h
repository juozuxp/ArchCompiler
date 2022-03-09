#pragma once

class CompileMap
{
public:
	constexpr CompileMap()
	{
	}

	constexpr CompileMap(unsigned long long StackSize) : VarStackOffset(StackSize)
	{
	}

public:
	constexpr unsigned long long AllocateLocalVariable(unsigned long long Size)
	{
		return VarStackOffset -= Size;
	}

private:
	unsigned long long VarStackOffset = 0;
};