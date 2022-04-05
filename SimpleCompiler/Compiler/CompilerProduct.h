#pragma once
#include "../Components/Enviroments/FileEnviromentMap.h"
#include "../Utilities/RefObject.h"
#include "../Utilities/List.h"

class CompilerProduct
{
public:
	constexpr CompilerProduct()
	{
	}

	CompilerProduct(RefObject<FileEnviromentMap> Enviroment, const List<unsigned char>& Code);
	
public:
	const List<unsigned char>& GetByteCode();
	RefObject<class Function> GetFunction(const char* Function);

public:
	constexpr unsigned long GetSectionCount()
	{
		return 1;
	}

private:
	List<unsigned char> ByteCode;
	RefObject<FileEnviromentMap> Enviroment;
};