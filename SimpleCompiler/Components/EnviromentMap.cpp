#include "EnviromentMap.h"

void EnviromentMap::AddVariable(RefObject<Variable> Element)
{
	const char* VarName;

	VarName = Element->GetVariableName();

	Variables.Add(VarName, strlen(VarName), Element);
	AddParsed(Element.Cast<ParserElement>());
}

RefObject<Variable> EnviromentMap::GetVariable(const char* Name, unsigned long long Length) const
{
	unsigned long long Index;
	if (!Length)
		Length = strlen(Name);

	Index = Variables.GetIndex(Name, Length);
	if (Index == ~0)
		return Parent->GetVariable(Name, Length);

	return Variables.GetByIndex(Index);
}

void EnviromentMap::AddParsed(RefObject<ParserElement> Element)
{
	ParseElements.Add(Element);
}