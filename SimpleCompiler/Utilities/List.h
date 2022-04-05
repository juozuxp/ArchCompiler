#pragma once
#include "ArrayBase.h"
#include <stdlib.h>

template<typename Type>
class List : public ArrayBase<Type>
{
public:
	constexpr List()
	{
	}

	List(unsigned long long InitialSize) : ArrayBase<Type>()
	{
		this->ArrayMax = InitialSize;
		this->Array = (Type*)malloc(InitialSize * sizeof(Type));
	}

public:
	~List()
	{
		if (this->Array)
		{
			for (unsigned long long i = 0; i < this->ArrayNum; i++)
				this->Array[i].~Type();

			free(this->Array);
		}
	}

	List(const List& Copy)
	{
		this->ArrayNum = Copy.ArrayNum;
		this->ArrayMax = Copy.ArrayMax;

		this->Array = (Type*)malloc(Copy.ArrayMax * sizeof(Type));

		Type* RunArray = this->Array;
		const Type* CopyArray = Copy.Array;
		for (unsigned long long i = 0; i < this->ArrayNum; i++, RunArray++, CopyArray++)
			*RunArray = *CopyArray;
	}

	List(List&& Move)
	{
		this->Array = Move.Array;
		this->ArrayNum = Move.ArrayNum;
		this->ArrayMax = Move.ArrayMax;

		Move.Array = 0;
	}

	List& operator=(const List& Copy)
	{
		this->ArrayNum = Copy.ArrayNum;
		this->ArrayMax = Copy.ArrayMax;

		this->Array = (Type*)malloc(Copy.ArrayMax * sizeof(Type));

		Type* RunArray = this->Array;
		const Type* CopyArray = Copy.Array;
		for (unsigned long long i = 0; i < this->ArrayNum; i++, RunArray++, CopyArray++)
			*RunArray = *CopyArray;

		return *this;
	}

	List& operator=(List&& Move)
	{
		this->Array = Move.Array;
		this->ArrayNum = Move.ArrayNum;
		this->ArrayMax = Move.ArrayMax;

		Move.Array = 0;

		return *this;
	}

public:
	inline void Add(const Type& Element)
	{
		Expand(1);
		this->Array[this->ArrayNum - 1] = Element;
	}

	inline void Add(const Type* Array, unsigned long long ArrayNum)
	{
		Type* CopyBase;

		Expand(ArrayNum);

		CopyBase = this->Array + this->ArrayNum - ArrayNum;
		for (unsigned long long i = 0; i < ArrayNum; i++, CopyBase++, Array++)
			*CopyBase = *Array;
	}

	inline void Add(const List<Type>& Array)
	{
		Add(Array, Array.GetCount());
	}

	inline void Remove(const Type& Element)
	{
		unsigned long long Index;

		Index = IndexOf(Element);
		if (Index == ~0)
			return;

		RemoveIndex(Index);
	}

	inline void RemoveIndex(unsigned long long Index)
	{
		this->ArrayNum--;
		this->Array[Index].~Type();
		memmove(this->Array + Index, this->Array + Index + 1, sizeof(Type) * (this->ArrayNum - Index));
	}

	inline bool Contains(const Type& Element) const
	{
		return IndexOf(Element) != ~0;
	}

	inline unsigned long long IndexOf(const Type& Element) const
	{
		for (unsigned long long i = 0; i < this->ArrayNum; i++)
		{
			if (this->Array[i] == Element)
				return i;
		}

		return ~0;
	}

	inline void Expand(unsigned long long Size)
	{
		if (this->ArrayNum + Size <= this->ArrayMax)
		{
			this->ArrayNum += Size;
			return;
		}

		this->ArrayNum += Size;
		this->ArrayMax = this->ArrayNum;
		this->Array = (Type*)realloc(this->Array, this->ArrayNum * sizeof(Type));
	}

public:
	constexpr unsigned long long GetMaxCount() const
	{
		return this->ArrayMax;
	}

private:
	unsigned long long ArrayMax = 0;
};

