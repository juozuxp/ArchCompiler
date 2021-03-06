#include "CompileMap.h"
#include "CompilerProduct.h"
#include "../Components/Enviroments/FileEnviromentMap.h"

void CompileMap::ReassesStack()
{
	unsigned long long BackupSize;
	bool ShouldAlign;

	if (AllocatedTempStack < TempStack)
		AllocatedTempStack = TempStack;

	ConstStack = AllocatedStack;
	TempStack = AllocatedTempStack;
	AllocatedStack += AllocatedTempStack;

	AllocatedStack = (AllocatedStack + ((1 << 3) - 1)) & ~((1 << 3) - 1); // Stack alignment, making sure that it's 8 byte alligned

	BackupSize = 0;
	ShouldAlign = true;
	for (unsigned short i = 0; i < 16; i++)
	{
		if (RegisterMask & (1 << i))
			BackupSize += 8;
	}

	if (!((AllocatedStack + BackupSize) & (1 << 3)))
		AllocatedStack += (1 << 3); // Stack alignment, making sure the 16 byte missalignment is fixed

	CollectiveCompileStack = AllocatedStack + BackupSize;
}

CompilerProduct CompileMap::CreateProduct(RefObject<FileEnviromentMap> Enviroment)
{
	return CompilerProduct(Enviroment, CompiledCode, StaticSpace);
}