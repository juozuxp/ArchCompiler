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

	virtual void Parse(const char* Expression, RefObject<Enviroment> Current)
	{
	}

	virtual void AddVariable(RefObject<Variable> Element);
	virtual RefObject<Variable> GetVariable(const char* Name, unsigned long long Length = 0) const;

protected:
	static List<char> ExtractSubEnviroment(const char* Enviroment, unsigned long long* Length);

protected:
	HashMap<char, RefObject<Variable>> Variables;

protected:
	static constexpr Deflatable Deflater = Deflatable("\r\n");
};

