#include "Enviroment.h"
#include "../Types/Variable.h"
#include "../Types/String.h"
#include "../Types/ForLoop.h"

void Enviroment::PreCompile(class CompileMap& Enviroment)
{
}

void Enviroment::Compile(class CompileMap& Enviroment)
{
}

void Enviroment::PostCompile(class CompileMap& Enviroment)
{
}

void Enviroment::Parse(const char* Expression, RefObject<Enviroment> This)
{
}

bool Enviroment::IsUnderlying()
{
	return false;
}

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

RefObject<String> Enviroment::GetString(const char* String, unsigned long long Length)
{
	return RefObject<::String>();
}

void Enviroment::AddConstantValue(unsigned long long Value, const char* Name, unsigned long long Length)
{
	if (!Length)
		Length = strlen(Name);

	ConstantValues.Add(Name, Length, Value);
}

bool Enviroment::GetConstantValue(unsigned long long* Value, const char* Name, unsigned long long Length) const
{
	unsigned long long Index;
	if (!Length)
		Length = strlen(Name);

	Index = ConstantValues.GetIndex(Name, Length);
	if (Index == ~0ull)
		return false;

	if (Value)
		*Value = ConstantValues.GetByIndex(Index);

	return true;
}

unsigned long Enviroment::GetTermDefintionSize(const char* Expression)
{
	for (unsigned long i = 0; *Expression; i++, Expression++)
	{
		if (*Expression == ';')
			return i + 1;
	}

	return 0;
}

unsigned long Enviroment::EstimateSubEnviromentSize(const char* Expression)
{
	const char* RunEnviroment = Expression;
	while (*RunEnviroment)
	{
		if (*RunEnviroment != '\t')
			break;

		for (RunEnviroment++; *RunEnviroment; RunEnviroment++)
		{
			if (*RunEnviroment != '\t')
				break;
		}

		for (; *RunEnviroment; RunEnviroment++)
		{
			if (*RunEnviroment == ';' || *RunEnviroment == '\t')
			{
				RunEnviroment++;
				break;
			}
		}
	}

	return RunEnviroment - Expression;
}

List<char> Enviroment::ExtractSubEnviroment(const char* Enviroment, unsigned long long* Length)
{
	List<char> Evaluated = List<char>(0);

	const char* RunEnviroment = Enviroment;
	while (*RunEnviroment)
	{
		if (*RunEnviroment != '\t')
			break;

		const char* Start = RunEnviroment + 1;

		unsigned long long Length = 0;
		for (RunEnviroment++; *RunEnviroment; RunEnviroment++, Length++)
		{
			if (*RunEnviroment != '\t')
				break;
		}

		if (ForLoop::IsExpression(RunEnviroment))
		{
			unsigned long long ExpressionLength = ForLoop::ExpressionLength(RunEnviroment);

			RunEnviroment += ExpressionLength;
			Length += ExpressionLength;
		}
		else
		{
			for (; *RunEnviroment && *RunEnviroment != '\t'; RunEnviroment++, Length++)
			{
				if (*RunEnviroment == ';')
				{
					RunEnviroment++;
					Length++;
					break;
				}
			}
		}

		Evaluated.Add(Start, Length);
	}

	if (Length)
		*Length = RunEnviroment - Enviroment;

	Evaluated.Add('\0');
	return Evaluated;
}