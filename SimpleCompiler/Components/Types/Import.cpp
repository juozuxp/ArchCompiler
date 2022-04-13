#include "Import.h"
#include <string.h>

bool Import::IsExpression(const char* Expression)
{
	Expression = Ignorable.Skip(Expression);
	if (strncmp(Expression, "import", sizeof("import") - 1))
		return false;

	if (!Ignorable.IsSkippable(*(Expression + sizeof("import") - 1)) && *(Expression + sizeof("import") - 1) != '(')
		return false;

	if (!strchr(Expression, '('))
		return false;

	if (!strchr(Expression, ')'))
		return false;

	return true;
}