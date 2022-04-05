#pragma once
#include <Windows.h>
#include "CompilerProduct.h"

class PEBuilder
{
public:
	constexpr PEBuilder()
	{
	}

	inline PEBuilder(const CompilerProduct& CompilerMap) : CompilerMap(CompilerMap)
	{
	}

	PEBuilder(const char* Code);

public:
	void BuildExecutable(const char* Path);

private:
	List<unsigned char> BuildHeader();

	void BuildDosHeader(IMAGE_DOS_HEADER* DosHeader);
	void BuildNTHeader(IMAGE_NT_HEADERS64* NTHeader);
	void BuildFileHeader(IMAGE_FILE_HEADER* FileHeader);
	void BuildSectionHeaders(IMAGE_SECTION_HEADER* SectionHeaders);
	void BuildOptionalHeader(IMAGE_OPTIONAL_HEADER64* OptionalHeader);

private:
	CompilerProduct CompilerMap;

private:
	static constexpr unsigned long long StackCommit = 0x1000;
	static constexpr unsigned long long StackReserve = 0x10000;

	static constexpr unsigned long long HeapCommit = 0x1000;
	static constexpr unsigned long long HeapReserve = 0x1000;

	static constexpr unsigned long FileAlignment = 0x400;
	static constexpr unsigned long MemoryAlignment = 0x1000;
};