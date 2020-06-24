#include "ClientNumber.h"

ClientNumber::ClientNumber()
{
}

ClientNumber::ClientNumber(ServerRationalNumber s1, ServerRationalNumber s2, Operation op)
{
	this->_s1 = s1;
	this->_s2 = s2;
	_operation = op;
	_resultOperation = GetResultOperation(s1, s2, op);
}

ServerRationalNumber ClientNumber::GetResultOperation(ServerRationalNumber s1,
	ServerRationalNumber s2, Operation operation)
{
	switch (operation)
	{
	case Plus:
		return s1 + s2;
	case Minus:
		return s1 - s2;
	case Multiplication:
		return s1 * s2;
	case Divide:
		return s1 / s2;
	default:
		break;
	}
}

void ClientNumber::IncreaseAccuracyResult(int numberDigits)
{
	_resultOperation.IncreaseCurrentAccuracy(numberDigits);
}

string ClientNumber::ToString()
{
	return _resultOperation.ToString();
}

ClientNumber::~ClientNumber()
{
}
