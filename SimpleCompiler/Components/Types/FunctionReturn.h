#pragma once
#include "TypeElement.h"
#include "../../Utilities/Skippable.h"

class FunctionReturn : public TypeElement
{
public:
	constexpr FunctionReturn() : TypeElement()
	{
	}

public:
	void PreCompile(class CompileMap& Enviroment);
	void Compile(class CompileMap& Enviroment);
	void PostCompile(class CompileMap& Enviroment);

	unsigned long long Parse(RefObject<class EnviromentMap> Enviroment, const char* Expression);
	
public:
	static bool IsExpression(const char* Expression);

private:
	unsigned long AllocatedJump = 0;

	RefObject<class Arithmetic> Return;
	RefObject<class EnviromentMap> Host;

private:
	static constexpr Skippable Ignorables = Skippable("\t ");
};