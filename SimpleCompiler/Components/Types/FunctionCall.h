#pragma once
#include "ParserElement.h"
#include "../Transferable/Transferable.h"
#include "Arithmetic.h"
#include "Variable.h"
#include "../../Utilities/Skippable.h"

class FunctionCall : ParserElement
{
public:
	constexpr FunctionCall()
	{
	}

public:
	unsigned long long GetCallingStackSize();
	void Compile(class CompileMap& Enviroment);
	unsigned long long Parse(class EnviromentMap& Enviroment, const char* Expression);

public:
	static bool IsFunctionCall(const char* Expression);

private:
	static RefObject<Transferable> GetAssignable(unsigned long long Argument);

private:
	RefObject<Variable> Function;
	List<RefObject<Arithmetic>> Arguments;

private:
	static constexpr Skippable Ignorables = Skippable("\t ");
};