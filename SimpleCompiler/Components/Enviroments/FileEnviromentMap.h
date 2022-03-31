#pragma once
#include "EnviromentMap.h"
#include "Enviroment.h"
#include "../Types/Function.h"

class FileEnviromentMap : public Enviroment
{
public:
	FileEnviromentMap();

public:
	void Compile(class CompileMap& Enviroment);

	void Parse(const char* Expression, RefObject<Enviroment> Current);

	void AddFunction(RefObject<Function> Function);

public:
	List<RefObject<Function>> Functions;
};