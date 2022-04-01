#pragma once
#include "../../Utilities/RefObject.h"

class TypeElement
{
public:
	constexpr TypeElement()
	{
	}

public:
	virtual void PreCompile(class CompileMap& Enviroment);
	virtual void Compile(class CompileMap& Enviroment);
	virtual void PostCompile(class CompileMap& Enviroment);

	virtual unsigned long long Parse(RefObject<class EnviromentMap> Enviroment, const char* Expression);
};