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

	CompilerProduct(RefObject<FileEnviromentMap> Enviroment, const List<unsigned char>& Code, const List<unsigned char>& StaticData);
	
public:
	const List<unsigned char>& GetByteCode();
	const List<unsigned char>& GetStaticData();

	RefObject<class Function> GetFunction(const char* Function);

public:
	constexpr unsigned long GetSectionCount()
	{
		return 2;
	}

private:
	List<unsigned char> ByteCode;
	List<unsigned char> StaticData;

	RefObject<FileEnviromentMap> Enviroment;
};