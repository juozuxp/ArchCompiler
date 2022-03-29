#pragma once
#include "../../Utilities/Skippable.h"
#include "../../Utilities/Deflatable.h"
#include "ParserElement.h"
#include "Arithmetic.h"

class Conditional : ParserElement
{
public:
	void Compile(class CompileMap& Enviroment);
	unsigned long long Parse(class EnviromentMap& Enviroment, const char* Expression);

public:
	static bool IsConditional(const char* Expression);

private:
	RefObject<Arithmetic> Condition;

private:
	static constexpr Skippable Ignorable = Skippable(" \t");
	static constexpr Deflatable Deflatable = Deflatable(" \t");
};