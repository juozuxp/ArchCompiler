#include "Import.h"
#include "../../Compiler/CompileMap.h"
#include <string.h>

Import::Import(const char* Expression)
{
	const char* EncapStart;
	const char* EncapEnd;

	VariableName = ExtractName(strstr(Expression, "import") + sizeof("import") - 1);

	EncapStart = strchr(Expression, '\"');
	EncapEnd = StringEncap.GetEncapEnd(EncapStart);

	SourceName.Add(EncapStart + 1, EncapEnd - (EncapStart + 1));
	SourceName.Add('\0');

	EncapStart = strchr(EncapEnd + 1, '\"');
	EncapEnd = StringEncap.GetEncapEnd(EncapStart);

	FunctionName.Add(EncapStart + 1, EncapEnd - (EncapStart + 1));
	FunctionName.Add('\0');

	VariableSize = 8;
	VariableReference = 1;
}

bool Import::IsExpression(const char* Expression)
{
	Expression = Ignorable.Skip(Expression);
	if (strncmp(Expression, "import", sizeof("import") - 1))
		return false;

	if (!Ignorable.IsSkippable(*(Expression + sizeof("import") - 1)) && *(Expression + sizeof("import") - 1) != '(')
		return false;

	if (!strchr(Expression, '('))
		return false;

	if (!strchr(Expression, ')'))
		return false;

	return true;
}

void Import::PreCompile(CompileMap& Enviroment)
{
	Enviroment.AllocImportStaticSpace(GetVariableSize());
}

void Import::Compile(CompileMap& Enviroment)
{
	constexpr unsigned long long Default = 0xDEADBEEFDEADBEEF; // FUCKING STUPID DESCISION AFTER STUPID DECISION, MFS MAKE NEED THE FIRST THUNK NOT TO BE ZERO FUCK SAKES

	DataPosition = Enviroment.AllocImportStaticSpace(GetVariableSize());
	Enviroment.PatchStaticSpace(DataPosition, (unsigned char*)&Default, GetVariableSize());
}