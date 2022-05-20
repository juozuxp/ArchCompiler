#include "Variable.h"
#include "../../Utilities/SimpleUtilities.h"
#include "../Enviroments/EnviromentMap.h"
#include "../../GlobalInfo/VariableTypes.h"
#include "Arithmetic.h"
#include "../Transferable/TransferVariable.h"

void Variable::CompileCall(class CompileMap& Enviroment)
{
}

void Variable::CompileAssign(class CompileMap& Enviroment, RegisterType Source, long long Dimension)
{
}

void Variable::CompileRetrieve(class CompileMap& Enviroment, RegisterType Source)
{
}

void Variable::CompileRefrence(class CompileMap& Enviroment, RegisterType Source)
{
}

unsigned long Variable::GetReferenceMultiplier(long long Reference)
{
	if (Reference < 0)
		return (VariableReference + (VariabelDimension != 1)) ? 8 : VariableSize;

	if (((long long)(VariableReference + (VariabelDimension != 1))) - Reference == 1)
		return VariableSize;

	if (((long long)(VariableReference + (VariabelDimension != 1))) - Reference > 1)
		return 8;

	return 0;
}

Variable::Variable(const char* Expression) : TypeElement()
{
	const VariableType* Variable;
	
	Expression = Ignorables.Skip(Expression);
	Variable = VariableTypes::RetrieveType(Expression);

	Expression += strlen(Variable->GetName());

	VariableSize = Variable->GetSize();
	VariableSigniage = Variable->GetSigend();

	VariableName = ExtractName(Expression);
	VariabelDimension = GetDimensions(Expression);
	VariableReference = CountReferences(Expression);
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
	Expression = NonNameChar.Skip(Expression);
	Expression = NonNameChar.InverseSkip(Expression);
	Expression = NonNameChar.Skip(Expression);

	if (!Arithmetic::IsArtimetic(Expression))
		return 0;

	for (; *Expression; Expression++)
	{
		if (*Expression == '=')
			break;
	}

	Assigner = RefObject<Arithmetic>(Arithmetic());
	Assigner->Parse(Enviroment, Expression + 1, RefObject<TransferVariable>(TransferVariable(Enviroment->GetVariable(VariableName, VariableName.GetCount() - 1))).Cast<Transferable>(), VariableSigniage);

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

unsigned long long Variable::CountReferences(const char* Expression)
{
	unsigned long long References;

	Expression = Ignorables.Skip(Expression);
	for (References = 0; NonNameChar.IsSkippable(*Expression); Expression++)
	{
		if (*Expression == '*')
			References++;
	}

	return References;
}

unsigned long long Variable::GetDimensions(const char* Expression)
{
	Expression = NonNameChar.Skip(Expression);
	Expression = NonNameChar.InverseSkip(Expression);
	Expression = Ignorables.Skip(Expression);

	if (*Expression == '[')
	{
		Expression = NonNameChar.Skip(Expression);
		if (IS_NUMBER(Expression))
			return strtoull(Expression, 0, 10);
	}

	return 1;
}

bool Variable::IsVariable(const char* Expression)
{
	return VariableTypes::RetrieveType(Expression);
}