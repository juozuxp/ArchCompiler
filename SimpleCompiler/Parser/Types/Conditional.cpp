#include "Conditional.h"
#include <string.h>
#include "../../Compiler/Enviroments/Enviroment.h"

bool Conditional::IsConditional(const char* Expression)
{
	Expression = Ignorable.Skip(Expression);
	if (strncmp(Expression, "if", sizeof("if") - 1))
		return false;

	if (!Ignorable.IsSkippable(*(Expression + sizeof("if") - 1)))
		return false;

	if (!strchr(Expression, '('))
		return false;

	if (!strchr(Expression, ')'))
		return false;

	return true;
}

unsigned long Conditional::ExpressionSize(const char* Expression)
{
	const char* EndIf = strrchr(Expression, ')') + 1;
	return (EndIf - Expression) + Enviroment::EstimateSubEnviromentSize(EndIf);
}