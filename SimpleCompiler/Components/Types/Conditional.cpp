#include "Conditional.h"
#include <string.h>
#include "../../Compiler/Enviroments/Enviroment.h"
#include "../Transferable/TransferRegister.h"

unsigned long long Conditional::Parse(EnviromentMap& Enviroment, const char* Expression)
{
	List<char> SubString;

	unsigned long long Length;

	const char* StartIf;
	const char* EndIf;

	EndIf = strrchr(Expression, ')') + 1;
	StartIf = strchr(Expression, '(');

	SubString.Add(StartIf + 1, EndIf - StartIf - 2);
	SubString.Add('\0');

	Condition = RefObject<Arithmetic>(Arithmetic());
	Condition->Parse(Enviroment, SubString, RefObject<TransferRegister>(TransferRegister(RegisterType::RAX)).Cast<Transferable>());

	Enviroment::ExtractSubEnviroment(EndIf, &Length);
	return (EndIf - Expression) + Length;
}

void Conditional::Compile(CompileMap& Enviroment)
{
	Condition->Compile(Enviroment);
}

bool Conditional::IsConditional(const char* Expression)
{
	Expression = Ignorable.Skip(Expression);
	if (strncmp(Expression, "if", sizeof("if") - 1))
		return false;

	if (!Ignorable.IsSkippable(*(Expression + sizeof("if") - 1)))
		return false;

	if (!strchr(Expression, '('))
		return false;

	if (!strchr(Expression, ')'))
		return false;

	return true;
}