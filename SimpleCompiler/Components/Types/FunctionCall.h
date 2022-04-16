#pragma once
#include "TypeElement.h"
#include "../../Utilities/Skippable.h"
#include "../../Utilities/RefObject.h"
#include "../../Utilities/List.h"
#include "Arithmetic.h"
#include "Variable.h"

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
	RefObject<Variable> Function;
	List<RefObject<Arithmetic>> Arguments;

private:
	static constexpr Skippable Ignorables = Skippable("\t ");
	static constexpr Encapsulable StringEncap = Encapsulable('\"', '\"', '\\');
	static constexpr Encapsulable Encapsule = Encapsulable('(', ')', 0, &StringEncap);
};