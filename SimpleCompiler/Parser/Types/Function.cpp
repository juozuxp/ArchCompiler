#include "Function.h"
#include "../../GlobalInfo/VariableTypes.h"
#include "../../Utilities/StrTok.h"
#include "../../Compiler/Enviroments/EnviromentMap.h"
#include "../../Compiler/CompileMap.h"

#define SHELL_RELATIVITY MainRelativity
#include "../../Utilities/x86_x64Shell.h"

Function::Function(const char* Expression) : Variable(Expression)
{
	ExtractArguments(Expression);
}

void Function::ExtractArguments(const char* Expression)
{
	List<char> IsolateExpression;
	const char* LocatedEnd;

	Expression = strstr(Expression, "(") + 1;
	if (!Expression)
		return;

	LocatedEnd = strstr(Expression, ")");
	if (!LocatedEnd)
		return;

	IsolateExpression.Add(Expression, LocatedEnd - Expression);
	IsolateExpression.Add('\0');

	for (char* Token : StrTok(IsolateExpression, ","))
		Arguments.Add(RefObject<Variable>(Variable(Token)));
}

void Function::BindEnviroment(RefObject<EnviromentMap> Enviroment)
{
	this->Enviroment = Enviroment;
}

void Function::Compile(CompileMap& Enviroment)
{
	this->Enviroment->Compile(Enviroment);
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

void Function::CompileCall(CompileMap& Enviroment)
{
	unsigned long long MainRelativity;

	MainRelativity = 0;
	unsigned char Shell[] =
	{
		CALL_RD(this->Enviroment->RelativeLocation - (Enviroment.GetRelativeLocation() + MainRelativity))
	};

	Enviroment.AddCode(Shell, sizeof(Shell));
}