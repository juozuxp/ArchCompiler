#include "Compiler.h"
#include "CompileMap.h"
#include "CompilerProduct.h"
#include "../Parser/SyntaxParser.h"

Compiler::Compiler(const char* Buffer, bool FilePath) : Compiler(FilePath ? SyntaxParser::ParseFile(Buffer) : SyntaxParser::Parse(Buffer))
{
}

CompilerProduct Compiler::Compile()
{
	CompileMap CompiledEnviroment;

	BaseEnviroment->Compile(CompiledEnviroment);

	return CompiledEnviroment.CreateProduct(BaseEnviroment);
}