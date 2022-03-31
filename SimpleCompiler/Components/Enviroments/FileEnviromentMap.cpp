#include "FileEnviromentMap.h"
#include "../../Compiler/CompileMap.h"
#include "../../GlobalInfo/GlobalConstants.h"

FileEnviromentMap::FileEnviromentMap() : Enviroment()
{
	for (unsigned long long i = 0; i < ARRAY_COUNT(GlobalConstants::Constants); i++)
		AddConstantValue(GlobalConstants::Constants[i].GetValue(), GlobalConstants::Constants[i].GetName(), GlobalConstants::Constants[i].GetNameLength());
}

void FileEnviromentMap::AddFunction(RefObject<Function> Function)
{
	Functions.Add(Function);
	AddVariable(Function.Cast<Variable>());
}

void FileEnviromentMap::Compile(CompileMap& Enviroment)
{
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
		if (Function::IsFunctionDefinition(RunDeflate))
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
		else
			break;
	}
}