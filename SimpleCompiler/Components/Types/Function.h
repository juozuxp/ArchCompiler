#pragma once
#include "../../Utilities/RefObject.h"
#include "../../Utilities/Skippable.h"
#include "../../Utilities/List.h"
#include "Variable.h"
#include "Argument.h"
#include "../Enviroments/EnviromentMap.h"

class Function : public Variable
{
public:
	constexpr Function()
	{
	}

	Function(const char* Expression);

public:
	constexpr unsigned long long GetRelativeLocation()
	{
		return RelativeLocation;
	}

public:
	void ExtractArguments(const char* Expression);
	void BindEnviroment(RefObject<class EnviromentMap> Enviroment);

	void PreCompile(class CompileMap& Enviroment);
	void Compile(class CompileMap& Enviroment);
	void PostCompile(class CompileMap& Enviroment);

	void CompileCall(class CompileMap& Enviroment);
	void CompileRetrieve(class CompileMap& Enviroment, class RegisterType Source);

public:
	static bool IsFunctionDefinition(const char* Expression);
	static unsigned long long GetDefinitionLength(const char* Expression);

private:
	void CompileExit(class CompileMap& Enviroment);
	void CompileEntry(class CompileMap& Enviroment);

	void CompileRegisterBackups(class CompileMap& Enviroment);
	void CompileRegisterRestores(class CompileMap& Enviroment);

private:
	RefObject<EnviromentMap> Enviroment;
	List<RefObject<Argument>> Arguments;

	unsigned long long RelativeLocation = 0;

private:
	static constexpr Skippable Ignorable = Skippable(" \t");
};