#pragma once
#include "FormulaRecognition.h"
#include "ClientNumber.h"
#include "StackList.h"

class FormulaManager
{
public:
	FormulaManager(){ _realAccuracyResult = 0;}

	string Calculate(string formula)
	{
		formula = FormulaRecognition::ClearBadSymbolsInFormula(formula);
		string formulaPPN = FormulaRecognition::ConvertPPN(formula);
		_clientNumbersTree = FormulaRecognition::Calculate(formulaPPN);
		_realAccuracyResult = CalculateRealAccuracyResult();
		return GetFinalResult();
	}

	// Возвращает результат с заданной точностью с помощью регулирования точности дерева операций.
	string GetIncreasedAccuracyResult(int accuracy) 
	{
		// Устанавливаем для всего дерева заданную точность.
		int tempAccuracy = accuracy;
		while (_realAccuracyResult <= accuracy)
		{
			// Если увеличение точности на 10 знаков не позволило прийти к нужному результату, то считаем,
			// что его уже не достигнуть и выбрасываем исключение.
			if (tempAccuracy > accuracy + 11) {
				throw "Не удалось достигнуть заданной точности";
			}
			SetAccuracyForAllTreeNodes(tempAccuracy);
			_realAccuracyResult = CalculateRealAccuracyResult();
			// Если разница между идеальным и текущим числом равна 0, то значит достигнута максимальная точность.
			if (_realAccuracyResult == 0) {
				return GetFinalResult();
			}
			tempAccuracy++;
		}

		// Если получившаяся точность результата больше, чем заданная,
		// то будем производить последовательное уменьшение точности для дерева начиная с головы.
		if (_realAccuracyResult > accuracy)
		{
			DecreaseAccuracyForTree(accuracy);
		}
		if (_realAccuracyResult < accuracy)
		{
			throw "Не удалось достигнуть заданной точности!";
		}

		return GetFinalResult();
	}

	void PrintTreeResult()
	{
		_clientNumbersTree.Print();
	}

	int GetRealAccuracyResult() 
	{
		return _realAccuracyResult;
	}

	string GetFinalResult()
	{
		ClientNumber topResult = _clientNumbersTree.Top();
		string resultString = topResult.GetResultOperation().ToString();
		return resultString;
	}

private:
	StackList<ClientNumber> _clientNumbersTree;

	int _realAccuracyResult;

	// Устанавливает заданную точность у каждого узла дерева.
	void SetAccuracyForAllTreeNodes(int accuracy)
	{
		// Идем по стеку клиент-серверных чисел от хвоста к голове 
		// и последовательно увеличиваем точность у каждого узла дерева.
		auto node = _clientNumbersTree.GetPTail();
 
		while (node != nullptr)
		{
			ClientNumber currentClientNumber = node->item;
			ServerRationalNumber currentOldOperationResult = currentClientNumber.GetResultOperation();
			currentClientNumber.SetAccuracyResult(accuracy);
			node->item = currentClientNumber;
			// Если это не последний элемент в списке, то заменим результат с увеличенной точностью у связанного элемента.
			if (node->prev != nullptr)
			{
				ReplaceOperationResultForNode(node, currentClientNumber, currentOldOperationResult);
			}

			node = node->prev;
		}
	}

	int CalculateRealAccuracyResult()
	{
		ClientNumber topResult = _clientNumbersTree.Top();
		return topResult.GetRealAccuracyNumber();
	}

	// Уменьшает точность конечного результата выражения с помощью
	// постепенного уменьшения точности, начиная с головы для дерева.
	void DecreaseAccuracyForTree(int accuracy)
	{
		auto node = _clientNumbersTree.GetPTop();
		int tempAccuracy = accuracy;
		while (_realAccuracyResult > accuracy)
		{
			tempAccuracy--;
			while (node != nullptr) 
			{
				NodeStack<ClientNumber>* p = node;
				// Пока не дойдем до головного элемента, пересчитаем все узлы дерева с новой точностью.
				while (p != nullptr)
				{
					ClientNumber currentClientNumber = p->item;
					ServerRationalNumber currentOldOperationResult = currentClientNumber.GetResultOperation();
					currentClientNumber.SetAccuracyResult(tempAccuracy);
					p->item = currentClientNumber;
					// Если это не последний элемент в списке, то заменим результат с уменьшенной точностью у связанного элемента.
					if (p->prev != nullptr)
					{
						ReplaceOperationResultForNode(p, currentClientNumber, currentOldOperationResult);
					}

					p = p->prev;
				}

				_realAccuracyResult = CalculateRealAccuracyResult();
				if (_realAccuracyResult == accuracy)
				{
					return;
				}

				if (_realAccuracyResult < accuracy)// Значит проскачили и посчитать не удасться.
				{
					throw "Не удалось достигнуть заданной точности!";
				}

				node = node->next;
			}
		}

	}

	// Заменяет в дереве старое значение item на значение с обновленной точностью.
	void ReplaceOperationResultForNode(NodeStack<ClientNumber>* node, ClientNumber currentClientNumber,
		ServerRationalNumber currentOldOperationResult)
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
};