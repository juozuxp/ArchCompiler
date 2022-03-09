#pragma once
#include <intrin.h>

template<typename Type>
class RefObject
{
private:
	template<typename RefType>
	class RefLink
	{
	public:
		constexpr RefLink()
		{
		}

		inline RefLink(const RefType& Object) : Object(Object), RefCount(1)
		{
		}

	public:
		unsigned long long RefCount = 0;
		RefType Object = RefType();
	};

public:
	constexpr RefObject()
	{
	}

	inline RefObject(const Type& Object)
	{
		Pointer = new RefLink<Type>(Object);
	}

	inline RefObject(void* CastPointer)
	{
		Pointer = (RefLink<Type>*)CastPointer;
		if (!Pointer)
			return;

		IncreaseRef();
	}

public:
	inline ~RefObject()
	{
		if (!Pointer)
			return;

		DecreaseRef();
		if (Pointer->RefCount == 0)
			delete Pointer;
	}

	inline RefObject(const RefObject& Copy)
	{
		Pointer = Copy.Pointer;
		if (!Pointer)
			return;

		IncreaseRef();
	}

	inline RefObject(RefObject&& Move)
	{
		Pointer = Move.Pointer;
		Move.Pointer = 0;
	}

	inline RefObject& operator=(const RefObject& Copy)
	{
		Pointer = Copy.Pointer;
		if (!Pointer)
			return *this;

		IncreaseRef();

		return *this;
	}

	inline RefObject& operator=(RefObject&& Move)
	{
		Pointer = Move.Pointer;
		Move.Pointer = 0;

		return *this;
	}

private:
	volatile void DecreaseRef()
	{
		_interlockeddecrement64((volatile long long*)&Pointer->RefCount);
	}

	volatile void IncreaseRef()
	{
		_interlockedincrement64((volatile long long*)&Pointer->RefCount);
	}

public:
	constexpr Type* operator->()
	{
		return &Pointer->Object;
	}

	constexpr const Type* operator->() const
	{
		return &Pointer->Object;
	}

	constexpr Type& operator*()
	{
		return Pointer->Object;
	}

	constexpr const Type& operator*() const
	{
		return Pointer->Object;
	}

	constexpr bool operator!() const
	{
		return !Pointer;
	}

	constexpr operator bool() const
	{
		return Pointer;
	}

	template<typename CType>
	constexpr RefObject<CType> Cast()
	{
		return RefObject<CType>((void*)Pointer);
	}

private:
	RefLink<Type>* Pointer = 0;
};