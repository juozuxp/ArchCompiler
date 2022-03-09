#include "EnviromentMap.h"

RefObject<Variable> EnviromentMap::GetVariable(const char* Name, unsigned long long Length)
{
	if (!Length)
		Length = strlen(Name);

	return Variables.Get(Name, Length);
}

void EnviromentMap::AddParsed(RefObject<ParserElement> Element)
{
	ParseElements.Add(Element);
}

void EnviromentMap::AddVariable(RefObject<Variable> Element)
{
	const char* VarName;

	VarName = Element->GetVariableName();

	ParseElements.Add(Element.Cast<ParserElement>());
	Variables.Add(VarName, strlen(VarName), Element);
}