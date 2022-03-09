#pragma once
#include "../Parser/Types/ParserElement.h"
#include "../Utilities/RefObject.h"
#include "../Components/FileEnviromentMap.h"

class Compiler
{
public:
	Compiler()
	{
	}

	Compiler(RefObject<FileEnviromentMap> CompileElements);

public:
	List<unsigned char> Compile();

private:
	static List<unsigned char> CompileEnviroment(const EnviromentMap& Enviroment);
	static unsigned long long EstimateStackSize(const EnviromentMap& Enviroment);

private:
	RefObject<FileEnviromentMap> Enviroment;
};