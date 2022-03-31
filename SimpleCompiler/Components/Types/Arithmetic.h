#pragma once
#include "TypeElement.h"
#include "../../Utilities/RefObject.h"
#include "../../Utilities/Deflatable.h"
#include "../Transferable/Transferable.h"
#include "../../Compiler/TempVariableMap.h"
#include "../../Utilities/SimpleUtilities.h"

#include "Arithmetic/Operand.h"

class Arithmetic : public TypeElement
{
public:
	constexpr Arithmetic() : TypeElement()
	{
	}

public:
	static bool IsArtimetic(const char* Expression);

public:
	void PreCompile(class CompileMap& Enviroment);
	void Compile(class CompileMap& Enviroment);

	unsigned long long Parse(RefObject<EnviromentMap> Enviroment, const char* Expression);
	unsigned long long Parse(RefObject<EnviromentMap> Enviroment, const char* Expression, RefObject<Transferable> AssignTo);

private:
	RefObject<class Operand> EvaluateArthmetic(class EnviromentMap& Enviroment, const char* Expression);

private:
	static const char* HuntEnclosure(const char* Expression);
	static List<char> ExtractEnclosure(const char* Expression);

private:
	RefObject<Operand> Origin;
	TempVariableMap TemporarySpace;
	RefObject<Transferable> AssignTo;

private:
	static constexpr Deflatable Deflater = Deflatable(" \t");
};