#pragma once
#include "../../Utilities/Skippable.h"

class Conditional
{
public:
	static bool IsConditional(const char* Expression);
	static unsigned long ExpressionSize(const char* Expression);

private:
	static constexpr Skippable Ignorable = Skippable(" \t");
};