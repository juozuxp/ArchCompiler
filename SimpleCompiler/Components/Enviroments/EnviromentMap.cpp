#include "EnviromentMap.h"
#include "../../Compiler/CompileMap.h"
#include "../../Utilities/StrTok.h"
#include "../Types/FunctionCall.h"
#include "../Types/LocalVariable.h"
#include "../Types/Conditional.h"

void EnviromentMap::AddVariable(RefObject<Variable> Element)
{
	AddVariableNoCompile(Element);
	AddParsed(Element.Cast<TypeElement>());
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

void EnviromentMap::AddParsed(RefObject<TypeElement> Element)
{
	ParseElements.Add(Element);
}

void EnviromentMap::Parse(const char* Expression, RefObject<Enviroment> Current)
{
	for (StrTok::CommmitIterator::Commitable Token : StrTok(Expression, ";").GetCommitable())
	{
		if (Conditional::IsConditional(Token.GetToken()))
		{
			RefObject<Conditional> Condition = RefObject<Conditional>(Conditional());

			AddParsed(Condition.Cast<TypeElement>());

			Condition->Parse(*this, Token.GetToken());

			Token.SkipFor(Condition->Parse(*this, Token.GetToken()));
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

			AddParsed(Expression.Cast<TypeElement>());

			Expression->Parse(*this, Token.GetToken());
		}
		else if (FunctionCall::IsFunctionCall(Token.GetToken()))
		{
			RefObject<FunctionCall> Expression = RefObject<FunctionCall>(FunctionCall());

			AddParsed(Expression.Cast<TypeElement>());

			Expression->Parse(*this, Token.GetToken());
		}
	}
}

void EnviromentMap::Compile(CompileMap& Enviroment)
{
	for (RefObject<TypeElement> Element : ParseElements)
		Element->Compile(Enviroment);
}

unsigned short EnviromentMap::EstimateRegisterUsage() const
{
	unsigned short Mask = 0;
	for (RefObject<TypeElement> Element : ParseElements)
		Mask |= Element->GetRegisterMask();

	return Mask;
}

unsigned long long EnviromentMap::EstimateStackSize() const
{
	unsigned long long StackSize = 0;
	unsigned long long CallingStackSize = 0;
	for (RefObject<TypeElement> Element : ParseElements)
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