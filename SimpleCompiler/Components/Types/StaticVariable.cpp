#include "StaticVariable.h"
#include "../../Utilities/SimpleUtilities.h"
#include "../Enviroments/EnviromentMap.h"
#include "../../Compiler/CompileMap.h"
#include "Arithmetic.h"

#define SHELL_RELATIVITY MainRelativity
#include "../../Utilities/x86_x64Shell.h"

void StaticVariable::CompileAssign(CompileMap& Enviroment, RegisterType Source)
{
	unsigned long MainRelativity;

	MainRelativity = 0;
	switch (GetVariableSize())
	{
	case 1:
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXR, MOVB_RM_R(REL_DO_R(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				MOVB_RM_R(REL_DO_R(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	case 2:
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXR, PFX_WORD, MOVD_RM_R(REL_DO_R(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_WORD, MOVD_RM_R(REL_DO_R(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	case 4:
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXR, MOVD_RM_R(REL_DO_R(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				MOVD_RM_R(REL_DO_R(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	case 8:
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXRW, PFX_WORD, MOVD_RM_R(REL_DO_R(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_RM_R(REL_DO_R(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	}
}

void StaticVariable::CompileRetrieve(CompileMap& Enviroment, RegisterType Source)
{
	unsigned long MainRelativity;

	MainRelativity = 0;
	switch (GetVariableSize())
	{
	case 1:
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXR, MOVB_RM_R(R_REL_DO(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				MOVB_RM_R(R_REL_DO(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	case 2:
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXR, PFX_WORD, MOVD_RM_R(R_REL_DO(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_WORD, MOVD_RM_R(R_REL_DO(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	case 4:
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXR, MOVD_RM_R(R_REL_DO(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				MOVD_RM_R(R_REL_DO(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	case 8:
	{
		if (Source.IsExtended())
		{
			unsigned char Shell[] =
			{
				PFX_REXRW, PFX_WORD, MOVD_RM_R(R_REL_DO(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
		else
		{
			unsigned char Shell[] =
			{
				PFX_REXW, MOVD_RM_R(R_REL_DO(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
			};

			Enviroment.AddCode(Shell, sizeof(Shell));
		}
	} break;
	}
}

void StaticVariable::CompileRefrence(CompileMap& Enviroment, RegisterType Source)
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

void StaticVariable::PreCompile(CompileMap& Enviroment)
{
	if (Assigner)
		Assigner->PreCompile(Enviroment);

	Enviroment.AllocStaticSpace(GetVariableSize());
}

void StaticVariable::Compile(CompileMap& Enviroment)
{
	DataPosition = Enviroment.AllocStaticSpace(GetVariableSize());
	if (Assigner)
		Assigner->Compile(Enviroment);
}

void StaticVariable::CompileCall(CompileMap& Enviroment)
{
	unsigned long MainRelativity;

	MainRelativity = 0;
	unsigned char Shell[] =
	{
		CALLQ_RM(REL_DO(DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
	};

	Enviroment.AddCode(Shell, sizeof(Shell));
}