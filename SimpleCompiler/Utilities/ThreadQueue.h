#pragma once
#include "List.h"
#include "Mutex.h"

template<typename T>
class ThreadQueue
{
public:
	class ListLink
	{
	public:
		constexpr ListLink()
		{
			this->Flink = this;
			this->Blink = this;
		}

		constexpr ListLink(const ListLink& Copy)
		{
			*this = Copy;
		}

	public:
		ListLink& operator=(const ListLink& Copy)
		{
			if (Copy.Flink == Copy.Blink)
			{
				this->Flink = this;
				this->Blink = this;

				return *this;
			}

			this->Flink = Copy.Flink;
			this->Blink = Copy.Blink;

			return *this;
		}

		ListLink& operator=(ListLink&& Move)
		{
			if (Move.Flink != &Move)
			{
				this->Flink = Move.Flink;
				this->Blink = Move.Blink;

				Move.Flink->Blink = this;
				Move.Blink->Flink = this;

				Move.Flink = &Move;
				Move.Blink = &Move;
			}
			else
			{
				this->Flink = this;
				this->Blink = this;
			}

			return *this;
		}

	protected:
		constexpr void Link(ListLink& Base)
		{
			Flink = Base.Blink->Flink;
			Blink = Base.Blink;

			Blink->Flink = this;
			Flink->Blink = this;
		}

	public:
		constexpr void Unlink() const
		{
			Blink->Flink = Flink;
			Flink->Blink = Blink;
		}

		constexpr ListLink* GetNext() const
		{
			return Flink;
		}

		constexpr ListLink* GetPrev() const
		{
			return Blink;
		}

	private:
		ListLink* Flink = 0;
		ListLink* Blink = 0;
	};

	class Node : public ListLink
	{

	};

public:



private:
	ListLink BaseLink;
};

