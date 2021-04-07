//#include "FormulaManager.h"
//
//string FormulaManager::Calculate(string formula)
//{
//    formula = FormulaRecognition::ClearBadSymbolsInFormula(formula);
//    string formulaPPN = FormulaRecognition::ConvertPPN(formula);
//    _clientNumbersTree = FormulaRecognition::Calculate(formulaPPN);
//    ClientNumber topResult = _clientNumbersTree.Top();
//    string resultString = topResult.GetResultOperation().ToString();
//    return resultString;
//}
