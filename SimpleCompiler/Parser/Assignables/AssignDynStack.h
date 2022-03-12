#pragma once

class AssignDynStack
{
public:
	constexpr AssignDynStack()
	{
	}

public:
	void Compile(class CompileMap& Enviroment);
	void CompileRetrieve(class CompileMap& Enviroment);

private:
	unsigned long long LocationInStack = ~0;
};