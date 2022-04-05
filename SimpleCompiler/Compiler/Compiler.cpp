#include "Compiler.h"
#include "CompileMap.h"
#include "CompilerProduct.h"
#include "../Parser/SyntaxParser.h"

Compiler::Compiler(const char* Code) : Compiler(SyntaxParser::Parse(Code))
{
}

CompilerProduct Compiler::Compile()
{
	CompileMap CompiledEnviroment;

	BaseEnviroment->Compile(CompiledEnviroment);

	return CompiledEnviroment.CreateProduct(BaseEnviroment);
}