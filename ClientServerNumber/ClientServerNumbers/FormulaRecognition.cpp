#include "pch.h"
#include "framework.h"
#include "FormulaRecognition.h"

FormulaRecognition::FormulaRecognition()
{
}

StackList<ClientNumber> FormulaRecognition::Calculate(string formula)
{
	StackList<ServerRationalNumber> serverRationalNumbersStack;
	StackList<ClientNumber> resultClientNumbersStack;
	for (auto i = 0; i < formula.length(); i++)
	{
		if (formula[i] == ' ')
			continue;

		if (FormulaRecognition::IsDigit(formula[i]))
		{
			int startIndexDigit = i;
			string digitsBeforePeriodWhole = "";
			string digitsBeforePeriodNotWhole = "";
			string period = "";
			bool isPeriodNumber = false;
			int indexStartNotWholeDigitsBeforePeriod = 0;
			int indexStartPeriod = 0;
			while (FormulaRecognition::IsDigit(formula[i]) || (i < formula.length() && isPeriodNumber))
			{
				if (i + 1 != formula.length() && IsSeporatorNotWholePart(formula[i + 1])) 
				{
					isPeriodNumber = true;
				}
				else if (IsSeporatorNotWholePart(formula[i]))
				{
					digitsBeforePeriodWhole = formula.substr(startIndexDigit, i - startIndexDigit);
					indexStartNotWholeDigitsBeforePeriod = i + 1;
				}
				else if (IsSeporatorPeriodStart(formula[i]))
				{
					digitsBeforePeriodNotWhole = formula.substr(indexStartNotWholeDigitsBeforePeriod, i - indexStartNotWholeDigitsBeforePeriod);
					indexStartPeriod = i + 1;
				}
				else if (IsSeporatorPeriodEnd(formula[i])) 
				{
					period = formula.substr(indexStartPeriod, i - indexStartPeriod);
					isPeriodNumber = false;
				}

				i++;
			}

			ServerRationalNumber serverRationalNumber = ServerRationalNumber();
			// Если число задано в виде a,b(c).
			if (period != "") {
				serverRationalNumber = ServerRationalNumber(digitsBeforePeriodWhole, digitsBeforePeriodNotWhole, period, 1);
			}
			else {
				string numerator = formula.substr(startIndexDigit, i - startIndexDigit);
				serverRationalNumber = ServerRationalNumber(numerator);
			}
			serverRationalNumbersStack.Push(serverRationalNumber);
			i--;
		}
		else
		{
			char operation = formula[i];
			if (serverRationalNumbersStack.Count() < 2){
				throw "Error invalid formula";
			}
			
			ServerRationalNumber secondNumber = serverRationalNumbersStack.Pop();
			ServerRationalNumber firstNumber = serverRationalNumbersStack.Pop();
			Operation op = ClientNumber::CharToOperation(operation);
			ClientNumber cl = ClientNumber(firstNumber, secondNumber, op);
			resultClientNumbersStack.Push(cl);
			ServerRationalNumber resultOperation = cl.GetResultOperation();
			serverRationalNumbersStack.Push(resultOperation);
		}
	}

	if (serverRationalNumbersStack.Count() != 1)
		throw "Invalid formula";

	return resultClientNumbersStack;
}

FormulaRecognition::~FormulaRecognition()
{
}

bool FormulaRecognition::IsArithmeticOperator(char c)
{
	switch (c)
	{
	case '*': case '/': case '+': case '-': case '(': case ')':
		return true;
	default:
		return false;
	}
}

bool FormulaRecognition::IsDigit(char c)
{
	return (c >= '0'&& c <= '9');
}

bool FormulaRecognition::IsNumberOrNumberPart(char c)
{
	return IsDigit(c) || IsSeporatorNotWholePart(c) || IsSeporatorPeriodStart(c) || IsSeporatorPeriodEnd(c);
}

bool FormulaRecognition::IsSeporatorNotWholePart(char c)
{
	return c == ',' || c == '.';
}

bool FormulaRecognition::IsSeporatorPeriodStart(char c)
{
	return c == '(';
}

bool FormulaRecognition::IsSeporatorPeriodEnd(char c)
{
	return c == ')';
}

string FormulaRecognition::ClearBadSymbolsInFormula(string formula)
{
	string strResult = "";
	for (auto i = 0; i < formula.length(); i++)
	{
		char symbol = formula[i];
		if (IsArithmeticOperator(symbol) || IsNumberOrNumberPart(symbol))
			strResult += symbol;
	}
	return strResult;
}

int FormulaRecognition::Prior(char c)
{
	switch (c) {
	case '(': return 1;
	case '+': case '-': return 2;
	case '*': case '/': return 3;
	default: return 0;
	}
}

string FormulaRecognition::GetNumberOrOperation(string str, int startIndex)
{
	string formulaElement = "";
	char symbol = str[startIndex];
	// Флаги для проверки целостности, если число будет задано в виде a,b(c).
	bool wasSeporatatorNotWhole = false;
	bool wasSeporatorStartPeriod = false;
	bool wasSeporatorEndPeriod = false;
	bool isPeriodNumber = false;
	while ((IsDigit(symbol) || isPeriodNumber) && startIndex < str.length())
	{
		formulaElement += symbol;
		// Проверим является ли следующий символ частью периодического числа a,b(c).
		if (startIndex + 1 < str.length() && IsSeporatorNotWholePart(str[startIndex + 1])) {
			isPeriodNumber = true;
		}
		else if (IsSeporatorNotWholePart(symbol)) {
			wasSeporatatorNotWhole = true;
		}
		else if (IsSeporatorPeriodStart(symbol)) {
			wasSeporatorStartPeriod = true;
		}
		else if (IsSeporatorPeriodEnd(symbol)) {
			wasSeporatorEndPeriod = true;
			isPeriodNumber = false;
		}

		symbol = str[++startIndex];
	}
	// Если все флаги находятся не в одинаковом состоянии, считаем, что синтаксис некорректный
	if (!(!wasSeporatatorNotWhole && !wasSeporatorStartPeriod && !wasSeporatorEndPeriod
		|| wasSeporatatorNotWhole && wasSeporatorStartPeriod && wasSeporatorEndPeriod))
	{
		throw "Формула имеет некорректный формат.";
	}
	// Если это не число, то это должна быть операция.
	if (formulaElement.length() == 0)
	{
		formulaElement += symbol;
	}

	return formulaElement;
}

string FormulaRecognition::ConvertPPN(string formulaString)
{
	if (formulaString.length() == 0)
		throw "Formula is invalid";

	if ((!IsDigit(formulaString[0])) && formulaString[0] != '(')
		throw "Syntax error";

	int charIndex = 0;
	StackList<char> operationStack;
	string resultString = "";
	int openAndCloseBrackets = 0;
	bool wasOperation = false;
	while (charIndex != formulaString.length()) {
		string formulaElement = FormulaRecognition::GetNumberOrOperation(formulaString, charIndex);
		if (formulaElement.length() > 1 || IsDigit(formulaElement[0]))
		{
			resultString += formulaElement + " ";
			wasOperation = false;
			charIndex += formulaElement.length();
			continue;
		}
		else
		{
			char operation = formulaElement[0];
			switch (operation)
			{
			case '(':
				operationStack.Push(operation);
				openAndCloseBrackets++;
				wasOperation = false;
				break;
			case '*': case '/': case '+': case '-':
				if (charIndex == formulaString.length())
					throw "Syntax error";

				if (wasOperation == false)
				{
					wasOperation = true;
					if (operationStack.Count() == 0)
					{
						operationStack.Push(operation);
						break;
					}
					while (!(operationStack.Count() == 0) && FormulaRecognition::Prior(operation) <= FormulaRecognition::Prior(operationStack.Top()))
					{
						resultString += operationStack.Pop();
					}
					if (!(operationStack.Count() == 0) && Prior(operation) > Prior(operationStack.Top()) || (operationStack.Count() == 0))
					{
						operationStack.Push(operation);
					}
					break;
				}
				else throw "Syntax error";

			case ')':
				if (wasOperation == true)
					throw "Syntax error";
				else
				{
					while (!(operationStack.Count() == 0) && (operation = operationStack.Top()) != '(' && openAndCloseBrackets > 0)
					{
						resultString += operation;
						operationStack.Pop();
					}
					if (operationStack.Top() == '(')
						operationStack.Pop();
				}
				openAndCloseBrackets--;
				break;
			default:
			{
				throw "Error: invalid symbol in the string";
			}
			}
		}
		charIndex++;
	}

	while (!(operationStack.Count() == 0))
	{
		resultString += operationStack.Pop();
	}
	if (openAndCloseBrackets > 1)
		throw "Error: wrong number of brackets";

	return resultString;
}
