#pragma once
#include "TypeElement.h"
#include "../../Utilities/RefObject.h"
#include "../../Utilities/Deflatable.h"
#include "../../Utilities/Skippable.h"
#include "../Transferable/Transferable.h"
#include "../../Compiler/TempVariableMap.h"
#include "../../Utilities/SimpleUtilities.h"
#include "../../Utilities/Encapsulable.h"
#include "../../Utilities/Pair.h"

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
	void PostCompile(class CompileMap& Enviroment);

	unsigned long long Parse(RefObject<class EnviromentMap> Enviroment, const char* Expression);
	unsigned long long Parse(RefObject<class EnviromentMap> Enviroment, const char* Expression, RefObject<Transferable> AssignTo, unsigned char Signed = (1 << 1));

private:
	RefObject<class Operand> EvaluateArthmetic(RefObject<class EnviromentMap> Enviroment, const char* Expression);
	RefObject<class Operand> EvaluateOperand(RefObject<class EnviromentMap> Enviroment, const char** Expression, const class DualOperation** ResultingOperation);

private:
	unsigned char Signed = 1; // if second bit is set, it's valid, otherwise it isn't

	RefObject<Operand> Origin;
	TempVariableMap TemporarySpace;
	RefObject<Transferable> AssignTo;

	List<Pair<RefObject<Transferable>, RefObject<Transferable>>> PriorityTransfers;

private:
	static constexpr Skippable Skipper = Skippable(" \t");
	static constexpr Skippable NameSkipper = Skippable(" \t=*()[]=");
	static constexpr Encapsulable StringEncap = Encapsulable('\"', '\"', '\\');
	static constexpr Encapsulable Encapsule = Encapsulable('(', ')', 0, &StringEncap);
};