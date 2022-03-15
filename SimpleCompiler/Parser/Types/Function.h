#pragma once
#include "Argument.h"
#include "../../Utilities/RefObject.h"

class Function : Variable
{
public:
	constexpr Function()
	{
	}

	Function(const char* Expression);

public:
	void ExtractArguments(const char* Expression);
	void BindEnviroment(RefObject<EnviromentMap> Enviroment);

	void Compile(class CompileMap& Enviroment);
	void CompileCall(class CompileMap& Enviroment);
	void CompileRetrieve(class CompileMap& Enviroment, RegisterType Source);

public:
	static bool IsFunctionDefinition(const char* Expression);
	static unsigned long long GetDefinitionLength(const char* Expression);

private:
	void CreateExit(class CompileMap& Enviroment, unsigned short RegisterMask);
	void CreateEntry(class CompileMap& Enviroment, unsigned short RegisterMask);
	void CompileRegisterBackups(class CompileMap& Enviroment, unsigned short Mask);
	void CompileRegisterRestores(class CompileMap& Enviroment, unsigned short Mask);

private:
	static constexpr bool IsIgnorable(char Character)
	{
		for (const char* RunIgnorable = Ignorable; *RunIgnorable; RunIgnorable++)
		{
			if (*RunIgnorable == Character)
				return true;
		}

		return false;
	}

private:
	RefObject<EnviromentMap> Enviroment;
	List<RefObject<Argument>> Arguments;

private:
	static constexpr const char* Ignorable = " \t";
};