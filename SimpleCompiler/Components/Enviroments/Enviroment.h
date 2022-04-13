#pragma once
#include "../../Utilities/Deflatable.h"
#include "../../Utilities/RefObject.h"
#include "../../Utilities/HashMap.h"
#include "../../Utilities/List.h"

class Enviroment
{
public:
	inline Enviroment() : Variables(HashMap<char, RefObject<class Variable>>(0)), ConstantValues(HashMap<char, unsigned long long>(0))
	{
	}

public:
	virtual void PreCompile(class CompileMap& Enviroment);
	virtual void Compile(class CompileMap& Enviroment);
	virtual void PostCompile(class CompileMap& Enviroment);
	
	virtual void Parse(const char* Expression, RefObject<Enviroment> This);

	virtual void AddVariable(RefObject<class Variable> Element);
	virtual void AddConstantValue(unsigned long long Value, const char* Name, unsigned long long Length = 0);

	virtual RefObject<class String> GetString(const char* String, unsigned long long Length);
	virtual RefObject<class Variable> GetVariable(const char* Name, unsigned long long Length = 0) const;
	virtual bool GetConstantValue(unsigned long long* Value, const char* Name, unsigned long long Length = 0) const;

	virtual bool IsUnderlying();

public:
	static unsigned long GetTermDefintionSize(const char* Expression);

	static unsigned long EstimateSubEnviromentSize(const char* Expression);
	static List<char> ExtractSubEnviroment(const char* Enviroment, unsigned long long* Length);

protected:
	HashMap<char, unsigned long long> ConstantValues;
	HashMap<char, RefObject<class Variable>> Variables;

protected:
	static constexpr unsigned char Terminator = ';';
	static constexpr Deflatable Deflater = Deflatable("\r\n");
};

