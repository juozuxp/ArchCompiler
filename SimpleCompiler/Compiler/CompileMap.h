#pragma once
#include "../Utilities/List.h"
#include "../Utilities/RefObject.h"
#include "../GlobalInfo/RegisterTypes.h"
#include "../GlobalInfo/GlobalCompileInfo.h"

class CompileMap
{
private:
	enum CompileState
	{
		CompileState_PreCompile,
		CompileState_Compile,
		CompileState_PostCompile
	};

public:
	constexpr CompileMap()
	{
	}

public:
	class CompilerProduct CreateProduct(RefObject<class FileEnviromentMap> Enviroment);

public:
	inline void AddCode(unsigned char Code)
	{
		if (State != CompileState_Compile)
			return;

		CompiledCode.Add(Code);
	}

	inline void AddCode(List<unsigned char> Code)
	{
		if (State != CompileState_Compile)
			return;

		CompiledCode.Add(Code);
	}

	inline void AddCode(const unsigned char* Code, unsigned long long Size)
	{
		if (State != CompileState_Compile)
			return;

		CompiledCode.Add(Code, Size);
	}

	inline void PatchCode(unsigned long long Location, unsigned char Code)
	{
		if ((State != CompileState_Compile) && (State != CompileState_PostCompile))
			return;

		CompiledCode[Location] = Code;
	}

	inline void PatchCode(unsigned long long Location, List<unsigned char> Code)
	{
		if ((State != CompileState_Compile) && (State != CompileState_PostCompile))
			return;

		CompiledCode.Set(Location, Code, Code.GetCount());
	}

	inline void PatchCode(unsigned long long Location, const unsigned char* Code, unsigned long long Size)
	{
		if ((State != CompileState_Compile) && (State != CompileState_PostCompile))
			return;

		CompiledCode.Set(Location, Code, Size);
	}

	inline void PatchStaticSpace(unsigned long long Location, const unsigned char* Data, unsigned long long Size)
	{
		if ((State != CompileState_Compile) && (State != CompileState_PostCompile))
			return;

		StaticSpace.Set(Location, Data, Size);
	}

public:
	constexpr unsigned long long AllocStaticSpace(unsigned long long Size)
	{
		Size = (Size + ((1ull << 3) - 1)) & ~((1ull << 3) - 1);
		if (State == CompileState_Compile)
		{
			CurrentStaticSpace += Size;
			return CurrentStaticSpace - Size;
		}

		else if (State == CompileState_PreCompile)
			AllocatedStaticSpace += Size;

		return 0;
	}

	constexpr unsigned long long AllocImportStaticSpace(unsigned long long Size)
	{
		Size = (Size + ((1ull << 3) - 1)) & ~((1ull << 3) - 1);
		if (State == CompileState_Compile)
		{
			CurrentImportSpace += Size;
			return CurrentImportSpace - Size;
		}

		else if (State == CompileState_PreCompile)
			AllocatedImportSpace += Size;

		return 0;
	}

	constexpr unsigned long long AllocConstStack(unsigned long long Size)
	{
		Size = (Size + ((1ull << 3) - 1)) & ~((1ull << 3) - 1);
		if (State == CompileState_Compile)
			return (ConstStack -= Size) + AllocatedTempStack;

		else if (State == CompileState_PreCompile)
			AllocatedStack += Size;

		return 0;
	}

	constexpr unsigned long long AllocTempStack(unsigned long long Size)
	{
		Size = (Size + ((1ull << 3) - 1)) & ~((1ull << 3) - 1);
		if (State == CompileState_Compile)
			return TempStack -= Size;

		else if (State == CompileState_PreCompile)
			TempStack += Size;

		return 0;
	}

	constexpr void ResetTempStack()
	{
		if (State == CompileState_PreCompile)
		{
			if (AllocatedTempStack < TempStack)
				AllocatedTempStack = TempStack;

			TempStack = 0;
		}

		else if (State == CompileState_Compile)
			TempStack = AllocatedTempStack;
	}

	constexpr void AddRegisterMask(RegisterMask Mask)
	{
		if (State != CompileState_PreCompile)
			return;

		if (Mask & (RegisterMask_RAX | RegisterMask_RCX | RegisterMask_RDX | RegisterMask_R8 | RegisterMask_R9))
			return;

		RegisterMask |= Mask;
	}

	constexpr void AddRegisterMask(unsigned short Mask)
	{
		if (State != CompileState_PreCompile)
			return;

		RegisterMask |= (Mask & ~(RegisterMask_RAX | RegisterMask_RCX | RegisterMask_RDX | RegisterMask_R8 | RegisterMask_R9));
	}

	constexpr unsigned long long GetStackSize()
	{
		return AllocatedStack;
	}

	constexpr unsigned long long GetCollectiveStack()
	{
		return CollectiveCompileStack;
	}

	constexpr unsigned short GetRegisterMask()
	{
		return RegisterMask;
	}

	constexpr unsigned long long GetCodeLocation()
	{
		return CompiledCode.GetCount();
	}

	constexpr unsigned long long GetStaticSpaceSize()
	{
		return AllocatedStaticSpace;
	}
	
	constexpr unsigned long long GetStaticSpaceSizeAlligned()
	{
		return (AllocatedStaticSpace + (GlobalCompileInfo::MemoryAlignment - 1)) & ~(GlobalCompileInfo::MemoryAlignment - 1);
	}

	constexpr List<unsigned char>& GetCode()
	{
		return CompiledCode;
	}

	inline void SwitchToCompile()
	{
		State = CompileState_Compile;

		ReassesStack();

		if (AllocatedImportSpace)
		{
			AllocatedStaticSpace += AllocatedImportSpace + 8;
			CurrentStaticSpace = AllocatedImportSpace + 8;
		}

		if (StaticSpace.GetCount() != AllocatedStaticSpace)
			StaticSpace.Expand(AllocatedStaticSpace);

		if (AllocatedImportSpace)
		{
			memset(&StaticSpace[AllocatedImportSpace], 0, 8);
			AllocatedImportSpace = 0;
		}
	}

	constexpr void SwitchToPreCompile()
	{
		TempStack = 0;
		RegisterMask = 0;
		AllocatedStack = 0;
		AllocatedTempStack = 0;

		State = CompileState_PreCompile;
	}

	constexpr void SwitchToPostCompile()
	{
		State = CompileState_PostCompile;
	}

private:
	void ReassesStack();

private:
	List<unsigned char> StaticSpace;
	List<unsigned char> CompiledCode;

	CompileState State = CompileState_PreCompile;

	unsigned short RegisterMask = 0;

	unsigned long long TempStack = 0;
	unsigned long long ConstStack = 0;

	unsigned long long AllocatedStack = 0;
	unsigned long long AllocatedTempStack = 0;

	unsigned long long CollectiveCompileStack = 0;

	unsigned long long CurrentStaticSpace = 0;
	unsigned long long CurrentImportSpace = 0;
	unsigned long long AllocatedStaticSpace = 0;
	unsigned long long AllocatedImportSpace = 0;
};