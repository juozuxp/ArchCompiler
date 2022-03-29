#pragma once
#include "List.h"

class Encapsulable
{
public:
	constexpr Encapsulable()
	{
	}

	constexpr Encapsulable(char Opening, char Closing) : Opening(Opening), Closing(Closing)
	{
	}

public:
	constexpr const char* GetEncapEnd(const char* Begining) const
	{
		for (; *Begining && *Begining != Opening; Begining++);
		if (!*Begining)
			return 0;

		unsigned long long EncapCount = 1;
		for (Begining++; *Begining; Begining++)
		{
			if (*Begining == Opening)
				EncapCount++;

			else if (*Begining == Closing)
				EncapCount--;

			if (!EncapCount)
				return Begining;
		}

		return 0;
	}

	constexpr char* GetEncapEnd(char* Begining) const
	{
		return (char*)GetEncapEnd((const char*)Begining);
	}

	inline List<char> GetEncapSpace(const char* Begining) const
	{
		List<char> Space;

		for (; *Begining && *Begining != Opening; Begining++);
		if (!*Begining)
			return List<char>();

		const char* End = GetEncapEnd(Begining);
		if (!End)
			return List<char>();

		Space.Add(Begining, End - Begining);
		Space.Add('\0');

		return Space;
	}

private:
	char Opening = 0;
	char Closing = 0;
};