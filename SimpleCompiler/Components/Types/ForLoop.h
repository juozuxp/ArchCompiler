#pragma once
#include "WhileLoop.h"

class ForLoop : public WhileLoop
{
public:
	void PreCompile(class CompileMap& Enviroment);
	void Compile(class CompileMap& Enviroment);
	void PostCompile(class CompileMap& Enviroment);

	unsigned long long Parse(RefObject<EnviromentMap> Enviroment, const char* Expression);

public:
	static bool IsExpression(const char* Expression);
	static unsigned long ExpressionLength(const char* Expression);

private:
	RefObject<TypeElement> PreLoop;
	RefObject<Arithmetic> ForEachCycle;
};

