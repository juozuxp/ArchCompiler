#pragma once
#include "StaticVariable.h"
#include "../../Utilities/Encapsulable.h"

class String : public StaticVariable
{
public:
	constexpr String()
	{
	}

	String(const char* Expression, unsigned long long Length = 0);

public:
	void Compile(class CompileMap& Enviroment);
	void PreCompile(class CompileMap& Enviroment);

	void CompileCall(class CompileMap& Enviroment);
	void CompileAssign(class CompileMap& Enviroment, class RegisterType Source);
	void CompileRetrieve(class CompileMap& Enviroment, class RegisterType Source);
	void CompileRefrence(class CompileMap& Enviroment, class RegisterType Source);

	List<char> FormatString(const char* Expression, unsigned long long Length = 0);
};