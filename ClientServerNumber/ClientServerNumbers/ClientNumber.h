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

	// Устанавливает точность результата операции на заданное значение,
	// при необходимости увеличивает или уменьшает точность путем изменения точности Серверных чисел.
	void SetAccuracyResult(int numberDigits);

	ServerRationalNumber GetResultOperation();
	ServerRationalNumber GetLeftServerNumber();
	ServerRationalNumber GetRightServerNumber();
	Operation GetOperation();

	// Получает точное число.
	ExponentialNotation GetAccurateExponentialNumber();

	string ToString();
	friend ostream& operator <<(ostream&, const ClientNumber&);
	static string OperationToString(Operation op);
	static Operation CharToOperation(char op);

	// Получает действительную точность числа. Как разницу очень точного и действительного.
	int GetRealAccuracyNumber();

	~ClientNumber();

private:
	ServerRationalNumber _s1;
	ServerRationalNumber _s2;
	Operation _operation;

	ServerRationalNumber _resultOperation;

	// Точный результат в виде экспоненциального числа.
	ExponentialNotation _accurateExponentialNumber;

	// Вычисляет точное значение операции.
	void CalculateAccurateNumber();

	ServerRationalNumber GetServerRationalNumberWithNewAccuracy(ServerRationalNumber srn, int accuracy);

	// Получает результат операции.
	ServerRationalNumber CalculateResultOperation(ServerRationalNumber s1,
		ServerRationalNumber s2, Operation operation);
};
