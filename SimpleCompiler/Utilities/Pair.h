#pragma once

template<typename TFirst, typename TSecond>
class Pair
{
public:
	inline Pair()
	{
	}

	inline Pair(TFirst First, TSecond Second) : First(First), Second(Second)
	{
	}

public:
	TFirst First;
	TSecond Second;
};