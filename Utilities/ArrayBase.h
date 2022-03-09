#pragma once
#include <string.h>

template<typename Type>
class ArrayBase
{
public:
	class Iterator
	{
	public:
		constexpr Iterator()
		{
		}

	public:
		constexpr Iterator& operator++()
		{
			RunArray++;
			RunIndex++;

			return *this;
		}

		constexpr Iterator& operator++(int)
		{
			return operator++();
		}

		constexpr Iterator& operator--()
		{
			RunArray--;
			RunIndex--;

			return *this;
		}

		constexpr Iterator& operator--(int)
		{
			return operator--();
		}

		constexpr Type* operator->() const
		{
			return RunArray;
		}

		constexpr Type& operator*() const
		{
			return *RunArray;
		}

		constexpr bool operator==(const Iterator& Second) const
		{
			return RunArray == Second.RunArray;
		}

		constexpr bool operator!=(const Iterator& Second) const
		{
			return !operator==(Second);
		}

		constexpr unsigned long long GetIndex()
		{
			return RunIndex;
		}

	private:
		constexpr Iterator(Type* ArrayBase)
		{
			RunIndex = 0;
			RunArray = ArrayBase;
		}

	private:
		friend class ArrayBase;

	private:
		Type* RunArray = 0;
		unsigned long long RunIndex = 0;
	};

	class ConstIterator
	{
	public:
		constexpr ConstIterator()
		{
		}

	public:
		constexpr ConstIterator& operator++()
		{
			RunArray++;
			RunIndex++;

			return *this;
		}

		constexpr ConstIterator& operator++(int)
		{
			return operator++();
		}

		constexpr ConstIterator& operator--()
		{
			RunArray--;
			RunIndex--;

			return *this;
		}

		constexpr ConstIterator& operator--(int)
		{
			return operator--();
		}

		constexpr const Type* operator->() const
		{
			return RunArray;
		}

		constexpr const Type& operator*() const
		{
			return *RunArray;
		}

		constexpr bool operator==(const ConstIterator& Second) const
		{
			return RunArray == Second.RunArray;
		}

		constexpr bool operator!=(const ConstIterator& Second) const
		{
			return !operator==(Second);
		}

		constexpr unsigned long GetIndex()
		{
			return RunIndex;
		}

	private:
		constexpr ConstIterator(const Type* ArrayBase)
		{
			RunIndex = 0;
			RunArray = ArrayBase;
		}

	private:
		friend class ArrayBase;

	private:
		const Type* RunArray = 0;
		unsigned long long RunIndex = 0;
	};

public:
	constexpr ArrayBase()
	{
	}

	constexpr ArrayBase(Type* Buffer, unsigned long Count) : Array(Buffer), ArrayNum(Count)
	{
	}

	constexpr Iterator begin()
	{
		return Iterator(Array);
	}

	constexpr Iterator end()
	{
		return Iterator(Array + ArrayNum);
	}
	
	constexpr ConstIterator begin() const
	{
		return ConstIterator(Array);
	}

	constexpr ConstIterator end() const
	{
		return ConstIterator(Array + ArrayNum);
	}

	constexpr operator Type* () const
	{
		return Array;
	}

	constexpr Type& operator*() const
	{
		return *Array;
	}

	constexpr Type& operator[](unsigned long i) const
	{
		return Array[i];
	}

public:
	constexpr unsigned long GetCount() const
	{
		return ArrayNum;
	}

	inline void Remove(unsigned long Index)
	{
		Remove(Index, 1);
	}

	inline void Remove(unsigned long Index, unsigned long Count)
	{
		if ((ArrayNum - Index) < Count)
			Count = ArrayNum - Index;

		for (unsigned long i = Index; i < (Index + Count); i++)
			Array[i].~Type();

		ArrayNum -= Count;

		memmove(Array + Index, Array + Index + Count, (ArrayNum - Index) * sizeof(Type));
		memset(Array + ArrayNum, 0, Count * sizeof(Type));
	}

	inline void Flush()
	{
		for (unsigned long i = 0; i < ArrayNum; i++)
			Array[i].~Type();

		memset(Array, 0, sizeof(Type) * ArrayNum);

		ArrayNum = 0;
	}

	inline void Trim(unsigned long long NewSize)
	{
		for (unsigned long long i = NewSize; i < ArrayNum; i++)
			Array[i].~Type();

		memset(Array + NewSize, 0, (ArrayNum - NewSize) * sizeof(Type));

		ArrayNum = NewSize;
	}

protected:
	Type* Array = 0;
	unsigned long long ArrayNum = 0;
};