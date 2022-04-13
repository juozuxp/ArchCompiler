#include "String.h"
#include "../../Compiler/CompileMap.h"

#define SHELL_RELATIVITY MainRelativity
#include "../../Utilities/x86_x64Shell.h"

String::String(const char* Expression, unsigned long long Length)
{
	if (!Length)
		Length = strlen(Expression);

	VariableSize = 1;
	VariableReference = 1;

	VariableName.Add(Expression, Length);
	VariableName.Add('\0');
}

void String::PreCompile(CompileMap& Enviroment)
{
	Enviroment.AllocStaticSpace(VariableSize * VariableName.GetCount());
}

void String::Compile(CompileMap& Enviroment)
{
	DataPosition = Enviroment.AllocStaticSpace(VariableSize * VariableName.GetCount());
	Enviroment.PatchStaticSpace(DataPosition, (const unsigned char*)VariableName.operator char*(), VariableSize * VariableName.GetCount());
}

void String::CompileCall(CompileMap& Enviroment)
{
	unsigned long MainRelativity;

	MainRelativity = 0;
	unsigned char Shell[] =
	{
		CALL_RD(DataPosition - (MainRelativity + Enviroment.GetCodeLocation() - Enviroment.GetStaticSpaceSizeAlligned()))
	};

	Enviroment.AddCode(Shell, sizeof(Shell));
}

void String::CompileAssign(CompileMap& Enviroment, RegisterType Source)
{
}

void String::CompileRetrieve(CompileMap& Enviroment, RegisterType Source)
{
	unsigned long MainRelativity;

	MainRelativity = 0;

	if (Source.IsExtended())
	{
		unsigned char Shell[] =
		{
			PFX_REXWR, LEAD_R_M(R_REL_DO(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
	else
	{
		unsigned char Shell[] =
		{
			PFX_REXW, LEAD_R_M(R_REL_DO(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
		};

		Enviroment.AddCode(Shell, sizeof(Shell));
	}
}

void String::CompileRefrence(CompileMap& Enviroment, RegisterType Source)
{
}