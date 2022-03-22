#include "VariableTypes.h"
#include "../Utilities/SimpleUtilities.h"
#include <string.h>

const VariableType* VariableTypes::RetrieveType(const char* Expression)
{
	Expression = Ignorables.Skip(Expression);
	for (unsigned long long i = 0; i < ARRAY_COUNT(Types); i++)
	{
		unsigned long TypeLength = strlen(Types[i].GetName());
		if (!strncmp(Types[i].GetName(), Expression, TypeLength))
		{
			if (!Ignorables.IsSkippable(Expression[TypeLength]))
				continue;

			return &Types[i];
		}
	}

	return 0;
}