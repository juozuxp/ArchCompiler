#pragma once
#include "EnviromentMap.h"
#include "Enviroment.h"

class FileEnviromentMap : Enviroment
{
public:
	inline FileEnviromentMap() : FunctionMaps(List<RefObject<EnviromentMap>>(0))
	{
	}

public:
	void AddEnviroment(RefObject<EnviromentMap> Enviroment);

public:
	List<RefObject<EnviromentMap>> FunctionMaps;
};