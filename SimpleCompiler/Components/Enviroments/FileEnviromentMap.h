#pragma once
#include "EnviromentMap.h"
#include "Enviroment.h"
#include "../Types/Function.h"
#include "../Types/String.h"
#include "../Types/Import.h"

class FileEnviromentMap : public Enviroment
{
public:
	FileEnviromentMap();

public:
	void Compile(class CompileMap& Enviroment);

	void Parse(const char* Expression, RefObject<Enviroment> Current);

	void AddImport(RefObject<Import> Import);
	void AddFunction(RefObject<Function> Function);

	bool IsUnderlying();

	RefObject<String> GetString(const char* String, unsigned long long Length = 0);

public:
	constexpr HashMap<char, List<RefObject<Import>>>::ValueIterator GetImportIterator() const
	{
		return Imports.GetIterator();
	}
	
	constexpr unsigned long GetImportCount() const
	{
		return Imports.GetEntryCount();
	}

private:
	static List<char> SmartDeflate(const char* Expression);

public:
	List<RefObject<Function>> Functions;

	HashMap<char, RefObject<String>> Strings;
	HashMap<char, List<RefObject<Import>>> Imports;
};