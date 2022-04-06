#pragma once
#include "EnviromentMap.h"
#include "Enviroment.h"
#include "../Types/Function.h"
#include "../Types/String.h"

class FileEnviromentMap : public Enviroment
{
public:
	FileEnviromentMap();

public:
	void Compile(class CompileMap& Enviroment);

	void Parse(const char* Expression, RefObject<Enviroment> Current);

	void AddFunction(RefObject<Function> Function);

	bool IsUnderlying();

	RefObject<String> GetString(const char* String, unsigned long long Length = 0);

public:
	List<RefObject<Function>> Functions;
	HashMap<char, RefObject<String>> Strings;
};