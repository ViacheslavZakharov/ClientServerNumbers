#pragma once
#include "FormulaRecognition.h"
#include "ClientNumber.h"
#include "StackList.h"

class FormulaManager
{
public:
	FormulaManager(){}
	string Calculate(string formula)
	{
		formula = FormulaRecognition::ClearBadSymbolsInFormula(formula);
		string formulaPPN = FormulaRecognition::ConvertPPN(formula);
		_clientNumbersTree = FormulaRecognition::Calculate(formulaPPN);
		ClientNumber topResult = _clientNumbersTree.Top();
		string resultString = topResult.GetResultOperation().ToString();
		return resultString;
	}

	//static string GetIncreasedAccuracyResult(int accuracy);

private:
	StackList<ClientNumber> _clientNumbersTree;
};