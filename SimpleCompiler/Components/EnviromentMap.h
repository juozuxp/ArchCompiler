#pragma once
#include "../Utilities/HashMap.h"
#include "../Parser/Types/Variable.h"
#include "../Parser/Types/ParserElement.h"
#include "../Utilities/RefObject.h"

class EnviromentMap
{
public:
	inline EnviromentMap() : ParseElements(List<RefObject<ParserElement>>(0)), Variables(HashMap<char, RefObject<Variable>>(0))
	{
	}

public:
	RefObject<Variable> GetVariable(const char* Name, unsigned long long Length = 0);

public:
	void AddVariable(RefObject<Variable> Element);
	void AddParsed(RefObject<ParserElement> Element);

public:
	List<RefObject<ParserElement>> ParseElements;
	HashMap<char, RefObject<Variable>> Variables;
};