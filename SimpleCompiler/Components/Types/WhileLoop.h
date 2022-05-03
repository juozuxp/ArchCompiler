#pragma once
#include "TypeElement.h"
#include "Arithmetic.h"
#include "../Enviroments/EnviromentMap.h"
#include "../../Utilities/Deflatable.h"
#include "../../Utilities/Skippable.h"
#include "../../Utilities/Encapsulable.h"

class WhileLoop : public TypeElement
{
public:
	void PreCompile(class CompileMap& Enviroment);
	void Compile(class CompileMap& Enviroment);
	void PostCompile(class CompileMap& Enviroment);

	unsigned long long Parse(RefObject<EnviromentMap> Enviroment, const char* Expression);

public:
	static bool IsWhileLoop(const char* Expression);

protected:
	RefObject<Arithmetic> Condition;
	RefObject<EnviromentMap> LoopEnviroment;

protected:
	static constexpr Skippable Ignorable = Skippable(" \t");
	static constexpr Deflatable Deflatable = Deflatable(" \t");
	static constexpr Encapsulable Encapsulable = Encapsulable('(', ')');
};