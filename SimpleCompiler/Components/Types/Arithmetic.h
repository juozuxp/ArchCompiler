#pragma once
#include "TypeElement.h"
#include "../../Utilities/RefObject.h"
#include "../../Utilities/Deflatable.h"
#include "../Transferable/Transferable.h"
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

class DefinitionValue
{
public:
	constexpr DefinitionValue()
	{
	}

	constexpr DefinitionValue(const char* Definition, unsigned long long Value) : Definition(Definition), Value(Value)
	{
	}

public:
	inline bool IsType(const char* Expression, unsigned long long Length) const
	{
		if (!Length)
			Length = strlen(Expression);

		return !strncmp(Expression, Definition, Length);
	}

	constexpr unsigned long long GetValue() const
	{
		return Value;
	}

private:
	const char* Definition = 0;
	unsigned long long Value = 0;
};

class Arithmetic : TypeElement
{
private:
	class Operand
	{
	public:
		constexpr Operand()
		{
		}

	public:
		virtual void Compile(class CompileMap& Enviroment, RegisterType Source)
		{
		}
	};

	class TranferOperator : Operand
	{
	public:
		constexpr TranferOperator()
		{
		}

		inline TranferOperator(RefObject<Transferable> Source) : Source(Source)
		{
		}

	public:
		void Compile(class CompileMap& Enviroment, RegisterType Source);

	private:
		RefObject<Transferable> Source;
	};

	class Operation : public Operand
	{
	public:
		constexpr Operation()
		{
		}

	protected:
		inline Operation(RefObject<Operand> Left, RefObject<Operand> Right, RegisterType TransitionSpace) : Left(Left), Right(Right), TransitionSpace(TransitionSpace)
		{
		}

	protected:
		RefObject<Operand> Left;
		RefObject<Operand> Right;
		RegisterType TransitionSpace;
	};

	class Addition : Operation
	{
	public:
		constexpr Addition()
		{
		}

		inline Addition(RefObject<Operand> Left, RefObject<Operand> Right, RegisterType TransitionSpace) : Operation(Left, Right, TransitionSpace)
		{
		}

	public:
		void Compile(class CompileMap& Enviroment, RegisterType Source);
	};

	class Subtraction : Operation
	{
	public:
		constexpr Subtraction()
		{
		}

		inline Subtraction(RefObject<Operand> Left, RefObject<Operand> Right, RegisterType TransitionSpace) : Operation(Left, Right, TransitionSpace)
		{
		}

	public:
		void Compile(class CompileMap& Enviroment, RegisterType Source);
	};

public:
	constexpr Arithmetic() : TypeElement()
	{
	}

public:
	static bool IsArtimetic(const char* Expression);

public:
	unsigned short GetRegisterMask();

	void Compile(class CompileMap& Enviroment);

	unsigned long long Parse(class EnviromentMap& Enviroment, const char* Expression);
	unsigned long long Parse(class EnviromentMap& Enviroment, const char* Expression, RefObject<Transferable> AssignTo);

private:
	RefObject<Operand> EvaluateArthmetic(class EnviromentMap& Enviroment, const char* Expression);

private:
	static const char* HuntEnclosure(const char* Expression);
	static List<char> ExtractEnclosure(const char* Expression);
	static const char* LocateOperation(const char* Expression, const OperationDef** OperationDescription);
	static const DefinitionValue* ExtractDefinitionValue(const char* Expression, unsigned long long Length);

private:
	RefObject<Operand> Origin;
	TempVariableMap TemporarySpace;
	RefObject<Transferable> AssignTo;

private:
	static constexpr Deflatable Deflater = Deflatable(" \t");
	static constexpr OperationDef Operations[] = { OperationDef(OperationDef::OperationType_Addition, '+'), OperationDef(OperationDef::OperationType_Subtraction, '-'), OperationDef(OperationDef::OperationType_Division, '/'), 
												   OperationDef(OperationDef::OperationType_Multiplication, '*'), OperationDef(OperationDef::OperationType_Modulus, '%'), OperationDef(OperationDef::OperationType_Or, '|'), 
												   OperationDef(OperationDef::OperationType_Xor, '^'), OperationDef(OperationDef::OperationType_And, '&') };
	static constexpr DefinitionValue DefValues[] = { DefinitionValue("true", 1), DefinitionValue("false", 0) };
};