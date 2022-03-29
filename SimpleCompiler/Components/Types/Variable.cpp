#include "Variable.h"
#include "../../Utilities/SimpleUtilities.h"
#include "../Enviroments/EnviromentMap.h"
#include "Arithmetic.h"
#include "../../GlobalInfo/VariableTypes.h"

Variable::Variable(const char* Expression) : TypeElement()
{
	const VariableType* Variable;
	
	Expression = Ignorables.Skip(Expression);
	Variable = VariableTypes::RetrieveType(Expression);

	VariableSize = Variable->GetSize();
	VariableName = ExtractName(Expression + strlen(Variable->GetName()));
}

unsigned short Variable::GetRegisterMask()
{
	if (!Assigner)
		return 0;

	return Assigner->GetRegisterMask();
}

unsigned long long Variable::Parse(EnviromentMap& Enviroment, const char* Expression)
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