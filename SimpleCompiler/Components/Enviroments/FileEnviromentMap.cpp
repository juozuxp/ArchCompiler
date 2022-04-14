#include "FileEnviromentMap.h"
#include "../../Compiler/CompileMap.h"
#include "../../GlobalInfo/GlobalConstants.h"
#include "../Types/String.h"
#include "../Types/Import.h"

FileEnviromentMap::FileEnviromentMap() : Enviroment(), Strings(HashMap<char, RefObject<String>>(0)), Imports(HashMap<char, List<RefObject<Import>>>(0))
{
	for (unsigned long long i = 0; i < ARRAY_COUNT(GlobalConstants::Constants); i++)
		AddConstantValue(GlobalConstants::Constants[i].GetValue(), GlobalConstants::Constants[i].GetName(), GlobalConstants::Constants[i].GetNameLength());
}

void FileEnviromentMap::AddFunction(RefObject<Function> Function)
{
	Functions.Add(Function);
	AddVariable(Function.Cast<Variable>());
}

void FileEnviromentMap::AddImport(RefObject<Import> Import)
{
	unsigned long long SourceLength;
	unsigned long long SourceIndex;

	SourceLength = strlen(Import->GetSourceName());

	SourceIndex = Imports.GetIndex(Import->GetSourceName(), SourceLength);
	if (SourceIndex == ~0)
	{
		List<RefObject<::Import>> Functions;

		Functions.Add(Import);
		Imports.Add(Import->GetSourceName(), SourceLength, Functions);
	}
	else
		Imports.GetByIndex(SourceIndex).Add(Import);

	AddVariable(Import.Cast<Variable>());
}

void FileEnviromentMap::Compile(CompileMap& Enviroment)
{
	/*for (RefObject<String> String : Strings.GetIterator())
	{
		Enviroment.SwitchToPreCompile();
		String->
	}*/

	Enviroment.SwitchToPreCompile();
	for (const List<RefObject<Import>>& Imports : Imports.GetIterator())
	{
		for (RefObject<Import> Import : Imports)
			Import->PreCompile(Enviroment);
	}

	for (RefObject<String> String : Strings.GetIterator())
		String->PreCompile(Enviroment);

	Enviroment.SwitchToCompile();
	for (const List<RefObject<Import>>& Imports : Imports.GetIterator())
	{
		for (RefObject<Import> Import : Imports)
			Import->Compile(Enviroment);
	}

	for (RefObject<String> String : Strings.GetIterator())
		String->Compile(Enviroment);

	Enviroment.SwitchToPostCompile();
	for (const List<RefObject<Import>>& Imports : Imports.GetIterator())
	{
		for (RefObject<Import> Import : Imports)
			Import->PostCompile(Enviroment);
	}

	for (RefObject<String> String : Strings.GetIterator())
		String->PostCompile(Enviroment);

	for (RefObject<Function> Function : Functions)
	{
		Enviroment.SwitchToPreCompile();
		Function->PreCompile(Enviroment);

		Enviroment.SwitchToCompile();
		Function->Compile(Enviroment);

		Enviroment.SwitchToPostCompile();
		Function->PostCompile(Enviroment);
	}
}

void FileEnviromentMap::Parse(const char* Expression, RefObject<Enviroment> Current)
{
	List<char> Deflate = Deflater.Deflate(Expression);
	for (const char* RunDeflate = Deflate; *RunDeflate;)
	{
		if (Import::IsExpression(RunDeflate))
		{
			AddImport(RefObject<::Import>(::Import(RunDeflate)));

			RunDeflate += GetTermDefintionSize(RunDeflate);
		}
		else if (Function::IsFunctionDefinition(RunDeflate))
		{
			RefObject<EnviromentMap> SubEnviroment;
			RefObject<Function> Function;
			
			unsigned long long SubLength;

			Function = RefObject<::Function>(::Function(RunDeflate));
			SubEnviroment = RefObject<EnviromentMap>(EnviromentMap(Current));

			AddFunction(Function);

			RunDeflate += Function::GetDefinitionLength(RunDeflate);

			Function->BindEnviroment(SubEnviroment);
			SubEnviroment->Parse(ExtractSubEnviroment(RunDeflate, &SubLength), SubEnviroment.Cast<Enviroment>());

			RunDeflate += SubLength;
		}
		else if (Variable::IsVariable(RunDeflate))
		{
			RunDeflate += GetTermDefintionSize(RunDeflate);
		}
		else
			break;
	}
}

bool FileEnviromentMap::IsUnderlying()
{
	return true;
}

RefObject<String> FileEnviromentMap::GetString(const char* String, unsigned long long Length)
{
	if (!Length)
		Length = strlen(String);

	unsigned long long Index;

	Index = Strings.GetIndex(String, Length);
	if (Index == ~0ull)
	{
		RefObject<::String> Result = RefObject<::String>(::String(String, Length));

		Strings.Add(String, Length, Result);

		return Result;
	}

	return Strings.GetByIndex(Index);
}