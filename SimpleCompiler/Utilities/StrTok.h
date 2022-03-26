#pragma once
#include "List.h"
#include <string.h>

class StrTok
{
public:
	class Iterator
	{
	public:
		constexpr Iterator()
		{
		}

	public:
		inline Iterator& operator++()
		{
			ExtractNextToken();
			return *this;
		}

		inline Iterator& operator++(int)
		{
			return operator++();
		}

		constexpr char* operator*() const
		{
			return Token;
		}

		constexpr bool operator==(const Iterator& Second) const
		{
			return LastToken == Second.LastToken;
		}

		constexpr bool operator!=(const Iterator& Second) const
		{
			return !operator==(Second);
		}

	private:
		inline void ExtractNextToken()
		{
			if (LastToken)
			{
				*(LastToken - 1) = *SubToken;
				Token = LastToken + SubTokenLength - 1;
			}
			else
				LastToken = Token;

			if (!*LastToken)
			{
				LastToken = 0;
				return;
			}

			for (LastToken++; *LastToken; LastToken++)
			{
				if (!strncmp(LastToken, SubToken, SubTokenLength))
				{
					*LastToken = '\0';
					LastToken++;
					break;
				}
			}
		}

	private:
		inline Iterator(char* String, const char* Sub, unsigned long long SubLength)
		{
			SubToken = Sub;
			SubTokenLength = SubLength;

			Token = String;
			ExtractNextToken();
		}

	private:
		friend class StrTok;

	private:
		char* Token = 0;
		char* LastToken = 0;
		const char* SubToken = 0;
		unsigned long long SubTokenLength = 0;
	};

	class CommmitIterator
	{
	public:
		class Commitable
		{
		private:
			constexpr Commitable()
			{
			}

			constexpr Commitable(CommmitIterator* Parent) : Parent(Parent)
			{
			}

		public:
			constexpr const char* GetToken() const
			{
				return Parent->Token;
			}

			constexpr void CommitToken() const
			{
				Parent->CommitToken();
			}

			constexpr void SkipFor(unsigned long long Length) const
			{
				Parent->SkipLength(Length);
			}

		private:
			CommmitIterator* Parent = 0;

		private:
			friend class CommmitIterator;
		};

	public:
		constexpr CommmitIterator()
		{
		}

	public:
		inline CommmitIterator& operator++()
		{
			ExtractNextToken();
			return *this;
		}

		inline CommmitIterator& operator++(int)
		{
			return operator++();
		}

		Commitable operator*()
		{
			return Commitable(this);
		}

		constexpr bool operator==(const CommmitIterator& Second) const
		{
			return LastToken == Second.LastToken;
		}

		constexpr bool operator!=(const CommmitIterator& Second) const
		{
			return !operator==(Second);
		}

	private:
		constexpr void CommitToken()
		{
			*(LastToken - 1) = '\0';
		}

		constexpr void SkipLength(unsigned long long Length)
		{
			Token += Length;
			LastToken = 0;
		}

		inline void ExtractNextToken()
		{
			if (LastToken)
			{
				*(LastToken - 1) = *SubToken;
				Token = LastToken + SubTokenLength - 1;
			}
			else
				LastToken = Token;

			if (!*LastToken)
			{
				LastToken = 0;
				return;
			}

			for (LastToken++; *LastToken; LastToken++)
			{
				if (!strncmp(LastToken, SubToken, SubTokenLength))
				{
					LastToken++;
					break;
				}
			}
		}

	private:
		inline CommmitIterator(char* String, const char* Sub, unsigned long long SubLength)
		{
			SubToken = Sub;
			SubTokenLength = SubLength;

			Token = String;
			ExtractNextToken();
		}

	private:
		friend class StrTok;

	private:
		char* Token = 0;
		char* LastToken = 0;
		const char* SubToken = 0;
		unsigned long long SubTokenLength = 0;
	};

	class CommitableIteration
	{
	public:
		inline CommitableIteration(List<char>& String, const char* SubToken, unsigned long long SubTokenLength) : String(String), SubToken(SubToken), SubTokenLength(SubTokenLength)
		{
		}

	public:
		inline CommmitIterator begin()
		{
			return CommmitIterator(String, SubToken, SubTokenLength);
		}

		constexpr CommmitIterator end()
		{
			return CommmitIterator();
		}

	private:
		List<char> String;

		const char* SubToken = 0;
		unsigned long long SubTokenLength = 0;
	};

public:
	constexpr StrTok()
	{
	}

	StrTok(const char* String, const char* SubToken)
	{
		unsigned long long Length;

		Length = strlen(String) + 1;

		this->String = List<char>(Length);
		this->String.Add(String, Length);

		this->SubToken = SubToken;
		this->SubTokenLength = strlen(SubToken);
	}

	StrTok(const char* String, unsigned long long Length, const char* SubToken, unsigned long long SubLength = 0)
	{
		this->String = List<char>(Length + 1);
		this->String.Add(String, Length);
		this->String.Add('\0');

		this->SubToken = SubToken;
		this->SubTokenLength = SubLength ? SubLength : strlen(SubToken);
	}

public:
	inline Iterator begin()
	{
		return Iterator(String, SubToken, SubTokenLength);
	}

	constexpr Iterator end()
	{
		return Iterator();
	}

	inline CommitableIteration GetCommitable()
	{
		return CommitableIteration(String, SubToken, SubTokenLength);
	}

private:
	List<char> String;

	const char* SubToken = 0;
	unsigned long long SubTokenLength = 0;
};