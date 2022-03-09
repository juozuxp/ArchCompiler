#pragma once
#include "../Parser/Types/ParserElement.h"
#include "../Utilities/RefObject.h"
#include "../Components/EnviromentMap.h"

class Compiler
{
public:
	Compiler()
	{
	}

	Compiler(const EnviromentMap& CompileElements);

public:
	List<unsigned char> Compile();

private:
	List<unsigned char> CompileEnviroment();

private:
	unsigned long long EstimateStackSize();

private:
	EnviromentMap Enviroment;
	unsigned long long StackSize = 0;
};