#pragma once
#include "../Utilities/RefObject.h"
#include "../Components/Enviroments/FileEnviromentMap.h"

class SyntaxParser
{
public:
	static RefObject<FileEnviromentMap> Parse(const char* Expression);
	static RefObject<FileEnviromentMap> ParseFile(const char* FilePath);
};