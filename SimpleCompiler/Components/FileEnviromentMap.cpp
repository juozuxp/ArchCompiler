#include "FileEnviromentMap.h"

void FileEnviromentMap::AddEnviroment(RefObject<EnviromentMap> Enviroment)
{
	FunctionMaps.Add(Enviroment);
}