#pragma once

class Skippable
{
public:
	constexpr Skippable()
	{
	}

	constexpr Skippable(const char* Tokens) : Tokens(Tokens)
	{
	}

public:
	constexpr bool IsSkippable(char Character) const
	{
		for (const char* RunToken = Tokens; *RunToken; RunToken++)
		{
			if (*RunToken == Character)
				return true;
		}

		return false;
	}

	constexpr const char* Skip(const char* String) const
	{
		for (; *String; String++)
		{
			if (!IsSkippable(*String))
				break;
		}

		return String;
	}

	constexpr const char* InverseSkip(const char* String) const
	{
		for (; *String; String++)
		{
			if (IsSkippable(*String))
				break;
		}

		return String;
	}

private:
	const char* Tokens = 0;
};