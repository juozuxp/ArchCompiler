#include "Function.h"
#include "../../GlobalInfo/VariableTypes.h"

Function::Function(const char* Expression)
{

}

bool Function::IsFunctionDefinition(const char* Expression)
{
	const VariableType* Type = VariableTypes::RetrieveType(Expression);
	if (!Type)
		return false;

	for (Expression += strlen(Type->GetName()); IsIgnorable(*Expression); Expression++);
	for (; *Expression && !IsIgnorable(*Expression); Expression++)
	{
		if (*Expression == '(')
			return true;
	}

	return false;
}

unsigned long long Function::GetDefinitionLength(const char* Expression)
{
	for (unsigned long long i = 0; *Expression; Expression++, i++)
	{
		if (*Expression == ')')
			return i + 1;
	}

	return 0;
}

List<char> Function::ExtractName(const char* Expression)
{
	List<char> Name = List<char>(10);

	const char* RunName = Expression;

	for (; IsIgnorable(*RunName); RunName++);
	for (; !IsIgnorable(*RunName); RunName++)
		Name.Add(*RunName);

	Name.Add('\0');

	return Name;
}