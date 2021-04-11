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
		return GetTopResult();
	}

	string GetIncreasedAccuracyResult(int accuracy) 
	{
		IncreaseAccuracyResult(accuracy);
		return GetTopResult();
	}

	void PrintTreeResult()
	{
		_clientNumbersTree.Print();
	}

	int GetRealAccuracyResult() 
	{
		ClientNumber topResult = _clientNumbersTree.Top();
		return topResult.GetRealAccuracyNumber();
	}

private:
	StackList<ClientNumber> _clientNumbersTree;

	// Увеличивает точность каждой операции у дерева.
	void IncreaseAccuracyResult(int accuracy)
	{
		// Идем по стеку клиент-серверных чисел от хвоста к голове 
		// и последовательно увеличиваем точность у каждого узла дерева.
		auto node = _clientNumbersTree.GetPTail();
 
		while (node != nullptr)
		{
			ClientNumber currentClientNumber = node->item;
			ServerRationalNumber currentOldOperationResult = currentClientNumber.GetResultOperation();
			currentClientNumber.IncreaseAccuracyResult(accuracy);
			node->item = currentClientNumber;
			// Если это не последний элемент в списке, то заменим результат с увеличенной точностью у связанного элемента.
			if (node->prev != nullptr)
			{
				auto nodePrev = node->prev;
				ClientNumber prevClientNumber = nodePrev->item;
				ServerRationalNumber s1 = prevClientNumber.GetLeftServerNumber();
				ServerRationalNumber s2 = prevClientNumber.GetRightServerNumber();
				ServerRationalNumber increasedNumber = currentClientNumber.GetResultOperation();
				// Поищем старый результат у связанного в стеке клиент-серверных чисел.
				// Если нашли - обновляем.
				if (s1 == currentOldOperationResult) {
					nodePrev->item = ClientNumber(increasedNumber, s2, prevClientNumber.GetOperation());
				}
				else if (s2 == currentOldOperationResult) {
					nodePrev->item = ClientNumber(s1, increasedNumber, prevClientNumber.GetOperation());
				}
				// У предыдущего числа нет такого результата операций, значит он есть выше по стеку.
				// Поищем его и заменим на обновленный.
				else {
					NodeStack<ClientNumber>* p = nodePrev;
					while (p != nullptr)
					{
						ClientNumber item = p->item;
						if (item.GetLeftServerNumber() == currentOldOperationResult) {
							p->item = ClientNumber(increasedNumber, item.GetRightServerNumber(), item.GetOperation());
							break;
						}
						else if (item.GetRightServerNumber() == currentOldOperationResult) {
							p->item = ClientNumber(item.GetLeftServerNumber(), increasedNumber, item.GetOperation());
							break;
						}

						p = p->prev;
					}
				}
			}

			node = node->prev;
		}
	}

	string GetTopResult() 
	{
		ClientNumber topResult = _clientNumbersTree.Top();
		string resultString = topResult.GetResultOperation().ToString();
		return resultString;
	}
};