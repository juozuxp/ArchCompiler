#pragma once
#include "TypeElement.h"
#include "../../Utilities/RefObject.h"
#include "../../Utilities/Deflatable.h"
#include "../Transferable/Transferable.h"
#include "../../Compiler/TempVariableMap.h"
#include "../../Utilities/SimpleUtilities.h"

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
		OperationType_LogicXor,
		OperationType_LogicAnd,
		OperationType_LogicOr,

		OperationType_And, // Conditional operations (yes arithmatic is gonna be conditional, this is way better than doing something simple and mundain)
		OperationType_Or,
		OperationType_Less,
		OperationType_Over,
		OperationType_LessOrEqual,
		OperationType_OverOrEqual,
		OperationType_Equal,
		OperationType_NotEqual
	};

public:
	constexpr OperationDef()
	{
	}

	constexpr OperationDef(OperationType Type, const char* SymbolSet, unsigned long long SetLength) : Type(Type), SymbolSet(SymbolSet), SetLength(SetLength)
	{
	}

public:
	inline bool IsOperation(const char* SymbolSet) const
	{
		return !strncmp(this->SymbolSet, SymbolSet, SetLength);
	}

	inline bool IsBetterFit(const OperationDef* Operation, const char* SymbolSet) const
	{
		if (SetLength <= Operation->SetLength)
			return false;

		return IsOperation(SymbolSet);
	}

	constexpr OperationType GetType() const
	{
		return Type;
	}

	constexpr unsigned long long ExpressionSize() const
	{
		return SetLength;
	}

private:
	const char* SymbolSet = 0;
	unsigned long long SetLength = 0;

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

class Arithmetic : public TypeElement
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

	class Equal : Operation
	{
	public:
		constexpr Equal()
		{
		}

		inline Equal(RefObject<Operand> Left, RefObject<Operand> Right, RegisterType TransitionSpace) : Operation(Left, Right, TransitionSpace)
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
	void PreCompile(class CompileMap& Enviroment);
	void Compile(class CompileMap& Enviroment);

	unsigned long long Parse(RefObject<EnviromentMap> Enviroment, const char* Expression);
	unsigned long long Parse(RefObject<EnviromentMap> Enviroment, const char* Expression, RefObject<Transferable> AssignTo);

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
	static constexpr OperationDef Operations[] = { OperationDef(OperationDef::OperationType_Addition, CSL_PAR("+")), OperationDef(OperationDef::OperationType_Subtraction, CSL_PAR("-")), OperationDef(OperationDef::OperationType_Division, CSL_PAR("/")),
												   OperationDef(OperationDef::OperationType_Multiplication, CSL_PAR("*")), OperationDef(OperationDef::OperationType_Modulus, CSL_PAR("%")), OperationDef(OperationDef::OperationType_LogicOr, CSL_PAR("|")),
												   OperationDef(OperationDef::OperationType_LogicXor, CSL_PAR("^")), OperationDef(OperationDef::OperationType_LogicAnd, CSL_PAR("&")), OperationDef(OperationDef::OperationType_LogicAnd, CSL_PAR("&")),
												   OperationDef(OperationDef::OperationType_And, CSL_PAR("&&")), OperationDef(OperationDef::OperationType_Or,CSL_PAR("||")), OperationDef(OperationDef::OperationType_Less, CSL_PAR("<")),
												   OperationDef(OperationDef::OperationType_Over, CSL_PAR(">")), OperationDef(OperationDef::OperationType_LessOrEqual, CSL_PAR("<=")), OperationDef(OperationDef::OperationType_OverOrEqual, CSL_PAR(">=")),
												   OperationDef(OperationDef::OperationType_Equal, CSL_PAR("==")), OperationDef(OperationDef::OperationType_NotEqual, CSL_PAR("!=")) };
	static constexpr DefinitionValue DefValues[] = { DefinitionValue("true", 1), DefinitionValue("false", 0) };
};