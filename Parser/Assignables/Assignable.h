#pragma once
#include "../../Utilities/List.h"

class Assignable
{
public:
	virtual List<unsigned char> Compile(class CompileMap& Enviroment)
	{
		return List<unsigned char>();
	}

private:

};