#include "VariableTypes.h"
#include "../Utilities/SimpleUtilities.h"
#include <string.h>

const VariableType* VariableTypes::RetrieveType(const char* Expression)
{
	for (; *Expression; Expression++)
	{
		if (!IsIgnorable(*Expression))
			break;
	}

	for (unsigned long long i = 0; i < ARRAY_COUNT(Types); i++)
	{
		unsigned long TypeLength = strlen(Types[i].GetName());
		if (!strncmp(Types[i].GetName(), Expression, TypeLength))
		{
			if (!IsIgnorable(Expression[TypeLength]))
				continue;

			return &Types[i];
		}
	}

	return 0;
}

bool VariableTypes::IsIgnorable(char Character)
{
	if (!Character)
		return true;

	for (const char* RunIgnorable = Ignorables; *RunIgnorable; RunIgnorable++)
	{
		if (Character == *RunIgnorable)
			return true;
	}

	return false;
}