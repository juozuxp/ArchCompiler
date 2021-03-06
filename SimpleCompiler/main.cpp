#include <Windows.h>
#include "Parser/SyntaxParser.h"
#include <stdio.h>
#include "Compiler/Compiler.h"
#include "Compiler/PEBuilder.h"

void Test(unsigned long long A, unsigned long long B, unsigned long long C, unsigned long long D, unsigned long long E)
{
	printf("Hello %llu %llu %llX %llu %llu\n", A, B, C, D, E);
}

void AttemptExecution(List<unsigned char> ShellCode)
{
	unsigned long OldProtection;

	VirtualProtect(ShellCode, ShellCode.GetCount(), PAGE_EXECUTE_READWRITE, &OldProtection);

	printf("%llX\n", ShellCode.operator unsigned char *());
	system("pause");

	printf("Done: %llX", ((unsigned long long(*)(unsigned long long))ShellCode.operator unsigned char* ())(12));
}

int main()
{
	/*const char* Enviroment = "import Printer(\"msvcrt.dll\", \"printf\");"
							 "import System(\"msvcrt.dll\", \"system\");"
							 "uint notsomain()"
							 "	uint HelloMain = 10;"
							 "uint main()"
							 "	ulong Type = ((80 + 1) + (80 + (90 + 100 + (100 + 80 + (70 + 90)))));\n"
							 "	Printer(\"First time printing :P\\nHere's a number to spice it up: %d\\n\", Type);"
							 "	Printer(\"Printer printing %s %s %s %s\\n\", \"Printer printing\", \"Printer printing\", \"Printer printing\", \"Printer printing\");"
							 "	System(\"pause\");"
							 "	uint* Hello = &Type;\n"
							 "	uchar** Shlong = &Hello;"
							 "	ulong testin = **Shlong;"
							 "	while (Type)"
							 "		Type = Type - 1;"
							 "	ulong Another = 10000000000000;\n"
							 "	uint Variable = Another - Type + Hello;"
							 "	Hello = Hello + Type + Another + Variable;"
							 "	notsomain(10);"
							 "	return 0;"
							 "\n"
							 "uint Test(uint Hello, uint World, uint Test, uint Yes)"
							 "	uint This_was_a_test = 10;"
							 "	main(This_was_a_test, 10, 50, 80, 100, Yes);"
							 "uint FuckOff()";*/

	const char* Fibonacci = "import print(\"msvcrt.dll\", \"printf\");"
							"import system(\"msvcrt.dll\", \"system\");"

							"void FiboRec(uint Last0, uint Last1, uint To)"
							"	if (Last1 == To)"
							"		return;"
							"	uint Next = Last0 + Last1;"
							"	print(\"%d \", Next);"
							"	FiboRec(Last1, Next, To);"

							"void main()"
							"	print(\"1 1 \");"
							"	FiboRec(1, 1, 377);"
							"	print(\"\\n\");"
							"	system(\"pause\");";


	PEBuilder("Main.AC", true).BuildExecutable("Compiled.exe");
}