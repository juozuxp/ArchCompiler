#pragma once
#include "ParserElement.h"
#include "Arithmetic.h"

class Variable : public ParserElement
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

public:
	void Parse(class EnviromentMap& Enviroment, const char* Expression);

public:
	virtual void CompileAssign(class CompileMap& Enviroment)
	{
	}

	virtual void CompileRetrieve(class CompileMap& Enviroment)
	{
	}

	virtual void CompileCall(class CompileMap& Enviroment)
	{
	}

public:
	static bool IsVariable(const char* Expression);
	
protected:
	static List<char> ExtractName(const char* Expression);

protected:
	List<char> VariableName;
	RefObject<Arithmetic> Assigner;

	unsigned long long VariableSize = 0;

private:
	static constexpr bool IsNameChar(char Character)
	{
		for (const char* RunNonChar = NonNameChar; *RunNonChar; RunNonChar++)
		{
			if (Character == *RunNonChar)
				return false;
		}

		return true;
	}

	static constexpr bool IsIgnorable(char Character)
	{
		for (const char* RunIgnorable = Ignorables; *RunIgnorable; RunIgnorable++)
		{
			if (Character == *RunIgnorable)
				return true;
		}

		return false;
	}

private:
	static constexpr const char* NonNameChar = " \t=()";
	static constexpr const char* Ignorables = " \t";
};