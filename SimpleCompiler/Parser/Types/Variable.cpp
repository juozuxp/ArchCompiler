#include "Variable.h"
#include "../../Utilities/SimpleUtilities.h"
#include "../../Compiler/Enviroments/EnviromentMap.h"
#include "Arithmetic.h"
#include "../../GlobalInfo/VariableTypes.h"

Variable::Variable(const char* Expression) : ParserElement()
{
	const VariableType* Variable;
	for (; *Expression; Expression++)
	{
		if (!IsIgnorable(*Expression))
			break;
	}

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

void Variable::Parse(EnviromentMap& Enviroment, const char* Expression)
{
	const char* PostDefExpression = strstr(Expression, VariableName);
	if (!Arithmetic::IsArtimetic(Expression))
		return;

	Assigner = RefObject<Arithmetic>(Arithmetic());
	Assigner->Parse(Enviroment, PostDefExpression);
}

List<char> Variable::ExtractName(const char* Expression)
{
	List<char> Name = List<char>(10);

	const char* RunName = Expression;

	for (; !IsNameChar(*RunName); RunName++);
	for (; IsNameChar(*RunName); RunName++)
		Name.Add(*RunName);

	Name.Add('\0');

	return Name;
}

bool Variable::IsVariable(const char* Expression)
{
	return VariableTypes::RetrieveType(Expression);
}