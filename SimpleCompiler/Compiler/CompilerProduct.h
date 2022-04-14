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
	unsigned long GetImportCount() const;

	const List<unsigned char>& GetByteCode() const;
	const List<unsigned char>& GetStaticData() const;

	RefObject<class Function> GetFunction(const char* Function) const;

	HashMap<char, List<RefObject<Import>>>::ValueIterator GetImportIterator() const;

public:
	constexpr unsigned long GetSectionCount() const
	{
		return 2;
	}

private:
	List<unsigned char> ByteCode;
	List<unsigned char> StaticData;

	RefObject<FileEnviromentMap> Enviroment;
};