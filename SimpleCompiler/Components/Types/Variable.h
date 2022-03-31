#pragma once
#include "TypeElement.h"
#include "Arithmetic.h"
#include "../../Utilities/Skippable.h"

class Variable : public TypeElement
{
public:
	constexpr Variable()
	{
	}

	Variable(const char* Expression);

public:
	constexpr const char* GetVariableName()
	{
		return VariableName;
	}

public:
	void PreCompile(class CompileMap& Enviroment);
	void PostCompile(class CompileMap& Enviroment);

	unsigned long long Parse(RefObject<EnviromentMap> Enviroment, const char* Expression);

public:
	virtual void CompileCall(class CompileMap& Enviroment);
	virtual void CompileAssign(class CompileMap& Enviroment, RegisterType Source);
	virtual void CompileRetrieve(class CompileMap& Enviroment, RegisterType Source);

public:
	static bool IsVariable(const char* Expression);
	
protected:
	static List<char> ExtractName(const char* Expression);

protected:
	List<char> VariableName;
	RefObject<Arithmetic> Assigner;

	unsigned long long VariableSize = 0;

private:
	static constexpr Skippable NonNameChar = Skippable(" \t=()");
	static constexpr Skippable Ignorables = Skippable(" \t");
};