#include "AsignVariable.h"

List<unsigned char> AsignVariable::Compile(class CompileMap& Enviroment)
{
	return Variable->CompileAssign();
}