#include "FileEnviromentMap.h"
#include "../CompileMap.h"

void FileEnviromentMap::AddFunction(RefObject<Function> Function)
{
	Functions.Add(Function);
	AddVariable(Function.Cast<Variable>());
}

void FileEnviromentMap::Compile(CompileMap& Enviroment)
{
	for (RefObject<Function> Function : Functions)
		Function->Compile(Enviroment);
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