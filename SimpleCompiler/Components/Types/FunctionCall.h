#pragma once
#include "TypeElement.h"
#include "../../Utilities/Skippable.h"
#include "../../Utilities/RefObject.h"
#include "../../Utilities/List.h"

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

	unsigned long long Parse(RefObject<class EnviromentMap> Enviroment, const char* Expression);

public:
	static bool IsFunctionCall(const char* Expression);

private:
	static RefObject<class Transferable> GetTranferable(unsigned long long Argument);

private:
	RefObject<class Variable> Function;
	List<RefObject<class Arithmetic>> Arguments;

private:
	static constexpr Skippable Ignorables = Skippable("\t ");
};