#pragma once

class GlobalCompileInfo
{
public:
	static constexpr unsigned long long StackCommit = 0x1000;
	static constexpr unsigned long long StackReserve = 0x10000;

	static constexpr unsigned long long HeapCommit = 0x1000;
	static constexpr unsigned long long HeapReserve = 0x1000;

	static constexpr unsigned long FileAlignment = 0x400;
	static constexpr unsigned long MemoryAlignment = 0x1000;
};