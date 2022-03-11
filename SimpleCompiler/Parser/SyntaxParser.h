#pragma once
#include "../Utilities/RefObject.h"
#include "../Compiler/Enviroments/FileEnviromentMap.h"

class SyntaxParser
{
public:
	static RefObject<FileEnviromentMap> Parse(const char* Expression);
};