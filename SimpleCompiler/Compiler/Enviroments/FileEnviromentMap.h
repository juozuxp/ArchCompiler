#pragma once
#include "EnviromentMap.h"
#include "Enviroment.h"
#include "../../Parser/Types/Function.h"

class FileEnviromentMap : public Enviroment
{
public:
	inline FileEnviromentMap() : Enviroment()
	{
	}

public:
	void Compile(class CompileMap& Enviroment);

	void AddFunction(RefObject<Function> Function);

public:
	List<RefObject<Function>> Functions;
};