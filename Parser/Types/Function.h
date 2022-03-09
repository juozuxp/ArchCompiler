#pragma once
#include "ParserElement.h"
#include "../../Utilities/RefObject.h"

class Function : ParserElement
{
public:
	constexpr Function()
	{
	}

	Function(const char* Expression);

private:
	List<char> ExtractName(const char* Expression);

private:
	List<char> FunctionName;
};