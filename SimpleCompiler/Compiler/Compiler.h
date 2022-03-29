#pragma once
#include "../Components/Enviroments/FileEnviromentMap.h"
#include "../Utilities/List.h"

class Compiler
{
public:
	inline Compiler(RefObject<FileEnviromentMap> Enviroment) : BaseEnviroment(Enviroment)
	{
	}

public:
	List<unsigned char> Compile();

private:
	RefObject<FileEnviromentMap> BaseEnviroment;
};