#pragma once
#include "../../Utilities/Skippable.h"
#include "StaticVariable.h"

class Import : public StaticVariable
{
public:
	Import(const char* Expression);

public:
	void Compile(class CompileMap& Enviroment);
	void PreCompile(class CompileMap& Enviroment);

public:
	constexpr const char* GetSourceName()
	{
		return SourceName;
	}

	constexpr const char* GetFunctionName()
	{
		return FunctionName;
	}

	constexpr unsigned long long GetDataLocation()
	{
		return DataPosition;
	}

public:
	static bool IsExpression(const char* Expression);

private:
	List<char> SourceName;
	List<char> FunctionName;

private:
	static constexpr Skippable Ignorable = Skippable(" \t");
	static constexpr Encapsulable StringEncap = Encapsulable('\"', '\"', '\\');
};