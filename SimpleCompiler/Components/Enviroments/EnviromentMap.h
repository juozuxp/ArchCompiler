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
	void Compile(class CompileMap& Enviroment);
	void Parse(const char* Expression, RefObject<Enviroment> Current);

	void AddVariable(RefObject<Variable> Element);
	void AddParsed(RefObject<TypeElement> Element);
	void AddVariableNoCompile(RefObject<Variable> Element);

	RefObject<Variable> GetVariable(const char* Name, unsigned long long Length = 0) const;

public:
	constexpr unsigned long long GetRelativeLocation()
	{
		return RelativeLocation;
	}

public:
	unsigned short EstimateRegisterUsage() const;
	unsigned long long EstimateStackSize() const;

public:
	RefObject<Enviroment> Parent;
	List<RefObject<TypeElement>> ParseElements;

	unsigned long long RelativeLocation;
};