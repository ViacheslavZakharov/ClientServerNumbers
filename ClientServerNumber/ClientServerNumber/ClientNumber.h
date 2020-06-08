#pragma once
#include "ServerRationalNumber.h"
#include "Operation.h"

class ClientNumber
{
public:
	ClientNumber();
	ClientNumber(ServerRationalNumber s1, ServerRationalNumber s2, Operation operation);

	// Получает результат операции.
	ServerRationalNumber GetResultOperation(ServerRationalNumber s1,
		ServerRationalNumber s2, Operation operation);

	// Увеличивает точность результата операции путем увеличения точности Серверных чисел.
	void IncreaseAccuracyResult(int numberDigits);

	string ToString();

	~ClientNumber();

private:
	ServerRationalNumber _s1;
	ServerRationalNumber _s2;
	Operation _operation;

	ServerRationalNumber _resultOperation;
};
