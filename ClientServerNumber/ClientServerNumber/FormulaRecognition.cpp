#include "FormulaRecognition.h"

FormulaRecognition::FormulaRecognition()
{
}

StackList<ClientNumber> FormulaRecognition::Calculate(string formula)
{
	StackList<ServerRationalNumber> serverRationalNumbersStack;
	StackList<ClientNumber> resultClientNumbersStack;
	BigInteger numerator = BigInteger();
	BigInteger denominator = BigInteger();
	Operation op = Operation::Plus;
	bool isnumeratorCalculate = false;
	bool isDenominatorCalculate = false;
	for (auto i = 0; i < formula.length(); i++)
	{
		if (formula[i] == ' ')
			continue;

		if (FormulaRecognition::IsDigit(formula[i]))
		{
			int startIndexDigit = i;
			while (FormulaRecognition::IsDigit(formula[i]))
			{
				i++;
			}
			BigInteger numberBI = BigInteger(formula.substr(startIndexDigit, i - startIndexDigit));
			ServerRationalNumber serverRationalNumber = ServerRationalNumber(RationalNumerics(numberBI, BigInteger(1)));
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

string FormulaRecognition::ClearBadSymbolsInFormula(string formula)
{
	string strResult = "";
	for (auto i = 0; i < formula.length(); i++)
	{
		char symbol = formula[i];
		if (IsArithmeticOperator(symbol) || IsDigit(symbol))
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

string FormulaRecognition::GetFormulaElement(string str, int startIndex)
{
	string formulaElement = "";
	char symbol = str[startIndex];
	while (FormulaRecognition::IsDigit(symbol) && startIndex < str.length())
	{
		formulaElement += symbol;
		symbol = str[++startIndex];
	}
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
		string formulaElement = FormulaRecognition::GetFormulaElement(formulaString, charIndex);
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
