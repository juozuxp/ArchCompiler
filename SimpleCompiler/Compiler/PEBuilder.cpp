#include "PEBuilder.h"
#include <Windows.h>

void PEBuilder::TestBuild()
{
	unsigned char Header[sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS64) + sizeof(IMAGE_SECTION_HEADER) * 2]; // 2 sections, 1 data, 1 code

	IMAGE_OPTIONAL_HEADER64* OptionalHeader;
	IMAGE_SECTION_HEADER* SectionHeader;
	IMAGE_NT_HEADERS64* NTHeaders;
	IMAGE_FILE_HEADER* FileHeader;
	IMAGE_DOS_HEADER* DosHeader;

	memset(Header, 0, sizeof(Header));

	DosHeader = (IMAGE_DOS_HEADER*)Header;
	NTHeaders = (IMAGE_NT_HEADERS64*)(Header + sizeof(IMAGE_DOS_HEADER));
	FileHeader = &NTHeaders->FileHeader;
	OptionalHeader = &NTHeaders->OptionalHeader;
	SectionHeader = (IMAGE_SECTION_HEADER*)(Header + sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS64));

	DosHeader->e_magic = *(unsigned short*)"MZ";
	DosHeader->e_lfanew = sizeof(IMAGE_DOS_HEADER);

	NTHeaders->Signature = *(unsigned long*)"PE\0\0";

	FileHeader->Machine = IMAGE_FILE_MACHINE_AMD64;
	FileHeader->NumberOfSections = 2;
	FileHeader->SizeOfOptionalHeader = sizeof(IMAGE_OPTIONAL_HEADER64);
	FileHeader->Characteristics = IMAGE_FILE_EXECUTABLE_IMAGE | IMAGE_FILE_DEBUG_STRIPPED;
}