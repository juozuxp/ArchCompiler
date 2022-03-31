#pragma once
#include "TypeElement.h"
#include "../Transferable/Transferable.h"
#include "Arithmetic.h"
#include "Variable.h"
#include "../../Utilities/Skippable.h"

class FunctionCall : public TypeElement
{
public:
	constexpr FunctionCall()
	{
	}

public:
	void PreCompile(class CompileMap& Enviroment);
	void Compile(class CompileMap& Enviroment);
	void PostCompile(class CompileMap& Enviroment);

	unsigned long long Parse(RefObject<EnviromentMap> Enviroment, const char* Expression);

public:
	static bool IsFunctionCall(const char* Expression);

private:
	static RefObject<Transferable> GetTranferable(unsigned long long Argument);

private:
	RefObject<Variable> Function;
	List<RefObject<Arithmetic>> Arguments;

private:
	static constexpr Skippable Ignorables = Skippable("\t ");
};