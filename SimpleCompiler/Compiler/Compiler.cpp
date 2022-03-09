#include "Compiler.h"
#include "Assembler.h"
#include "../Components/CompileMap.h"
#include "../Components/EnviromentMap.h"

Compiler::Compiler(RefObject<FileEnviromentMap> CompileElements) : Enviroment(CompileElements)
{
}

List<unsigned char> Compiler::Compile()
{
	List<unsigned char> Compiled = List<unsigned char>(0);
	for (RefObject<EnviromentMap> Enviroment : Enviroment->FunctionMaps)
		Compiled.Add(CompileEnviroment(*Enviroment));

	return Compiled;
}

List<unsigned char> Compiler::CompileEnviroment(const EnviromentMap& Enviroment)
{
	List<unsigned char> Compiled = List<unsigned char>(0);

	unsigned long long StackSize = EstimateStackSize(Enviroment);

	Assembler Assembly = Assembler(StackSize);

	Compiled.Add(Assembly.AssembleStart());

	CompileMap CompilationMap = CompileMap(StackSize);
	for (RefObject<ParserElement> Element : Enviroment.ParseElements)
		Compiled.Add(Element->Compile(CompilationMap));

	Compiled.Add(Assembly.AssembleEnd());

	return Compiled;
}

unsigned long long Compiler::EstimateStackSize(const EnviromentMap& Enviroment)
{
	unsigned long long StackSize = 0;
	for (RefObject<ParserElement> Element : Enviroment.ParseElements)
		StackSize += Element->GetStackSize();

	StackSize = (StackSize + ((1 << 3) - 1)) & ~((1 << 3) - 1); // Stack alignment, making sure that it's 8 byte alligned
	StackSize |= (1 << 3); // Stack alignment, making sure the 16 byte missalignment is fixed

	return StackSize;
}