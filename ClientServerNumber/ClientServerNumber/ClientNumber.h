#pragma once
#include "ServerRationalNumber.h"
#include "Operation.h"

class ClientNumber
{
public:
	ClientNumber();
	ClientNumber(ServerRationalNumber s1, ServerRationalNumber s2, Operation operation);
	// Конструктор для удобства задания рациональных чисел.
	ClientNumber(string firstNumerator, string firstDenominator, string secondNumerator, string secondDenominator,
		Operation operation);

	ClientNumber operator=(ClientNumber number);

	// Увеличивает точность результата операции путем увеличения точности Серверных чисел.
	void IncreaseAccuracyResult(int numberDigits);

	// Получает точность числа, как количество знаков до первой значимой цифры 
	// в разнице результата операции и идеального числа.
	int GetAccuracy();

	ServerRationalNumber GetResultOperation();

	// Получает точное число.
	ExponentialNotation GetAccurateExponentialNumber();

	string ToString();
	friend ostream& operator <<(ostream&, const ClientNumber&);
	static string OperationToString(Operation op);
	static Operation CharToOperation(char op);

	~ClientNumber();

private:
	// Макисмальная точность числа.
	const int MAX_ACCURACY = 1000;

	ServerRationalNumber _s1;
	ServerRationalNumber _s2;
	Operation _operation;

	ServerRationalNumber _resultOperation;

	// Точный результат в виде экспоненциального числа.
	ExponentialNotation _accurateExponentialNumber;

	// Вычисляет точное значение операции.
	void CalculateAccurateNumber();

	// Получает результат операции.
	ServerRationalNumber CalculateResultOperation(ServerRationalNumber s1,
		ServerRationalNumber s2, Operation operation);
};
