#pragma once
#include "../../Utilities/RefObject.h"
#include "../../Utilities/HashMap.h"
#include "../Types/Variable.h"

class Enviroment
{
public:
	inline Enviroment() : Variables(HashMap<char, RefObject<Variable>>(0))
	{
	}

public:
	virtual void PreCompile(class CompileMap& Enviroment);
	virtual void Compile(class CompileMap& Enviroment);
	virtual void PostCompile(class CompileMap& Enviroment);
	
	virtual void Parse(const char* Expression, RefObject<Enviroment> This);

	virtual void AddVariable(RefObject<Variable> Element);
	virtual RefObject<Variable> GetVariable(const char* Name, unsigned long long Length = 0) const;

public:
	static unsigned long EstimateSubEnviromentSize(const char* Expression);
	static List<char> ExtractSubEnviroment(const char* Enviroment, unsigned long long* Length);

protected:
	HashMap<char, RefObject<Variable>> Variables;

protected:
	static constexpr Deflatable Deflater = Deflatable("\r\n");
};
