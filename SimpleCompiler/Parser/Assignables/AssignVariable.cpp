#include "AssignVariable.h"

void AssignVariable::Compile(CompileMap& Enviroment)
{
	Variable->CompileAssign(Enviroment);
}