#pragma once
#include "../../Utilities/HashMap.h"
#include "../../Parser/Types/Variable.h"
#include "../../Parser/Types/ParserElement.h"
#include "../../Utilities/RefObject.h"
#include "Enviroment.h"

class EnviromentMap : public Enviroment
{
public:
	inline EnviromentMap(RefObject<Enviroment> Parent) : ParseElements(List<RefObject<ParserElement>>(0)), Parent(Parent)
	{
	}

public:
	void Compile(class CompileMap& Enviroment);
	void Parse(const char* Expression, RefObject<Enviroment> Current);

	void AddVariable(RefObject<Variable> Element);
	void AddParsed(RefObject<ParserElement> Element);
	void AddVariableNoCompile(RefObject<Variable> Element);

	RefObject<Variable> GetVariable(const char* Name, unsigned long long Length = 0) const;

public:
	constexpr unsigned long long GetRelativeLocation()
	{
		return RelativeLocation;
	}

public:
	unsigned long long EstimateStackSize() const;

public:
	RefObject<Enviroment> Parent;
	List<RefObject<ParserElement>> ParseElements;

	unsigned long long RelativeLocation;
};