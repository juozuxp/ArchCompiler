#pragma once

class Instruction
{
public:
	enum Prefix
	{
		Prefix_REX = 0x40,
		Prefix_REXB = 0x41,
		Prefix_REXX = 0x42,
		Prefix_REXR = 0x44,
		Prefix_REXW = 0x48
	};

private:
	constexpr Instruction()
	{
	}


private: 
};