#include "Compiler.h"
#include "CompileMap.h"

List<unsigned char> Compiler::Compile()
{
	CompileMap CompileEnviroment;

	BaseEnviroment->Compile(CompileEnviroment);

	return CompileEnviroment.GetCode();
}