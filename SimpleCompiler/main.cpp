#include <Windows.h>
#include "Parser/SyntaxParser.h"
#include <stdio.h>
#include "Compiler/Compiler.h"

void Test(unsigned long long A, unsigned long long B, unsigned long long C, unsigned long long D, unsigned long long E)
{
	printf("Hello %llu %llu %llu %llu %llu\n", A, B, C, D, E);
}

void AttemptExecution(List<unsigned char> ShellCode)
{
	unsigned long OldProtection;

	VirtualProtect(ShellCode, ShellCode.GetCount(), PAGE_EXECUTE_READWRITE, &OldProtection);

	printf("%llX\n", ShellCode.operator unsigned char *());
	system("pause");

	printf("Done: %llX", ((unsigned long long(*)(void*))ShellCode.operator unsigned char* ())(Test));
}

int main()
{
	const char* Enviroment = "uint main(ulong CallMe)"
							 "	CallMe(0, 1, 2, 3, 1337);"
							 "	return main == main;"
							 "	ushort Type = ((80 + 1) + (80 + (90 + 100 + (100 + 80 + (70 + 90)))));\n"
							 "	uint Hello = true;\n"
							 "	ulong Shlong = main;"
							 "	while (Type)"
							 "		Type = Type - 1;"
							 "	if (CallMe)"
							 "		main(CallMe - 1);"
							 "	else"
							 "		Hello = false;"
							 "	ulong Another = 10000000000000;\n"
							 "	uint Variable = Another - Type + Hello;"
							 "	Hello = Hello + Type + Another + Variable;"
							 "\n"
							 "uint Test(uint Hello, uint World, uint Test, uint Yes)"
							 "	uint This_was_a_test = 10;"
							 "	main(This_was_a_test, 10, 50, 80, 100, Yes);"
							 "uint FuckOff()";

	RefObject<FileEnviromentMap> Map = SyntaxParser::Parse(Enviroment);

	List<unsigned char> Buffer = Compiler(Map).Compile();

	AttemptExecution(Buffer);
}