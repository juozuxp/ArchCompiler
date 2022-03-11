#pragma once
#include "ParserElement.h"
#include "../Assignables/Assignable.h"
#include "Arithmetic.h"
#include "Variable.h"

class FunctionCall : ParserElement
{
public:
	constexpr FunctionCall()
	{
	}

public:
	void Compile(class CompileMap& Enviroment);
	void Parse(class EnviromentMap& Enviroment, const char* Expression);

public:
	static bool IsFunctionCall(const char* Expression);

private:
	static constexpr bool IsIgnorable(char Character)
	{
		for (const char* RunIgnore = Ignorables; *RunIgnore; RunIgnore++)
		{
			if (*RunIgnore == Character)
				return true;
		}

		return false;
	}

private:
	static RefObject<Assignable> GetAssignable(unsigned long long Argument);

private:
	RefObject<Variable> Function;
	List<RefObject<Arithmetic>> Arguments;

private:
	static constexpr const char* Ignorables = "\t ";
};