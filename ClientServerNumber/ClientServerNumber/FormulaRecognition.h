#pragma once
#include <iostream>
#include <string>
#include "ClientNumber.h"
#include "StackList.h"

//using namespace std;

class FormulaRecognition
{
public:
	FormulaRecognition();
	static string ClearBadSymbolsInFormula(string formula);
	// Преобразует строку в обратную польскую запись.
	string ConvertPPN(string formulaString);
	// Вычисляет значение формулы.
	StackList<ClientNumber> Calculate(string formula);
	~FormulaRecognition();
private:
	static bool IsArithmeticOperator(char c);
	// Определяет является ли символ цифрой.
	static bool IsDigit(char c);
	// Определяет приоретет операции.
	static int Prior(char c);
	static string GetFormulaElement(string str, int startIndex);
};

