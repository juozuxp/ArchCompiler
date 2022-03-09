#pragma once
#include "List.h"

class Deflatable
{
public:
	constexpr Deflatable()
	{
	}

	constexpr Deflatable(const char* Mask) : Mask(Mask)
	{
	}

public:
	constexpr unsigned long long Deflate(char* String) const
	{
		unsigned long long Offset = 0;
		unsigned long long Length = 0;
		for (; *(String + Offset); String++)
		{
			if (ShouldDeflate(*(String + Offset)))
				Offset++;

			Length++;
			*String = String[Offset];
		}

		*String = '\0';
		return Length;
	}

	inline void Deflate(List<char>& String) const
	{
		unsigned long long Length;

		Length = Deflate(String.operator char* ());
		String.Trim(Length + 1);
	}

	inline List<char> Deflate(const List<char>& String) const
	{
		List<char> Copy = String;

		Deflate(Copy);

		return Copy;
	}

	inline List<char> Deflate(const char* String) const
	{
		List<char> Copy = List<char>(0);

		Copy.Add(String, strlen(String) + 1);
		Deflate(Copy);

		return Copy;
	}

private:
	constexpr bool ShouldDeflate(char Character) const
	{
		const char* RunMask = Mask;
		for (; *RunMask; RunMask++)
		{
			if (*RunMask == Character)
				return true;
		}

		return false;
	}

private:
	const char* Mask = 0;
};