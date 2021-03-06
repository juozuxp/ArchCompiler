#include "EnviromentMap.h"
#include "../../Compiler/CompileMap.h"
#include "../../Utilities/StrTok.h"
#include "../Types/FunctionCall.h"
#include "../Types/LocalVariable.h"
#include "../Types/Conditional.h"
#include "../Types/WhileLoop.h"
#include "../Types/FunctionReturn.h"
#include "../Types/String.h"
#include "../Types/ForLoop.h"

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

RefObject<String> EnviromentMap::GetString(const char* String, unsigned long long Length)
{
	return Parent->GetString(String, Length);
}

bool EnviromentMap::GetConstantValue(unsigned long long* Value, const char* Name, unsigned long long Length) const
{
	unsigned long long Index;
	if (!Length)
		Length = strlen(Name);

	Index = ConstantValues.GetIndex(Name, Length);
	if (Index == ~0ull)
		return Parent->GetConstantValue(Value, Name, Length);

	if (Value)
		*Value = ConstantValues.GetByIndex(Index);

	return true;
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

void EnviromentMap::Parse(const char* Expression, RefObject<Enviroment> This)
{
	for (StrTok::CommmitIterator::Commitable Token : StrTok(Expression, ";").GetCommitable())
	{
		if (Conditional::IsConditional(Token.GetToken()))
		{
			RefObject<Conditional> Condition = RefObject<Conditional>(Conditional());

			AddParsed(Condition.Cast<TypeElement>());

			Token.SkipFor(Condition->Parse(This.Cast<EnviromentMap>(), Token.GetToken()));
			continue;
		}
		else if (WhileLoop::IsWhileLoop(Token.GetToken()))
		{
			RefObject<WhileLoop> Loop = RefObject<WhileLoop>(WhileLoop());

			AddParsed(Loop.Cast<TypeElement>());

			Token.SkipFor(Loop->Parse(This.Cast<EnviromentMap>(), Token.GetToken()));
			continue;
		}
		else if (ForLoop::IsExpression(Token.GetToken()))
		{
			RefObject<ForLoop> Loop = RefObject<ForLoop>(ForLoop());

			AddParsed(Loop.Cast<TypeElement>());

			Token.SkipFor(Loop->Parse(This.Cast<EnviromentMap>(), Token.GetToken()));
			continue;
		}

		Token.CommitToken();

		if (Variable::IsVariable(Token.GetToken()))
		{
			RefObject<LocalVariable> Variable = RefObject<LocalVariable>(LocalVariable(Token.GetToken()));

			AddVariable(Variable.Cast<::Variable>());

			Variable->Parse(This.Cast<EnviromentMap>(), Token.GetToken());
		}
		else if (Arithmetic::IsArtimetic(Token.GetToken()))
		{
			RefObject<Arithmetic> Expression = RefObject<Arithmetic>(Arithmetic());

			AddParsed(Expression.Cast<TypeElement>());

			Expression->Parse(This.Cast<EnviromentMap>(), Token.GetToken());
		}
		else if (FunctionCall::IsFunctionCall(Token.GetToken()))
		{
			RefObject<FunctionCall> Expression = RefObject<FunctionCall>(FunctionCall());

			AddParsed(Expression.Cast<TypeElement>());

			Expression->Parse(This.Cast<EnviromentMap>(), Token.GetToken());
		}
		else if (FunctionReturn::IsExpression(Token.GetToken()))
		{
			RefObject<FunctionReturn> Expression = RefObject<FunctionReturn>(FunctionReturn());

			AddParsed(Expression.Cast<TypeElement>());

			Expression->Parse(This.Cast<EnviromentMap>(), Token.GetToken());

			return;
		}
	}
}

void EnviromentMap::PreCompile(CompileMap& Enviroment)
{
	for (RefObject<TypeElement> Element : ParseElements)
	{
		Enviroment.ResetTempStack();
		Element->PreCompile(Enviroment);
	}
}

void EnviromentMap::Compile(CompileMap& Enviroment)
{
	EnviromentEntry = Enviroment.GetCodeLocation();
	for (RefObject<TypeElement> Element : ParseElements)
		Element->Compile(Enviroment);

	EnviromentSize = Enviroment.GetCodeLocation() - EnviromentEntry;
}

void EnviromentMap::PostCompile(CompileMap& Enviroment)
{
	for (RefObject<TypeElement> Element : ParseElements)
		Element->PostCompile(Enviroment);
}

RefObject<EnviromentMap> EnviromentMap::GetBaseEnviroment()
{
	RefObject<EnviromentMap> Base = RefObject<EnviromentMap>();
	for (RefObject<EnviromentMap> Current = Parent.Cast<EnviromentMap>(); !Current->IsUnderlying(); Base = Current, Current = Current->Parent.Cast<EnviromentMap>());

	return Base;
}