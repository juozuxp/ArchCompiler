#include "EnviromentMap.h"
#include "../CompileMap.h"
#include "../../Utilities/StrTok.h"
#include "../../Parser/Types/FunctionCall.h"
#include "../../Parser/Types/LocalVariable.h"
#include "../../Parser/Types/Conditional.h"

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
	for (StrTok::CommmitIterator::Commitable Token : StrTok(Expression, ";").GetCommitable())
	{
		RefObject<ParserElement> Object;

		if (Conditional::IsConditional(Token.GetToken()))
		{
			Token.SkipFor(Conditional::ExpressionSize(Token.GetToken()));
			continue;
		}

		Token.CommitToken();

		if (Variable::IsVariable(Token.GetToken()))
		{
			RefObject<LocalVariable> Variable = RefObject<LocalVariable>(LocalVariable(Token.GetToken()));

			AddVariable(Variable.Cast<::Variable>());

			Variable->Parse(*this, Token.GetToken());
		}
		else if (Arithmetic::IsArtimetic(Token.GetToken()))
		{
			RefObject<Arithmetic> Expression = RefObject<Arithmetic>(Arithmetic());

			AddParsed(Expression.Cast<ParserElement>());

			Expression->Parse(*this, Token.GetToken());
		}
		else if (FunctionCall::IsFunctionCall(Token.GetToken()))
		{
			RefObject<FunctionCall> Expression = RefObject<FunctionCall>(FunctionCall());

			AddParsed(Expression.Cast<ParserElement>());

			Expression->Parse(*this, Token.GetToken());
		}
	}
}

void EnviromentMap::Compile(CompileMap& Enviroment)
{
	for (RefObject<ParserElement> Element : ParseElements)
		Element->Compile(Enviroment);
}

unsigned short EnviromentMap::EstimateRegisterUsage() const
{
	unsigned short Mask = 0;
	for (RefObject<ParserElement> Element : ParseElements)
		Mask |= Element->GetRegisterMask();

	return Mask;
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

	return StackSize;
}