#include "Function.h"

Function::Function(const char* Expression)
{

}

List<char> Function::ExtractName(const char* Expression)
{
	List<char> Name = List<char>(10);

	const char* RunName = Expression;

	for (; *RunName == ' '; RunName++);
	for (; *RunName != ' '; RunName++)
		Name.Add(*RunName);

	Name.Add('\0');

	return Name;
}