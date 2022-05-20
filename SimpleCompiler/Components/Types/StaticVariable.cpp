#include "StaticVariable.h"
#include "../../Utilities/SimpleUtilities.h"
#include "../Enviroments/EnviromentMap.h"
#include "../../Compiler/CompileMap.h"
#include "Arithmetic.h"

#define SHELL_RELATIVITY MainRelativity
#include "../../Utilities/x86_x64Shell.h"

void StaticVariable::CompileAssign(CompileMap& Enviroment, RegisterType Source, long long Dimension)
{
	unsigned long MainRelativity;

	MainRelativity = 0;

	if (!Dimension)
	{
		switch (GetVariableAssignSize())
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
					PFX_REXRW, MOVD_RM_R(REL_DO_R(Source, DataPosition - (MainRelativity + Enviroment.GetCodeLocation() + Enviroment.GetStaticSpaceSizeAlligned())))
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
	else
	{
		CompileRetrieve(Enviroment, RegisterType::Type_RCX);
		switch (GetReferenceMultiplier(0))
		{
		case 1:
		{
			if (Source.IsExtended())
			{
				unsigned char Shell[] =
				{
					PFX_REXR, MOVB_RM_R(MR_DO_R(RCX, Source, GetReferenceMultiplier(0) * Dimension))
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					MOVB_RM_R(MR_DO_R(RCX, Source, GetReferenceMultiplier(0) * Dimension))
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
					PFX_REXR, PFX_WORD, MOVD_RM_R(MR_DO_R(RCX, Source, GetReferenceMultiplier(0) * Dimension))
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					PFX_WORD, MOVD_RM_R(MR_DO_R(RCX, Source, GetReferenceMultiplier(0) * Dimension))
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
					PFX_REXR, MOVD_RM_R(MR_DO_R(RCX, Source, GetReferenceMultiplier(0) * Dimension))
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					MOVD_RM_R(MR_DO_R(RCX, Source, GetReferenceMultiplier(0) * Dimension))
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
					PFX_REXRW, MOVD_RM_R(MR_DO_R(RCX, Source, GetReferenceMultiplier(0) * Dimension))
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
			else
			{
				unsigned char Shell[] =
				{
					PFX_REXW, MOVD_RM_R(MR_DO_R(RCX, Source, GetReferenceMultiplier(0) * Dimension))
				};

				Enviroment.AddCode(Shell, sizeof(Shell));
			}
		} break;
		}
	}
}

void StaticVariable::CompileRetrieve(CompileMap& Enviroment, RegisterType Source)
{
	unsigned long MainRelativity;

	if (VariabelDimension != 1)
	{
		CompileRefrence(Enviroment, Source);
		return;
	}

	MainRelativity = 0;
	switch (GetVariableRetrieveSize())
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

	Enviroment.AllocStaticSpace(GetVariableAllocationSize());
}

void StaticVariable::Compile(CompileMap& Enviroment)
{
	constexpr unsigned long long Default = 0;

	DataPosition = Enviroment.AllocStaticSpace(GetVariableAllocationSize());
	if (Assigner)
		Assigner->Compile(Enviroment);
	else
		Enviroment.PatchStaticSpace(DataPosition, (unsigned char*)&Default, GetVariableAllocationSize());
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