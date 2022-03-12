#include <Windows.h>
#include "Parser/SyntaxParser.h"
#include <stdio.h>
#include "Compiler/Compiler.h"

void AttemptExecution(List<unsigned char> ShellCode)
{
	unsigned long OldProtection;

	VirtualProtect(ShellCode, ShellCode.GetCount(), PAGE_EXECUTE_READWRITE, &OldProtection);

	printf("%llX\n", ShellCode.operator unsigned char *());
	system("pause");

	((void(*)())ShellCode.operator unsigned char* ())();
}

int main()
{
	const char* Enviroment = "int main()"
							 "	ushort Type = ((80 + 1) + (80 + 90));\n"
							 "	uchar Hello = 100;\n"
							 "	ulong Another = 8000;\n"
							 "	int Variable = Another - Type + Hello;"
							 "	Hello = Hello + Type + Another + Variable;"
							 "\n"
							 "int Test(int Hello, int World, int Test, int Yes)"
							 "	int This_was_a_test = 10;"
							 "	main(This_was_a_test, 10, 50, 80, 100, Yes);";

	RefObject<FileEnviromentMap> Map = SyntaxParser::Parse(Enviroment);

	List<unsigned char> Buffer = Compiler(Map).Compile();

	AttemptExecution(Buffer);
}