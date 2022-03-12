#pragma once
#include "ParserElement.h"
#include "../../Utilities/RefObject.h"
#include "../../Utilities/Deflatable.h"
#include "../Assignables/Assignable.h"
#include "../../Compiler/TempVariableMap.h"

class OperationDef // this absolutely insists on being defined outside the parent class, holy fuck kms
{
public:
	enum OperationType
	{
		OperationType_None,
		OperationType_Addition,
		OperationType_Subtraction,
		OperationType_Division,
		OperationType_Multiplication,
		OperationType_Modulus,
		OperationType_Xor,
		OperationType_And,
		OperationType_Or
	};

public:
	constexpr OperationDef()
	{
	}

	constexpr OperationDef(OperationType Type, char Symbol) : Type(Type), Symbol(Symbol)
	{
	}

public:
	constexpr bool IsOperation(char Symbol) const
	{
		return Symbol == this->Symbol;
	}

	constexpr OperationType GetType() const
	{
		return Type;
	}

private:
	char Symbol = 0;
	OperationType Type = OperationType_None;
};

class Arithmetic : ParserElement
{
private:

	class Operand
	{
	public:
		constexpr Operand()
		{
		}

	public:
		virtual void Compile(class CompileMap& Enviroment)
		{
		}
	};

	class AVariable : Operand
	{
	public:
		constexpr AVariable()
		{
		}

		inline AVariable(RefObject<class Variable> Origin) : Origin(Origin)
		{
		}

	public:
		void Compile(class CompileMap& Enviroment);

	private:
		RefObject<class Variable> Origin;
	};

	class Value : Operand
	{
	public:
		constexpr Value()
		{
		}

		constexpr Value(unsigned long long Value) : Definition(Value)
		{
		}

	public:
		void Compile(class CompileMap& Enviroment);

	private:
		unsigned long long Definition = 0;
	};

	class Operation : public Operand
	{
	public:
		constexpr Operation()
		{
		}

	protected:
		inline Operation(RefObject<Operand> Left, RefObject<Operand> Right, RefObject<Assignable> TransitionSpace) : Left(Left), Right(Right), TransitionSpace(TransitionSpace)
		{
		}

	protected:
		RefObject<Operand> Left;
		RefObject<Operand> Right;
		RefObject<Assignable> TransitionSpace;
	};

	class Addition : Operation
	{
	public:
		constexpr Addition()
		{
		}

		inline Addition(RefObject<Operand> Left, RefObject<Operand> Right, RefObject<Assignable> TransitionSpace) : Operation(Left, Right, TransitionSpace)
		{
		}

	public:
		void Compile(class CompileMap& Enviroment);
	};

	class Subtraction : Operation
	{
	public:
		constexpr Subtraction()
		{
		}

		inline Subtraction(RefObject<Operand> Left, RefObject<Operand> Right, RefObject<Assignable> TransitionSpace) : Operation(Left, Right, TransitionSpace)
		{
		}

	public:
		void Compile(class CompileMap& Enviroment);
	};

public:
	constexpr Arithmetic() : ParserElement()
	{
	}

public:
	static bool IsArtimetic(const char* Expression);

public:
	unsigned short GetRegisterMask();
	unsigned long long GetStackSize();

	void Compile(class CompileMap& Enviroment);

	void Parse(class EnviromentMap& Enviroment, const char* Expression);
	void Parse(class EnviromentMap& Enviroment, const char* Expression, RefObject<Assignable> AssignTo);

private:
	RefObject<Operand> EvaluateArthmetic(class EnviromentMap& Enviroment, const char* Expression);

private:
	static const char* HuntEnclosure(const char* Expression);
	static List<char> ExtractEnclosure(const char* Expression);
	static const char* LocateOperation(const char* Expression, const OperationDef** OperationDescription);

private:
	RefObject<Operand> Origin;
	RefObject<Assignable> AssignTo;
	TempVariableMap TemporarySpace = TempVariableMap(1, 0); // due to the harsh circumstances this is necessary for now

private:
	static constexpr Deflatable Deflater = Deflatable(" \t");
	static constexpr OperationDef Operations[] = { OperationDef(OperationDef::OperationType_Addition, '+'), OperationDef(OperationDef::OperationType_Subtraction, '-'), OperationDef(OperationDef::OperationType_Division, '/'), 
												   OperationDef(OperationDef::OperationType_Multiplication, '*'), OperationDef(OperationDef::OperationType_Modulus, '%'), OperationDef(OperationDef::OperationType_Or, '|'), 
												   OperationDef(OperationDef::OperationType_Xor, '^'), OperationDef(OperationDef::OperationType_And, '&') };
};