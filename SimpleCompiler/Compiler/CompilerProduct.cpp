#include "CompilerProduct.h"
#include "../Components/Types/Function.h"

CompilerProduct::CompilerProduct(RefObject<FileEnviromentMap> Enviroment, const List<unsigned char>& Code, const List<unsigned char>& StaticData)
{
	this->ByteCode = Code;
	this->StaticData = StaticData;
	this->Enviroment = Enviroment;
}

const List<unsigned char>& CompilerProduct::GetByteCode()
{
	return ByteCode;
}

const List<unsigned char>& CompilerProduct::GetStaticData()
{
	return StaticData;
}

RefObject<Function> CompilerProduct::GetFunction(const char* Function)
{
	return Enviroment->GetVariable(Function).Cast<::Function>();
}