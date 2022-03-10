#include <Windows.h>
#include "Parser/SyntaxParser.h"
#include "Compiler/Compiler.h"
#include <stdio.h>

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
	const char* Enviroment = "int main()"\
							 "	ushort Type = 80;\n"\
							 "	uchar Hello = 100;\n"\
							 "	ulong Another = 8000;\n"
							 "	int Variable = Another - Type + Hello;"\
							 "	Hello = Hello + Type + Another + Variable;"\
							 "int Test()";

	SyntaxParser Parser = SyntaxParser(Enviroment);
	RefObject<FileEnviromentMap> Map = Parser.ParseEnviroment();
	Compiler Compile = Compiler(Map);

	List<unsigned char> Buffer = Compile.Compile();

	AttemptExecution(Buffer);
}