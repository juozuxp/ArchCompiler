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

	PEBuilder(const char* Buffer, bool FilePath = false);

public:
	void BuildExecutable(const char* Path);

private:
	List<unsigned char> BuildHeader();
	List<unsigned char> BuildImportLookupTable();

	void BuildDosHeader(IMAGE_DOS_HEADER* DosHeader);
	void BuildNTHeader(IMAGE_NT_HEADERS64* NTHeader);
	void BuildFileHeader(IMAGE_FILE_HEADER* FileHeader);
	void BuildSectionHeaders(IMAGE_SECTION_HEADER* SectionHeaders);
	void BuildOptionalHeader(IMAGE_OPTIONAL_HEADER64* OptionalHeader);

private:
	CompilerProduct CompilerMap;
};