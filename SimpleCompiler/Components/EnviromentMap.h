#pragma once
#include "../Utilities/HashMap.h"
#include "../Parser/Types/Variable.h"
#include "../Parser/Types/ParserElement.h"
#include "../Utilities/RefObject.h"
#include "Enviroment.h"

class EnviromentMap : public Enviroment
{
public:
	inline EnviromentMap(RefObject<Enviroment> Parent) : ParseElements(List<RefObject<ParserElement>>(0)), Parent(Parent)
	{
	}

public:
	void AddVariable(RefObject<Variable> Element);
	void AddParsed(RefObject<ParserElement> Element);

	RefObject<Variable> GetVariable(const char* Name, unsigned long long Length = 0) const;

public:
	RefObject<Enviroment> Parent;
	List<RefObject<ParserElement>> ParseElements;
};