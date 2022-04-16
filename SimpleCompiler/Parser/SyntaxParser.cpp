#include "SyntaxParser.h"
#include <Windows.h>

RefObject<FileEnviromentMap> SyntaxParser::Parse(const char* Expression)
{
	RefObject<FileEnviromentMap> Enviroment = RefObject<FileEnviromentMap>(FileEnviromentMap());

	Enviroment->Parse(Expression, Enviroment.Cast<::Enviroment>());

	return Enviroment;
}

RefObject<FileEnviromentMap> SyntaxParser::ParseFile(const char* FilePath)
{
	RefObject<FileEnviromentMap> Result;
	HANDLE FileHandle;
	
	unsigned long long FileSize;
	char* FileBuffer;

	FileHandle = CreateFileA(FilePath, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (!FileHandle || FileHandle == INVALID_HANDLE_VALUE)
		return RefObject<FileEnviromentMap>();

	FileSize = GetFileSize(FileHandle, 0);
	if (!FileSize)
		return RefObject<FileEnviromentMap>();

	FileBuffer = (char*)malloc(FileSize + 1);
	if (!FileBuffer)
		return RefObject<FileEnviromentMap>();

	if (!ReadFile(FileHandle, FileBuffer, FileSize, 0, 0))
		return RefObject<FileEnviromentMap>();

	CloseHandle(FileHandle);

	FileBuffer[FileSize] = '\0';

	Result = Parse(FileBuffer);

	free(FileBuffer);
	return Result;
}