#include "CompilerProduct.h"
#include "../Components/Types/Function.h"

CompilerProduct::CompilerProduct(RefObject<FileEnviromentMap> Enviroment, const List<unsigned char>& Code)
{
	this->ByteCode = Code;
	this->Enviroment = Enviroment;
}

const List<unsigned char>& CompilerProduct::GetByteCode()
{
	return ByteCode;
}

RefObject<Function> CompilerProduct::GetFunction(const char* Function)
{
	return Enviroment->GetVariable(Function).Cast<::Function>();
}