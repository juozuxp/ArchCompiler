#pragma once
#include "TypeElement.h"
#include "../../Utilities/Skippable.h"
#include "../../Utilities/List.h"
#include "Arithmetic.h"

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

	unsigned long long Parse(RefObject<class EnviromentMap> Enviroment, const char* Expression);

public:
	virtual void CompileCall(class CompileMap& Enviroment);
	virtual void CompileAssign(class CompileMap& Enviroment, class RegisterType Source);
	virtual void CompileRetrieve(class CompileMap& Enviroment, class RegisterType Source);
	virtual void CompileRefrence(class CompileMap& Enviroment, class RegisterType Source);

	virtual unsigned long GetReferenceMultiplier(long long Reference);

public:
	static bool IsVariable(const char* Expression);
	
protected:
	static List<char> ExtractName(const char* Expression);
	static unsigned long long CountReferences(const char* Expression);

protected:
	constexpr unsigned long long GetVariableSize()
	{
		return VariableReference ? 8 : VariableSize;
	}

protected:
	List<char> VariableName;
	RefObject<Arithmetic> Assigner;

	unsigned long long VariableSize = 0;
	unsigned long long VariableReference = 0;

private:
	static constexpr Skippable NonNameChar = Skippable(" \t*=()");
	static constexpr Skippable Ignorables = Skippable(" \t");
};