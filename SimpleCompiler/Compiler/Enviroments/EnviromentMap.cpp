#include "EnviromentMap.h"
#include "../CompileMap.h"
#include "../Assembler.h"

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

void EnviromentMap::Compile(CompileMap& Enviroment)
{
	unsigned long long StackSize = EstimateStackSize();

	Assembler Assembly = Assembler(StackSize);

	RelativeLocation = Enviroment.GetRelativeLocation();

	Assembly.AssembleStart(Enviroment);

	Enviroment.SetStack(StackSize);
	for (RefObject<ParserElement> Element : ParseElements)
		Element->Compile(Enviroment);

	Assembly.AssembleEnd(Enviroment);
}

unsigned long long EnviromentMap::EstimateStackSize() const
{
	unsigned long long StackSize = 0;
	for (RefObject<ParserElement> Element : ParseElements)
		StackSize += Element->GetStackSize();

	StackSize = (StackSize + ((1 << 3) - 1)) & ~((1 << 3) - 1); // Stack alignment, making sure that it's 8 byte alligned
	StackSize |= (1 << 3); // Stack alignment, making sure the 16 byte missalignment is fixed

	return StackSize;
}