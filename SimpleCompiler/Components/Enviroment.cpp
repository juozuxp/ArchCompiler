#include "Enviroment.h"

RefObject<Variable> Enviroment::GetVariable(const char* Name, unsigned long long Length) const
{
	if (!Length)
		Length = strlen(Name);

	return Variables.Get(Name, Length);
}

void Enviroment::AddVariable(RefObject<Variable> Element)
{
	const char* VarName;

	VarName = Element->GetVariableName();
	Variables.Add(VarName, strlen(VarName), Element);
}