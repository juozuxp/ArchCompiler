#pragma once
#include "../../Utilities/Skippable.h"
#include "StaticVariable.h"

class Import : public StaticVariable
{
public:

public:
	static bool IsExpression(const char* Expression);

private:
	static constexpr Skippable Ignorable = Skippable(" \t");
};

