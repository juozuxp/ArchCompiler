#pragma once
#include "../Components/Enviroments/FileEnviromentMap.h"
#include "../Utilities/List.h"

class Compiler
{
public:
	constexpr Compiler()
	{
	}

	inline Compiler(RefObject<FileEnviromentMap> Enviroment) : BaseEnviroment(Enviroment)
	{
	}

	Compiler(const char* Code);

public:
	class CompilerProduct Compile();

private:
	RefObject<FileEnviromentMap> BaseEnviroment;
};