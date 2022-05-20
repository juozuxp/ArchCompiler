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

	constexpr bool GetSigniage()
	{
		return VariableSigniage;
	}

public:
	void PreCompile(class CompileMap& Enviroment);
	void PostCompile(class CompileMap& Enviroment);

	unsigned long long Parse(RefObject<class EnviromentMap> Enviroment, const char* Expression);

public:
	virtual void CompileCall(class CompileMap& Enviroment);
	virtual void CompileRetrieve(class CompileMap& Enviroment, class RegisterType Source);
	virtual void CompileRefrence(class CompileMap& Enviroment, class RegisterType Source);
	virtual void CompileAssign(class CompileMap& Enviroment, class RegisterType Source, long long Dimension);

	virtual unsigned long GetReferenceMultiplier(long long Reference);

public:
	static bool IsVariable(const char* Expression);
	
protected:
	static List<char> ExtractName(const char* Expression);
	static unsigned long long GetDimensions(const char* Expression);
	static unsigned long long CountReferences(const char* Expression);

protected:
	constexpr unsigned long long GetVariableAssignSize()
	{
		return VariableReference ? 8 : VariableSize;
	}

	constexpr unsigned long long GetVariableRetrieveSize()
	{
		return (VariableReference || VariabelDimension != 1) ? 8 : VariableSize;
	}

	constexpr unsigned long long GetVariableAllocationSize()
	{
		return GetVariableAssignSize() * VariabelDimension;
	}

protected:
	List<char> VariableName;
	RefObject<Arithmetic> Assigner;

	bool VariableSigniage = false;

	unsigned long long VariableSize = 0;
	unsigned long long VariabelDimension = 0;
	unsigned long long VariableReference = 0;

private:
	static constexpr Skippable NonNameChar = Skippable(" \t*=()[]");
	static constexpr Skippable Ignorables = Skippable(" \t");
};