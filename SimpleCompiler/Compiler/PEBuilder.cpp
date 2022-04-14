#include "PEBuilder.h"
#include "Compiler.h"
#include "../GlobalInfo/GlobalCompileInfo.h"

PEBuilder::PEBuilder(const char* Code) : CompilerMap(Compiler(Code).Compile())
{
}

List<unsigned char> PEBuilder::BuildHeader()
{
	unsigned char Header[sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS64)];
	List<unsigned char> Result;

	BuildDosHeader((IMAGE_DOS_HEADER*)Header);
	BuildNTHeader((IMAGE_NT_HEADERS64*)(Header + sizeof(IMAGE_DOS_HEADER)));

	Result.Add(Header, sizeof(Header));
	Result.Expand(sizeof(IMAGE_SECTION_HEADER) * CompilerMap.GetSectionCount());

	BuildSectionHeaders((IMAGE_SECTION_HEADER*)(Result.operator unsigned char*() + sizeof(Header)));
	
	Result.Expand(GlobalCompileInfo::FileAlignment - (Result.GetCount() & (GlobalCompileInfo::FileAlignment - 1))); // Header alignment
	return Result;
}

List<unsigned char> PEBuilder::BuildImportLookupTable()
{
	unsigned long long ImportLocation;
	unsigned long long DataLocation;

	List<unsigned char> Result;

	if (!CompilerMap.GetImportCount())
		return Result;

	Result.Expand(sizeof(IMAGE_IMPORT_DESCRIPTOR) * (CompilerMap.GetImportCount() + 1));
	Result.SetAll(CompilerMap.GetImportCount() * sizeof(IMAGE_IMPORT_DESCRIPTOR), 0, sizeof(IMAGE_IMPORT_DESCRIPTOR));
	
	if (Result.GetCount() & (8 - 1))
		Result.Expand(8 - (Result.GetCount() & (8 - 1)));

	ImportLocation = 0;
	DataLocation = GlobalCompileInfo::MemoryAlignment + CompilerMap.GetStaticData().GetCount() + Result.GetCount();
	for (const List<RefObject<Import>>& Imports : CompilerMap.GetImportIterator())
	{
		IMAGE_IMPORT_DESCRIPTOR* ImportDescriptor;

		unsigned long long DynamicData;
		unsigned long long NameLength;
		unsigned long long ThunkData;
		const char* Name;

		Name = Imports[0]->GetSourceName();
		NameLength = strlen(Name) + 1;

		Result.Add((unsigned char*)Name, NameLength);
		Result.Expand(8 - ((NameLength + 8) & (8 - 1)));

		ImportDescriptor = (IMAGE_IMPORT_DESCRIPTOR*)&Result[ImportLocation];

		memset(ImportDescriptor, 0, sizeof(IMAGE_IMPORT_DESCRIPTOR));

		ImportDescriptor->Name = DataLocation;
		ImportDescriptor->ForwarderChain = ~0;
		ImportDescriptor->FirstThunk = GlobalCompileInfo::MemoryAlignment + Imports[0]->GetDataLocation();
		ImportDescriptor->OriginalFirstThunk = DataLocation + (NameLength + (8 - 1)) & ~(8 - 1);

		ThunkData = Result.GetCount();
		Result.Expand((Imports.GetCount() + 1) * sizeof(unsigned long long));
		Result.SetAll(ThunkData + (Imports.GetCount() * sizeof(unsigned long long)), 0, sizeof(unsigned long long));

		DynamicData = Result.GetCount();

		DataLocation += ((NameLength + 8) & ~(8 - 1)) + ((Imports.GetCount() + 1) * sizeof(unsigned long long));
		for (RefObject<Import> Import : Imports)
		{
			IMAGE_IMPORT_BY_NAME* ByName;

			const char* ImportName;

			*(unsigned long long*)&Result[ThunkData] = DataLocation;

			Name = Import->GetFunctionName();
			NameLength = strlen(Name) + 1;

			Result.Expand(((GET_ELEMENT(IMAGE_IMPORT_BY_NAME, Name) + NameLength) + (8 - 1)) & ~(8 - 1));
			ByName = (IMAGE_IMPORT_BY_NAME*)&Result[DynamicData];

			ByName->Hint = 0;
			memcpy(ByName->Name, Name, NameLength);

			ThunkData += sizeof(unsigned long long);
			DynamicData += ((GET_ELEMENT(IMAGE_IMPORT_BY_NAME, Name) + NameLength) + (8 - 1)) & ~(8 - 1);
			DataLocation += ((GET_ELEMENT(IMAGE_IMPORT_BY_NAME, Name) + NameLength) + (8 - 1)) & ~(8 - 1);
		}
	}

	return Result;
}

void PEBuilder::BuildDosHeader(IMAGE_DOS_HEADER* DosHeader)
{
	memset(DosHeader, 0, sizeof(IMAGE_DOS_HEADER));

	DosHeader->e_magic = *(unsigned short*)"MZ";
	DosHeader->e_lfanew = sizeof(IMAGE_DOS_HEADER);
}

void PEBuilder::BuildNTHeader(IMAGE_NT_HEADERS64* NTHeader)
{
	memset(NTHeader, 0, sizeof(IMAGE_NT_HEADERS64));

	NTHeader->Signature = *(unsigned long*)"PE\0\0";
	BuildFileHeader(&NTHeader->FileHeader);
	BuildOptionalHeader(&NTHeader->OptionalHeader);
}

void PEBuilder::BuildFileHeader(IMAGE_FILE_HEADER* FileHeader)
{
	memset(FileHeader, 0, sizeof(IMAGE_FILE_HEADER));

	FileHeader->Machine = IMAGE_FILE_MACHINE_AMD64;
	FileHeader->NumberOfSections = CompilerMap.GetSectionCount();
	FileHeader->SizeOfOptionalHeader = sizeof(IMAGE_OPTIONAL_HEADER64);
	FileHeader->Characteristics = IMAGE_FILE_EXECUTABLE_IMAGE | IMAGE_FILE_DEBUG_STRIPPED;
}

void PEBuilder::BuildSectionHeaders(IMAGE_SECTION_HEADER* SectionHeaders)
{
	unsigned long long HeaderSize;

	memset(SectionHeaders, 0, sizeof(IMAGE_SECTION_HEADER) * CompilerMap.GetSectionCount());

	HeaderSize = sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS64) + sizeof(IMAGE_SECTION_HEADER) * CompilerMap.GetSectionCount();

	SectionHeaders[0].Misc.VirtualSize = CompilerMap.GetStaticData().GetCount();
	SectionHeaders[0].VirtualAddress = (HeaderSize + (GlobalCompileInfo::MemoryAlignment - 1)) & ~(GlobalCompileInfo::MemoryAlignment - 1); // start
	SectionHeaders[0].SizeOfRawData = (CompilerMap.GetStaticData().GetCount() + GlobalCompileInfo::FileAlignment) & ~(GlobalCompileInfo::FileAlignment - 1);
	SectionHeaders[0].PointerToRawData = (HeaderSize + (GlobalCompileInfo::FileAlignment - 1)) & ~(GlobalCompileInfo::FileAlignment - 1);
	SectionHeaders[0].Characteristics = IMAGE_SCN_CNT_INITIALIZED_DATA | IMAGE_SCN_MEM_WRITE | IMAGE_SCN_MEM_READ;

	strcpy((char*)SectionHeaders[0].Name, ".darch");

	SectionHeaders[1].Misc.VirtualSize = CompilerMap.GetByteCode().GetCount();
	SectionHeaders[1].VirtualAddress = SectionHeaders[0].VirtualAddress + ((SectionHeaders[0].SizeOfRawData + (GlobalCompileInfo::MemoryAlignment - 1)) & ~(GlobalCompileInfo::MemoryAlignment - 1));
	SectionHeaders[1].SizeOfRawData = (CompilerMap.GetByteCode().GetCount() + (GlobalCompileInfo::FileAlignment - 1)) & ~(GlobalCompileInfo::FileAlignment - 1);
	SectionHeaders[1].PointerToRawData = SectionHeaders[0].PointerToRawData + SectionHeaders[1].SizeOfRawData;
	SectionHeaders[1].Characteristics = IMAGE_SCN_CNT_CODE | IMAGE_SCN_MEM_EXECUTE | IMAGE_SCN_MEM_READ;

	strcpy((char*)SectionHeaders[1].Name, ".carch");
}

void PEBuilder::BuildOptionalHeader(IMAGE_OPTIONAL_HEADER64* OptionalHeader)
{
	unsigned long long HeaderSize;

	HeaderSize = sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS64) + sizeof(IMAGE_SECTION_HEADER) * CompilerMap.GetSectionCount();

	memset(OptionalHeader, 0, sizeof(IMAGE_OPTIONAL_HEADER64));

	OptionalHeader->Magic = IMAGE_NT_OPTIONAL_HDR64_MAGIC;
	OptionalHeader->SizeOfCode = (CompilerMap.GetByteCode().GetCount() + (GlobalCompileInfo::MemoryAlignment - 1)) & ~(GlobalCompileInfo::MemoryAlignment - 1);
	OptionalHeader->SizeOfInitializedData = (CompilerMap.GetStaticData().GetCount() + (GlobalCompileInfo::MemoryAlignment - 1)) & ~(GlobalCompileInfo::MemoryAlignment - 1);
	OptionalHeader->AddressOfEntryPoint = GlobalCompileInfo::MemoryAlignment + OptionalHeader->SizeOfInitializedData + CompilerMap.GetFunction("main")->GetRelativeLocation();
	OptionalHeader->BaseOfCode = GlobalCompileInfo::MemoryAlignment + OptionalHeader->SizeOfInitializedData;
	OptionalHeader->ImageBase = 0;
	OptionalHeader->FileAlignment = GlobalCompileInfo::FileAlignment;
	OptionalHeader->SectionAlignment = GlobalCompileInfo::MemoryAlignment;
	OptionalHeader->MajorOperatingSystemVersion = 6; // Windows vista version
	OptionalHeader->MinorOperatingSystemVersion = 0;
	OptionalHeader->MajorSubsystemVersion = 6; // Default subsystem
	OptionalHeader->MinorSubsystemVersion = 0;
	OptionalHeader->SizeOfImage = OptionalHeader->SizeOfCode + OptionalHeader->SizeOfInitializedData + (HeaderSize + (GlobalCompileInfo::MemoryAlignment - 1)) & ~(GlobalCompileInfo::MemoryAlignment - 1); // Sum of the entiere image
	OptionalHeader->SizeOfHeaders = (HeaderSize + (GlobalCompileInfo::FileAlignment - 1)) & ~(GlobalCompileInfo::FileAlignment - 1);
	OptionalHeader->Subsystem = IMAGE_SUBSYSTEM_WINDOWS_CUI; // Console subsystem
	OptionalHeader->DllCharacteristics = IMAGE_DLLCHARACTERISTICS_NO_SEH /*(Remove if try and except will be done)*/ | IMAGE_DLLCHARACTERISTICS_NX_COMPAT | IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE;
	OptionalHeader->SizeOfStackReserve = GlobalCompileInfo::StackReserve;
	OptionalHeader->SizeOfStackCommit = GlobalCompileInfo::StackCommit;
	OptionalHeader->SizeOfHeapReserve = GlobalCompileInfo::HeapReserve;
	OptionalHeader->SizeOfHeapCommit = GlobalCompileInfo::HeapCommit;

	if (CompilerMap.GetImportCount())
	{
		OptionalHeader->NumberOfRvaAndSizes = 1; // Number of DataDirectory objects

		OptionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].Size = (CompilerMap.GetImportCount() + 1) * sizeof(IMAGE_IMPORT_DESCRIPTOR);
		OptionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress = GlobalCompileInfo::MemoryAlignment + CompilerMap.GetStaticData().GetCount();
	}
	else
		OptionalHeader->NumberOfRvaAndSizes = 0; // Number of DataDirectory objects
}

//void PEBuilder::TestBuild()
//{
//
//	IMAGE_OPTIONAL_HEADER64* OptionalHeader;
//	IMAGE_SECTION_HEADER* SectionHeader;
//	IMAGE_NT_HEADERS64* NTHeaders;
//	IMAGE_FILE_HEADER* FileHeader;
//	IMAGE_DOS_HEADER* DosHeader;
//
//	memset(Header, 0, sizeof(Header));
//
//	DosHeader = (IMAGE_DOS_HEADER*)Header;
//	NTHeaders = ;
//	FileHeader = &NTHeaders->FileHeader;
//	OptionalHeader = &NTHeaders->OptionalHeader;
//	SectionHeader = (IMAGE_SECTION_HEADER*)(Header + sizeof(IMAGE_DOS_HEADER) + sizeof(IMAGE_NT_HEADERS64));
//
//
//
//	HANDLE FileHandle = CreateFileA("test.exe", GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
//	if (!FileHandle)
//		return;
//
//	unsigned char Exe[0x800];
//
//	memcpy(Exe, Header, sizeof(Header));
//	WriteFile(FileHandle, Exe, sizeof(Exe), 0, 0);
//
//	CloseHandle(FileHandle);
//}

void PEBuilder::BuildExecutable(const char* Path)
{
	List<unsigned char> FileBuffer;
	List<char> DynPath;
	HANDLE FileHandle;

	DynPath.Add(Path, strlen(Path));
	if (!strstr(Path, ".exe"))
		DynPath.Add(".exe", sizeof(".exe") - 1);

	DynPath.Add('\0');

	FileBuffer.Add(BuildHeader());

	FileBuffer.Add(CompilerMap.GetStaticData());
	FileBuffer.Add(BuildImportLookupTable());
	FileBuffer.Expand(GlobalCompileInfo::FileAlignment - (FileBuffer.GetCount() & (GlobalCompileInfo::FileAlignment - 1))); // SectionAlignment

	FileBuffer.Add(CompilerMap.GetByteCode());
	FileBuffer.Expand(GlobalCompileInfo::FileAlignment - (FileBuffer.GetCount() & (GlobalCompileInfo::FileAlignment - 1))); // SectionAlignment

	FileHandle = CreateFileA(DynPath, GENERIC_WRITE, FILE_SHARE_READ, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	if (FileHandle == INVALID_HANDLE_VALUE)
		return;

	if (!WriteFile(FileHandle, FileBuffer, FileBuffer.GetCount(), 0, 0))
	{
		CloseHandle(FileHandle);
		return;
	}

	CloseHandle(FileHandle);
}