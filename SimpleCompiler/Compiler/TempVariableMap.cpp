#include "TempVariableMap.h"
#include "../Parser/Assignables/AssignRegister.h"
#include "../Parser/Assignables/AssignStack.h"
#include "../Parser/Assignables/AssignDynStack.h"
#include "../Utilities/SimpleUtilities.h"

RefObject<Assignable> TempVariableMap::CreateAssignable()
{
	if (RegisterUseMask < ARRAY_COUNT(VolatileRegisters))
		return RefObject<AssignRegister>(AssignRegister(VolatileRegisters[RegisterUseMask++])).Cast<Assignable>();

	StackAllocation += 0x8;
	return RefObject<AssignDynStack>(AssignDynStack()).Cast<Assignable>();
}