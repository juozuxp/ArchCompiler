#include "SyntaxParser.h"

RefObject<FileEnviromentMap> SyntaxParser::Parse(const char* Expression)
{
	RefObject<FileEnviromentMap> Enviroment = RefObject<FileEnviromentMap>(FileEnviromentMap());

	Enviroment->Parse(Expression, Enviroment.Cast<::Enviroment>());

	return Enviroment;
}