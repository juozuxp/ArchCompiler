#pragma once
#include "SimpleUtilities.h"
#include <string.h>
#include <stdlib.h>
#include "ArrayBase.h"

template<typename Key, typename Type>
class HashMap
{
private:
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
	private:
		static void Construct(Node* Node, const Key* Key, unsigned long long Count, const Type& Element)
		{
			Construct(Node, Key, Count);
			Node->Element = Element;
		}

		static void Construct(Node* Node, const Key* Key, unsigned long long Count)
		{
			memcpy(Node->Array, Key, Count * sizeof(*Key));
			memset(&Node->Element, 0, sizeof(Type));

			Node->Next = 0;
			Node->Count = Count;
		}

	public:
		static inline Node* Create(ListLink& Base, const Key* Key, unsigned long long Count)
		{
			Node* Constructed;

			Constructed = (Node*)malloc(GET_ELEMENT(Node, Array) + (sizeof(*Key) * Count));
			Construct(Constructed, Key, Count);

			Constructed->Link(Base);

			return Constructed;
		}

		static inline Node* Create(ListLink& Base, const Key* Key, unsigned long long Count, const Type& Element)
		{
			Node* Constructed;

			Constructed = (Node*)malloc(GET_ELEMENT(Node, Array) + (sizeof(*Key) * Count));
			Construct(Constructed, Key, Count, Element);

			Constructed->Link(Base);

			return Constructed;
		}

	private:
		inline bool IsEqual(const Key* Key, unsigned long long Count) const
		{
			if (Count != this->Count)
				return false;

			return !memcmp(Array, Key, Count * sizeof(*Key));
		}

	public:
		inline bool Add(ListLink& Base, const Key* Key, unsigned long long Count, const Type& Element)
		{
			Node* Last;
			for (Last = this; Last->Next; Last = Last->Next)
			{
				if (Last->IsEqual(Key, Count))
				{
					Last->Element = Element;
					return false;
				}
			}

			if (Last->IsEqual(Key, Count))
			{
				Last->Element = Element;
				return false;
			}

			Last->Next = Create(Base, Key, Count, Element);
			return true;
		}

		inline unsigned long ReserveIndex(ListLink& Base, const Key* Key, unsigned long long Count, bool* Reserved)
		{
			Node* Last;
			unsigned long Index;

			*Reserved = false;
			for (Last = this, Index = 0; Last->Next; Last = Last->Next, Index++)
			{
				if (Last->IsEqual(Key, Count))
				{
					Last->Element = Element;
					return Index;
				}
			}

			if (Last->IsEqual(Key, Count))
				return Index;

			*Reserved = true;

			Last->Next = Create(Base, Key, Count);
			return Index + 1;
		}

		inline unsigned long GetIndex(const Key* Key, unsigned long long Count) const
		{
			const Node* Iter = this;
			for (unsigned long i = 0; Iter; i++, Iter = Iter->Next)
			{
				if (Iter->IsEqual(Key, Count))
					return i;
			}

			return ~0;
		}

		inline Type& GetByIndex(unsigned long Index)
		{
			Node* Iter = this;
			for (unsigned long i = 0; i < Index; i++)
				Iter = Iter->Next;

			return Iter->Element;
		}

		inline const Type& GetByIndex(unsigned long Index) const
		{
			const Node* Iter = this;
			for (unsigned long i = 0; i < Index; i++)
				Iter = Iter->Next;

			return Iter->Element;
		}

		inline const Node* GetNode(const Key* Key, unsigned long long Count) const
		{
			for (const Node* Iter = this; Iter; Iter = Iter->Next)
			{
				if (Iter->IsEqual(Key, Count))
					return Iter;
			}

			return 0;
		}

		inline Node* GetNode(const Key* Key, unsigned long long Count)
		{
			for (Node* Iter = this; Iter; Iter = Iter->Next)
			{
				if (Iter->IsEqual(Key, Count))
					return Iter;
			}

			return 0;
		}

		inline const Type& Get(const Key* Key, unsigned long long Count) const
		{
			const Node* Current;

			Current = GetNode(Key, Count);
			if (Current == 0)
				return Default;

			return Current->Element;
		}

		inline Type& Get(const Key* Key, unsigned long long Count)
		{
			Node* Current;

			Current = GetNode(Key, Count);
			if (Current == 0)
				return Default;

			return Current->Element;
		}

		inline bool Contains(const Key* Key, unsigned long long Count) const
		{
			return GetNode(Key, Count) != 0;
		}

		inline Node* Remove(const Key* Key, unsigned long long Count)
		{
			for (Node* Current = this,* Last = 0; Current; Last = Current, Current = Current->Next)
			{
				if (Current->IsEqual(Key, Count))
				{
					Current->Unlink();
					Current->Element.~Type();

					if (!Last)
					{
						Node* Replace;

						Replace = Current->Next;

						free(Current);
						return Replace;
					}

					Last->Next = Current->Next;

					free(Current);
					break;
				}
			}

			return this;
		}

		inline void Collapse()
		{
			this->Unlink();
			this->Element.~Type();

			free(this);
		}

	public:
		constexpr const Key* GetKey() const
		{
			return Array;
		}

		constexpr unsigned long long GetKeyCount() const
		{
			return Count;
		}

		constexpr const Type& GetElement() const
		{
			return Element;
		}

		constexpr Type& GetElement()
		{
			return Element;
		}

	private:
		Node* Next;
		unsigned long long Count;

		Type Element;
		Key Array[1];
	};

public:
	class ValueIterator
	{
	private:
		class Iterator
		{
		public:
			constexpr Iterator()
			{
			}

		public:
			constexpr Iterator& operator++()
			{
				RunNode = (Node*)RunNode->GetNext();
				return *this;
			}

			constexpr Iterator& operator++(int)
			{
				return operator++();
			}

			constexpr Iterator& operator--()
			{
				RunNode = (Node*)RunNode->GetPrev();
				return *this;
			}

			constexpr Iterator& operator--(int)
			{
				return operator--();
			}

			constexpr Type* operator->() const
			{
				return &RunNode->GetElement();
			}

			constexpr Type& operator*() const
			{
				return RunNode->GetElement();
			}

			constexpr bool operator==(const Iterator& Second) const
			{
				return RunNode == Second.RunNode;
			}

			constexpr bool operator!=(const Iterator& Second) const
			{
				return !operator==(Second);
			}

		private:
			constexpr Iterator(Node* InitialNode) : RunNode(InitialNode)
			{
			}

		private:
			Node* RunNode;

		private:
			friend class ValueIterator;
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
				RunNode = (const Node*)RunNode->GetNext();
				return *this;
			}

			constexpr ConstIterator& operator++(int)
			{
				return operator++();
			}

			constexpr ConstIterator& operator--()
			{
				RunNode = (const Node*)RunNode->GetPrev();
				return *this;
			}

			constexpr ConstIterator& operator--(int)
			{
				return operator--();
			}

			constexpr const Type* operator->() const
			{
				return &RunNode->GetElement();
			}

			constexpr const Type& operator*() const
			{
				return RunNode->GetElement();
			}

			constexpr bool operator==(const ConstIterator& Second) const
			{
				return RunNode == Second.RunNode;
			}

			constexpr bool operator!=(const ConstIterator& Second) const
			{
				return !operator==(Second);
			}

		private:
			constexpr ConstIterator(const Node* InitialNode) : RunNode(InitialNode)
			{
			}

		private:
			const Node* RunNode;

		private:
			friend class ValueIterator;
		};

	public:
		constexpr ValueIterator(const ListLink* BaseLink) : BaseLink(BaseLink)
		{
		}

		constexpr Iterator begin()
		{
			return Iterator((Node*)BaseLink->GetNext());
		}

		constexpr Iterator end()
		{
			return Iterator((Node*)BaseLink);
		}

		constexpr ConstIterator begin() const
		{
			return ConstIterator((const Node*)BaseLink->GetNext());
		}

		constexpr ConstIterator end() const
		{
			return ConstIterator((const Node*)BaseLink);
		}

	private:
		const ListLink* BaseLink;
	};

	class KeyIterator
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
				RunNode = (Node*)RunNode->GetNext();
				return *this;
			}

			constexpr Iterator& operator++(int)
			{
				return operator++();
			}

			constexpr Iterator& operator--()
			{
				RunNode = (Node*)RunNode->GetPrev();
				return *this;
			}

			constexpr Iterator& operator--(int)
			{
				return operator--();
			}

			constexpr ArrayBase<const Key> operator*() const
			{
				return ArrayBase<const Key>(RunNode->GetKey(), RunNode->GetKeyCount());
			}

			constexpr bool operator==(const Iterator& Second) const
			{
				return RunNode == Second.RunNode;
			}

			constexpr bool operator!=(const Iterator& Second) const
			{
				return !operator==(Second);
			}

		private:
			constexpr Iterator(const Node* InitialNode) : RunNode(InitialNode)
			{
			}

		private:
			const Node* RunNode;

		private:
			friend class KeyIterator;
		};

	public:
		constexpr KeyIterator(const ListLink* BaseLink) : BaseLink(BaseLink)
		{
		}

		constexpr Iterator begin() const
		{
			return Iterator((const Node*)BaseLink->GetNext());
		}

		constexpr Iterator end() const
		{
			return Iterator((const Node*)BaseLink);
		}

	private:
		const ListLink* BaseLink;
	};

public:
	constexpr HashMap()
	{
	}

	inline HashMap(unsigned char InitialSizeBits)
	{
		this->IndexBits = InitialSizeBits;
		this->EntryMap = (Node**)malloc((1ull << InitialSizeBits) * sizeof(Node*));

		memset(this->EntryMap, 0, (1ull << InitialSizeBits) * sizeof(Node*));
	}

public:
	inline HashMap(const HashMap& Copy)
	{
		this->operator=(Copy);
	}

	inline HashMap(HashMap&& Move)
	{
		this->operator=((HashMap&&)Move);
	}

	inline ~HashMap()
	{
		if (EntryMap)
		{
			Flush();
			free(EntryMap);
			EntryMap = 0;
		}
	}

public:
	inline HashMap& operator=(const HashMap& Copy)
	{
		this->EntryCount = 0;
		this->IndexBits = Copy.IndexBits;
		this->EntryMap = (Node**)malloc((1ull << Copy.IndexBits) * sizeof(Node*));

		memset(this->EntryMap, 0, (1ull << Copy.IndexBits) * sizeof(Node*));

		for (Node* Current = (Node*)Copy.BaseLink.GetNext(); Current != &Copy.BaseLink; Current = (Node*)Current->GetNext())
			Add(Current->GetKey(), Current->GetKeyCount(), Current->GetElement());

		return *this;
	}

	inline HashMap& operator=(HashMap&& Move)
	{
		this->BaseLink.operator=((ListLink&&)Move.BaseLink);
		this->EntryMap = Move.EntryMap;
		this->IndexBits = Move.IndexBits;
		this->EntryCount = Move.EntryCount;

		Move.EntryMap = 0;

		return *this;
	}

public:
	inline Type& operator[](const Key& Key)
	{
		return Get(&Key, 1);
	}

	inline const Type& operator[](const Key& Key) const
	{
		return Get(&Key, 1);
	}

public:
	constexpr ValueIterator GetIterator()
	{
		return ValueIterator(&BaseLink);
	}

	constexpr const ValueIterator GetIterator() const
	{
		return ValueIterator(&BaseLink);
	}

	constexpr const KeyIterator GetKeyIterator() const
	{
		return KeyIterator(&BaseLink);
	}

	inline void Add(const Key& Key, const Type& Element)
	{
		Add(&Key, 1, Element);
	}

	inline void Add(const Key* Key, unsigned long long Count, const Type& Element)
	{
		unsigned long Index;

		Resize();

		Index = GetHashIndex(Key, Count);
		if (EntryMap[Index] == 0)
		{
			EntryCount++;
			EntryMap[Index] = Node::Create(BaseLink, Key, Count, Element);
			return;
		}

		if (EntryMap[Index]->Add(BaseLink, Key, Count, Element))
			EntryCount++;
	}

	inline unsigned long long ReserveIndex(const Key& Key, bool* Reserved)
	{
		return ReserveIndex(&Key, 1, Reserved);
	}

	inline unsigned long long ReserveIndex(const Key* Key, unsigned long long Count, bool* Reserved)
	{
		unsigned long ReserveIndex;
		unsigned long Index;

		Resize();

		Index = GetHashIndex(Key, Count);
		if (EntryMap[Index] == 0)
		{
			*Reserved = true;

			EntryCount++;
			EntryMap[Index] = Node::Create(BaseLink, Key, Count);
			return Index;
		}

		ReserveIndex = EntryMap[Index]->ReserveIndex(BaseLink, Key, Count, Reserved);
		if (*Reserved)
			EntryCount++;

		return (((unsigned long long)ReserveIndex) << 32) | ((unsigned long long)Index);
	}

	inline unsigned long long GetIndex(const Key& Key) const
	{
		return GetIndex(&Key, 1);
	}

	inline unsigned long long GetIndex(const Key* Key, unsigned long long Count) const
	{
		unsigned long ReserveIndex;
		unsigned long Index;

		Index = GetHashIndex(Key, Count);
		if (EntryMap[Index] == 0)
			return ~0;

		ReserveIndex = EntryMap[Index]->GetIndex(Key, Count);
		if (ReserveIndex == ~0)
			return ~0;

		return (((unsigned long long)ReserveIndex) << 32) | ((unsigned long long)Index);
	}

	inline Type& GetByIndex(unsigned long long Index)
	{
		if (Index == ~0)
			return Default;

		return EntryMap[Index & ((1ull << 32) - 1)]->GetByIndex(Index >> 32);
	}

	inline const Type& GetByIndex(unsigned long long Index) const
	{
		if (Index == ~0)
			return Default;

		return EntryMap[Index & ((1ull << 32) - 1)]->GetByIndex(Index >> 32);
	}

	inline const Type& Get(const Key* Key, unsigned long long Count) const
	{
		unsigned long long Index;

		Index = GetHashIndex(Key, Count);
		if (EntryMap[Index] == 0)
			return Default;

		return EntryMap[Index]->Get(Key, Count);
	}

	inline Type& Get(const Key* Key, unsigned long long Count)
	{
		unsigned long long Index;

		Index = GetHashIndex(Key, Count);
		if (EntryMap[Index] == 0)
			return Default;

		return EntryMap[Index]->Get(Key, Count);
	}

	inline void Remove(const Key* Key, unsigned long long Count)
	{
		unsigned long long Index;

		Index = GetHashIndex(Key, Count);
		if (EntryMap[Index] == 0)
			return;

		EntryMap[Index]->Remove(Key, Count);
	}

	inline void Flush()
	{
		for (Node* Current = (Node*)BaseLink.GetNext(); BaseLink.GetNext() != &BaseLink; Current = (Node*)BaseLink.GetNext())
			Current->Collapse();

		memset(EntryMap, 0, EntryCount * sizeof(Node*));
		EntryCount = 0;
	}

private:
	inline void Resize()
	{
		if (EntryCount < (1ull << IndexBits))
			return;

		Node* Base;

		Base = (Node*)BaseLink.GetPrev();
		BaseLink.Unlink();

		free(EntryMap);

		EntryCount = 0;
		BaseLink = ListLink();

		IndexBits++;

		EntryMap = (Node**)malloc((1ull << IndexBits) * sizeof(Node*));
		memset(EntryMap, 0, (1ull << IndexBits) * sizeof(Node*));

		for (Node* Current = (Node*)Base->GetNext(); Base->GetNext() != Base; Current = (Node*)Base->GetNext())
		{
			Add(Current->GetKey(), Current->GetKeyCount(), Current->GetElement());
			Current->Collapse();
		}

		Add(Base->GetKey(), Base->GetKeyCount(), Base->GetElement());
		Base->Collapse();
	}

	constexpr unsigned long GetHashIndex(const Key* Key, unsigned long long Count) const
	{
		return GetHashIndex(Create64Hash(Key, Count * sizeof(*Key)));
	}

	constexpr unsigned long GetHashIndex(unsigned long long Hash) const
	{
		return Hash & ((1ull << IndexBits) - 1);
	}

	static constexpr unsigned long long Create64Hash(const void* Buffer, unsigned long BufferSize)
	{
		unsigned long long Hash64 = 14695981039346656037;
		const unsigned long Prime = 591798841;

		unsigned long long Cycles;
		unsigned long long NDhead;

		const char* RunKey = (const char*)Buffer;
		if (BufferSize > 8)
		{
			Cycles = ((BufferSize - 1) >> 4ull) + 1;
			NDhead = BufferSize - (Cycles << 3);

			for (; Cycles--; RunKey += 8)
			{
				Hash64 = (Hash64 ^ (*(unsigned long long*)(RunKey))) * Prime;
				Hash64 = (Hash64 ^ (*(unsigned long long*)(RunKey + NDhead))) * Prime;
			}
		}
		else if (BufferSize)
			Hash64 = (Hash64 ^ ((*(unsigned long long*)(RunKey) << ((8 - BufferSize) << 3)) >> ((8 - BufferSize) << 3))) * Prime;

		return Hash64;
	}

private:
	Node** EntryMap = 0;
	ListLink BaseLink = ListLink();

	unsigned char IndexBits = 0;
	unsigned long long EntryCount = 0;

private:
	static Type Default;
};

template<typename Key, typename Type>
Type HashMap<Key, Type>::Default = Type();