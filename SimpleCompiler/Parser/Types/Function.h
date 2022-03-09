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

public:
	static bool IsFunctionDefinition(const char* Expression);
	static unsigned long long GetDefinitionLength(const char* Expression);

private:
	List<char> ExtractName(const char* Expression);

private:
	static constexpr bool IsIgnorable(char Character)
	{
		for (const char* RunIgnorable = Ignorable; *RunIgnorable; RunIgnorable++)
		{
			if (*RunIgnorable == Character)
				return true;
		}

		return false;
	}

private:
	List<char> FunctionName;

private:
	static constexpr const char* Ignorable = " \t";
};