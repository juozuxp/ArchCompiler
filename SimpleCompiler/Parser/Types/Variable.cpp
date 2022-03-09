#include "Variable.h"
#include "../../Utilities/SimpleUtilities.h"
#include "../../Components/EnviromentMap.h"
#include "Arithmetic.h"
#include "../../GlobalInfo/VariableTypes.h"

Variable::Variable(const char* Expression) : ParserElement()
{
	const VariableType* Variable = VariableTypes::RetrieveType(Expression);

	VariableSize = Variable->GetSize();
	VariableName = ExtractName(Expression + strlen(Variable->GetName()));
}

void Variable::Parse(EnviromentMap& Enviroment, const char* Expression)
{
	const char* PostDefExpression = strstr(Expression, VariableName);
	if (!Arithmetic::IsArtimetic(Expression))
		return;

	RefObject<Arithmetic> Aritmatic = RefObject<Arithmetic>(Arithmetic());

	Enviroment.AddParsed(Aritmatic.Cast<ParserElement>());

	Aritmatic->Parse(Enviroment, PostDefExpression);
}

List<char> Variable::ExtractName(const char* Expression)
{
	List<char> Name = List<char>(10);

	const char* RunName = Expression;

	for (; *RunName == ' '; RunName++);
	for (; *RunName != ' '; RunName++)
		Name.Add(*RunName);

	Name.Add('\0');

	return Name;
}

bool Variable::IsVariable(const char* Expression)
{
	return VariableTypes::RetrieveType(Expression);
}