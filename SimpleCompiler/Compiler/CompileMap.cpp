#include "CompileMap.h"

void CompileMap::ReassesStack()
{
	unsigned long long BackupSize;
	bool ShouldAlign;

	AllocatedStack = (AllocatedStack + ((1 << 3) - 1)) & ~((1 << 3) - 1); // Stack alignment, making sure that it's 8 byte alligned

	BackupSize = 0;
	ShouldAlign = true;
	for (unsigned short i = 0; i < 16; i++)
	{
		if (RegisterMask & (1 << i))
			BackupSize += 8;
	}

	if (!(BackupSize & (1 << 3)))
		AllocatedStack |= (1 << 3); // Stack alignment, making sure the 16 byte missalignment is fixed

	CollectiveCompileStack = AllocatedStack + BackupSize;
}