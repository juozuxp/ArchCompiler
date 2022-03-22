#pragma once
#include "../../Utilities/Skippable.h"

class Conditional
{
public:
	static bool IsConditional(const char* Expression);

private:
	static constexpr Skippable Ignorable = Skippable(" \t");
};