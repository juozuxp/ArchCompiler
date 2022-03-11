#include "EnviromentMap.h"
#include "../CompileMap.h"
#include "../../Utilities/StrTok.h"
#include "../../Parser/Types/FunctionCall.h"
#include "../../Parser/Types/LocalVariable.h"

void EnviromentMap::AddVariable(RefObject<Variable> Element)
{
	AddVariableNoCompile(Element);
	AddParsed(Element.Cast<ParserElement>());
}

void EnviromentMap::AddVariableNoCompile(RefObject<Variable> Element)
{
	const char* VarName;

	VarName = Element->GetVariableName();

	Variables.Add(VarName, strlen(VarName), Element);
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

void EnviromentMap::Parse(const char* Expression, RefObject<Enviroment> Current)
{
	for (char* Token : StrTok(Expression, ";"))
	{
		RefObject<ParserElement> Object;

		if (Variable::IsVariable(Token))
		{
			RefObject<LocalVariable> Variable = RefObject<LocalVariable>(LocalVariable(Token));

			AddVariable(Variable.Cast<::Variable>());

			Variable->Parse(*this, Token);
		}
		else if (Arithmetic::IsArtimetic(Token))
		{
			RefObject<Arithmetic> Expression = RefObject<Arithmetic>(Arithmetic());

			AddParsed(Expression.Cast<ParserElement>());

			Expression->Parse(*this, Token);
		}
		else if (FunctionCall::IsFunctionCall(Token))
		{
			RefObject<FunctionCall> Expression = RefObject<FunctionCall>(FunctionCall());

			AddParsed(Expression.Cast<ParserElement>());

			Expression->Parse(*this, Token);
		}
	}
}

void EnviromentMap::Compile(CompileMap& Enviroment)
{
	for (RefObject<ParserElement> Element : ParseElements)
		Element->Compile(Enviroment);
}

unsigned long long EnviromentMap::EstimateStackSize() const
{
	unsigned long long StackSize = 0;
	unsigned long long CallingStackSize = 0;
	for (RefObject<ParserElement> Element : ParseElements)
	{
		unsigned long long CallingStack;

		StackSize += Element->GetStackSize();
		CallingStack = Element->GetCallingStackSize();

		if (CallingStackSize < CallingStack)
			CallingStackSize = CallingStack;
	}

	StackSize += CallingStackSize;
	StackSize = (StackSize + ((1 << 3) - 1)) & ~((1 << 3) - 1); // Stack alignment, making sure that it's 8 byte alligned
	StackSize |= (1 << 3); // Stack alignment, making sure the 16 byte missalignment is fixed

	return StackSize;
}