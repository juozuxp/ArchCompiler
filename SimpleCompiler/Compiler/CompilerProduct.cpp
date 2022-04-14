#include "CompilerProduct.h"
#include "../Components/Types/Function.h"

CompilerProduct::CompilerProduct(RefObject<FileEnviromentMap> Enviroment, const List<unsigned char>& Code, const List<unsigned char>& StaticData)
{
	this->ByteCode = Code;
	this->StaticData = StaticData;
	this->Enviroment = Enviroment;
}

unsigned long CompilerProduct::GetImportCount() const
{
	return Enviroment->GetImportCount();
}

const List<unsigned char>& CompilerProduct::GetByteCode() const
{
	return ByteCode;
}

const List<unsigned char>& CompilerProduct::GetStaticData() const
{
	return StaticData;
}

RefObject<Function> CompilerProduct::GetFunction(const char* Function) const
{
	return Enviroment->GetVariable(Function).Cast<::Function>();
}

HashMap<char, List<RefObject<Import>>>::ValueIterator CompilerProduct::GetImportIterator() const
{
	return Enviroment->GetImportIterator();
}