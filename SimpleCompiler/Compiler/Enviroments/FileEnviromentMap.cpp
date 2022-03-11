#include "FileEnviromentMap.h"
#include "../CompileMap.h"

void FileEnviromentMap::AddFunction(RefObject<Function> Function)
{
	Functions.Add(Function);
	AddVariable(Function.Cast<Variable>());
}

void FileEnviromentMap::Compile(CompileMap& Enviroment)
{
	for (RefObject<Function> Function : Functions)
		Function->Compile(Enviroment);
}