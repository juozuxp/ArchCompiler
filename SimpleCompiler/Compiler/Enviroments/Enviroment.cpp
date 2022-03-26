#include "Enviroment.h"

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

		for (; *RunEnviroment && *RunEnviroment != '\t'; RunEnviroment++, Length++)
		{
			if (*RunEnviroment == ';')
			{
				RunEnviroment++;
				Length++;
				break;
			}
		}

		Evaluated.Add(Start, Length);
	}

	if (Length)
		*Length = RunEnviroment - Enviroment;

	Evaluated.Add('\0');
	return Evaluated;
}