#include "OperationDef.h"
#include "Operand.h"
#include "../../../Compiler/TempVariableMap.h"

const char* OperationDefs::LocateDualOperation(const char* Expression, const DualOperation** OperationDescription)
{
	for (; *Expression; Expression++)
	{
		if (*Expression == '\"')
		{
			Expression = StringEncap.GetEncapEnd(Expression);
			continue;
		}

		for (unsigned long long i = 0; i < ARRAY_COUNT(DualOperations); i++)
		{
			if (DualOperations[i].IsOperation(Expression))
			{
				if (OperationDescription)
				{
					*OperationDescription = 0;

					const DualOperation* CuurentFit = &DualOperations[i];
					while (*OperationDescription != CuurentFit)
					{
						*OperationDescription = CuurentFit;
						for (unsigned long long ii = 0; ii < ARRAY_COUNT(DualOperations); ii++)
						{
							if (DualOperations[i].IsBetterFit(CuurentFit, Expression))
							{
								CuurentFit = &DualOperations[ii];
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

const SingularOperation* OperationDefs::LocateSingularOperation(const char* Expression)
{
	for (unsigned long long i = 0; i < ARRAY_COUNT(SingularOperations); i++)
	{
		if (SingularOperations[i].IsOperation(Expression))
		{
			const SingularOperation* CuurentFit = &SingularOperations[i];
			const SingularOperation* LastFit = 0;

			while (LastFit != CuurentFit)
			{
				LastFit = CuurentFit;
				for (unsigned long long ii = 0; ii < ARRAY_COUNT(SingularOperations); ii++)
				{
					if (SingularOperations[i].IsBetterFit(CuurentFit, Expression))
					{
						CuurentFit = &SingularOperations[ii];
						break;
					}
				}
			}

			return CuurentFit;
		}
	}

	return 0;
}

RefObject<Operand> DualOperation::CreateOperation(RefObject<Operand> First, RefObject<Operand> Second, RegisterType TransitionSpace) const
{
	return CreateOperator(First, Second, TransitionSpace);
}

RefObject<Operand> SingularOperation::CreateOperation(RefObject<Operand> Operand) const
{
	return CreateOperator(Operand);
}