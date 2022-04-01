#include "Variable.h"
#include "../../Utilities/SimpleUtilities.h"
#include "../Enviroments/EnviromentMap.h"
#include "../../GlobalInfo/VariableTypes.h"
#include "Arithmetic.h"

void Variable::CompileCall(class CompileMap& Enviroment)
{
}

void Variable::CompileAssign(class CompileMap& Enviroment, RegisterType Source)
{
}

void Variable::CompileRetrieve(class CompileMap& Enviroment, RegisterType Source)
{
}

void Variable::CompileRefrence(class CompileMap& Enviroment, RegisterType Source)
{
}

unsigned long Variable::GetArithmeticMultiplier(long long Reference)
{
	if (Reference < 0)
		return VariableSize;

	return 1;
}

Variable::Variable(const char* Expression) : TypeElement()
{
	const VariableType* Variable;
	
	Expression = Ignorables.Skip(Expression);
	Variable = VariableTypes::RetrieveType(Expression);

	VariableSize = Variable->GetSize();
	VariableName = ExtractName(Expression + strlen(Variable->GetName()));
}

void Variable::PreCompile(CompileMap& Enviroment)
{
	if (Assigner)
		Assigner->PreCompile(Enviroment);
}

void Variable::PostCompile(CompileMap& Enviroment)
{
	if (Assigner)
		Assigner->PostCompile(Enviroment);
}

unsigned long long Variable::Parse(RefObject<EnviromentMap> Enviroment, const char* Expression)
{
	const char* PostDefExpression = strstr(Expression, VariableName);
	if (!Arithmetic::IsArtimetic(Expression))
		return 0;

	Assigner = RefObject<Arithmetic>(Arithmetic());
	Assigner->Parse(Enviroment, PostDefExpression);

	return 0;
}

List<char> Variable::ExtractName(const char* Expression)
{
	List<char> Name = List<char>(10);

	Expression = NonNameChar.Skip(Expression);
	for (; !NonNameChar.IsSkippable(*Expression); Expression++)
		Name.Add(*Expression);

	Name.Add('\0');

	return Name;
}

bool Variable::IsVariable(const char* Expression)
{
	return VariableTypes::RetrieveType(Expression);
}