#pragma once
#include "List.h"

class Encapsulable
{
public:
	constexpr Encapsulable()
	{
	}

	constexpr Encapsulable(char Opening, char Closing, char Break = 0, const Encapsulable* IgnoreEncap = 0) : Opening(Opening), Closing(Closing), Break(Break), IgnoreEncap(IgnoreEncap)
	{
	}

public:
	constexpr const char* GetEncapEnd(const char* Begining) const
	{
		Begining = GetBeginingEncap(Begining);
		if (!Begining)
			return 0;

		unsigned long long EncapCount = 1;
		if (IgnoreEncap)
		{
			for (Begining++; *Begining; Begining++)
			{
				if (*Begining == Break)
				{
					Begining++;
					continue;
				}

				if (*Begining != IgnoreEncap->Break && *Begining == IgnoreEncap->Opening)
				{
					Begining = IgnoreEncap->GetEncapEnd(Begining);
					continue;
				}

				if (*Begining == IgnoreEncap->Break && *(Begining + 1) == IgnoreEncap->Opening)
				{
					Begining++;
					continue;
				}

				if (*Begining == Closing)
					EncapCount--;
				else if (*Begining == Opening)
					EncapCount++;

				if (!EncapCount)
					return Begining;
			}

			return 0;
		}

		for (Begining++; *Begining; Begining++)
		{
			if (*Begining == Break)
			{
				Begining++;
				continue;
			}

			if (*Begining == Closing)
				EncapCount--;

			else if (*Begining == Opening)
				EncapCount++;

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

		Begining = GetBeginingEncap(Begining);
		if (!Begining)
			return List<char>();

		const char* End = GetEncapEnd(Begining);
		if (!End)
			return List<char>();

		Space.Add(Begining + 1, End - (Begining + 1));
		Space.Add('\0');

		return Space;
	}

private:
	constexpr const char* GetBeginingEncap(const char* Begining) const
	{
		if (IgnoreEncap)
		{
			for (; *Begining; Begining++)
			{
				if (*Begining == Break)
				{
					Begining++;
					continue;
				}

				if (*Begining != IgnoreEncap->Break && *Begining == IgnoreEncap->Opening)
				{
					Begining = IgnoreEncap->GetEncapEnd(Begining);
					continue;
				}

				if (*Begining == IgnoreEncap->Break && *(Begining + 1) == IgnoreEncap->Opening)
				{
					Begining++;
					continue;
				}

				else if (*Begining == Opening)
					return Begining;
			}

			return 0;
		}

		for (; *Begining; Begining++)
		{
			if (*Begining == Break)
			{
				Begining++;
				continue;
			}
			else if (*Begining == Opening)
				return Begining;
		}

		return 0;
	}

private:
	char Break = 0;
	char Opening = 0;
	char Closing = 0;

	const Encapsulable* IgnoreEncap = 0;
};