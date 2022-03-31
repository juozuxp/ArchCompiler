#include "OperationDef.h"
#include "Operand.h"
#include "../../../Compiler/TempVariableMap.h"

const char* OperationDefs::LocateOperation(const char* Expression, const OperationDef** OperationDescription)
{
	for (; *Expression; Expression++)
	{
		for (unsigned long long i = 0; i < ARRAY_COUNT(Operations); i++)
		{
			if (Operations[i].IsOperation(Expression))
			{
				if (OperationDescription)
				{
					*OperationDescription = 0;

					const OperationDef* CuurentFit = &Operations[i];
					while (*OperationDescription != CuurentFit)
					{
						*OperationDescription = CuurentFit;
						for (unsigned long long ii = 0; ii < ARRAY_COUNT(Operations); ii++)
						{
							if (Operations[i].IsBetterFit(CuurentFit, Expression))
							{
								CuurentFit = &Operations[ii];
								break;
							}
						}
					}
				}

				return Expression;
			}
		}
	}

	return 0;
}

RefObject<Operand> OperationDef::CreateOperation(RefObject<Operand> First, RefObject<Operand> Second, RegisterType TransitionSpace) const
{
	return CreateOperator(First, Second, TransitionSpace);
}