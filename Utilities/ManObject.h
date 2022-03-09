#pragma once

template<typename Type>
class ManObject
{
public:
	constexpr ManObject()
	{
	}

	template<typename DType>
	inline ManObject(const DType& Object)
	{
		DType* Castable;

		Castable = new DType(Object);
		Pointer = (Type*)Castable;
	}

private:
	inline ManObject(void* CastPointer)
	{
		Pointer = (Type*)CastPointer;
	}

public:
	inline ~ManObject()
	{
		if (!Pointer)
			return;

		delete Pointer;
	}

	inline ManObject(const ManObject& Copy)
	{
		Pointer = new Type(*Copy.Pointer);
	}

	inline ManObject(ManObject&& Move)
	{
		Pointer = Move.Pointer;
		Move.Pointer = 0;
	}

	inline ManObject& operator=(const ManObject& Copy)
	{
		Pointer = new Type(*Copy.Pointer);
		return *this;
	}

	inline ManObject& operator=(ManObject&& Move)
	{
		Pointer = Move.Pointer;
		Move.Pointer = 0;

		return *this;
	}

public:
	constexpr Type* operator->()
	{
		return Pointer;
	}

	constexpr const Type* operator->() const
	{
		return Pointer;
	}

	constexpr Type& operator*()
	{
		return *Pointer;
	}

	constexpr const Type& operator*() const
	{
		return *Pointer;
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
	constexpr ManObject<CType> Cast()
	{
		return ManObject<CType>(Pointer);
	}

private:
	Type* Pointer = 0;
};