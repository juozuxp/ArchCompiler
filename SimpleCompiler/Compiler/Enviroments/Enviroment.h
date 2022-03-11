#pragma once
#include "../../Utilities/RefObject.h"
#include "../../Utilities/HashMap.h"
#include "../../Parser/Types/Variable.h"

class Enviroment
{
public:
	inline Enviroment() : Variables(HashMap<char, RefObject<Variable>>(0))
	{
	}

public:
	virtual void Compile(class CompileMap& Enviroment)
	{
	}

	virtual void AddVariable(RefObject<Variable> Element);
	virtual RefObject<Variable> GetVariable(const char* Name, unsigned long long Length = 0) const;

protected:
	HashMap<char, RefObject<Variable>> Variables;
};

