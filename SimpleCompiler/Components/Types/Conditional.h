#pragma once
#include "../../Utilities/Skippable.h"
#include "../../Utilities/Deflatable.h"
#include "../../Utilities/Encapsulable.h"
#include "TypeElement.h"
#include "Arithmetic.h"

class Conditional : public TypeElement
{
public:
	void PreCompile(class CompileMap& Enviroment);
	void Compile(class CompileMap& Enviroment);
	void PostCompile(class CompileMap& Enviroment);

	unsigned long long Parse(RefObject<EnviromentMap> Enviroment, const char* Expression);

public:
	static bool IsConditional(const char* Expression);

private:
	RefObject<Arithmetic> Condition;

	RefObject<EnviromentMap> ElseEnviroment;
	RefObject<EnviromentMap> ConditionEnviroment;

private:
	static constexpr Skippable Ignorable = Skippable(" \t");
	static constexpr Deflatable Deflatable = Deflatable(" \t");
	static constexpr Encapsulable Encapsulable = Encapsulable('(', ')');
};