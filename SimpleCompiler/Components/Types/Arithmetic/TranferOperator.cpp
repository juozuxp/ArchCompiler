#include "TranferOperator.h"

void TranferOperator::Compile(CompileMap& Enviroment, RegisterType Source)
{
	this->Source->CompileRetrieve(Enviroment, Source);
}