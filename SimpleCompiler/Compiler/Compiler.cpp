#include "Compiler.h"
#include "Assembler.h"
#include "../Components/CompileMap.h"

Compiler::Compiler(const EnviromentMap& CompileElements) : Enviroment(CompileElements)
{
	StackSize = EstimateStackSize();
}

List<unsigned char> Compiler::Compile()
{
	Assembler Assembly = Assembler(StackSize);
	List<unsigned char> Assembled = List<unsigned char>(0);

	Assembled.Add(Assembly.AssembleStart());
	Assembled.Add(CompileEnviroment());
	Assembled.Add(Assembly.AssembleEnd());

	return Assembled;
}

List<unsigned char> Compiler::CompileEnviroment()
{
	CompileMap CompilationMap = CompileMap(StackSize);
	List<unsigned char> Compiled = List<unsigned char>();
	for (RefObject<ParserElement> Element : Enviroment.ParseElements)
		Compiled.Add(Element->Compile(CompilationMap));

	return Compiled;
}

unsigned long long Compiler::EstimateStackSize()
{
	unsigned long long StackSize = 0;
	for (RefObject<ParserElement> Element : Enviroment.ParseElements)
		StackSize += Element->GetStackSize();

	StackSize = (StackSize + ((1 << 3) - 1)) & ~((1 << 3) - 1); // Stack alignment, making sure that it's 8 byte alligned
	StackSize |= (1 << 3); // Stack alignment, making sure the 16 byte missalignment is fixed

	return StackSize;
}