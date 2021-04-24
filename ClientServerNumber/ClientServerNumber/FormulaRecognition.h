#pragma once
#include <iostream>
#include <string>
#include "ClientNumber.h"
#include "StackList.h"

class FormulaRecognition
{
public:
	FormulaRecognition();
	static string ClearBadSymbolsInFormula(string formula);
	// Преобразует строку в обратную польскую запись.
	static string ConvertPPN(string formulaString);
	// Вычисляет значение формулы.
	static StackList<ClientNumber> Calculate(string formula);
	~FormulaRecognition();
private:
	static bool IsArithmeticOperator(char c);
	// Определяет является ли символ цифрой.
	static bool IsDigit(char c);
	// Проверяет, что переданный символ является числом или частью периодического числа.
	static bool IsNumberOrNumberPart(char c);
	// Определяет является ли переданный символ разделителем целой и нецелой части ',' или '.'.
	static bool IsSeporatorNotWholePart(char c);
	// Определяет является ли переданный символ разделителем начала периодической части числа.
	static bool IsSeporatorPeriodStart(char c);
	// Определяет является ли переданный символ разделителем конца периодической части числа.
	static bool IsSeporatorPeriodEnd(char c);
	// Определяет приоретет операции.
	static int Prior(char c);
	static string GetNumberOrOperation(string str, int startIndex);
};

