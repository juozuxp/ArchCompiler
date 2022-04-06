#pragma once
#include "../../Utilities/HashMap.h"
#include "../Types/Variable.h"
#include "../Types/TypeElement.h"
#include "../../Utilities/RefObject.h"
#include "Enviroment.h"

class EnviromentMap : public Enviroment
{
public:
	inline EnviromentMap(RefObject<Enviroment> Parent) : Parent(Parent)
	{
	}

public:
	void PreCompile(class CompileMap& Enviroment);
	void Compile(class CompileMap& Enviroment);
	void PostCompile(class CompileMap& Enviroment);

	void Parse(const char* Expression, RefObject<Enviroment> This);

	void AddVariable(RefObject<Variable> Element);
	void AddParsed(RefObject<TypeElement> Element);
	void AddVariableNoCompile(RefObject<Variable> Element);

	RefObject<class String> GetString(const char* String, unsigned long long Length);
	RefObject<Variable> GetVariable(const char* Name, unsigned long long Length = 0) const;
	bool GetConstantValue(unsigned long long* Value, const char* Name, unsigned long long Length = 0) const;

	RefObject<EnviromentMap> GetBaseEnviroment();

public:
	constexpr unsigned long long GetEnviromentSize()
	{
		return EnviromentSize;
	}

	constexpr unsigned long long GetEnviromentEntry()
	{
		return EnviromentEntry;
	}

private:
	RefObject<Enviroment> Parent;
	List<RefObject<TypeElement>> ParseElements;

	unsigned long long EnviromentEntry;
	unsigned long long EnviromentSize;
};