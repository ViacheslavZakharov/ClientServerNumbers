#include "ClientNumber.h"

ClientNumber::ClientNumber()
{
	this->_s1 = ServerRationalNumber();
	this->_s2 = ServerRationalNumber();
	_operation = Operation::Plus;
	_resultOperation = ServerRationalNumber();
	_accurateExponentialNumber = ExponentialNotation();
}

ClientNumber::ClientNumber(ServerRationalNumber s1, ServerRationalNumber s2, Operation op)
{
	this->_s1 = s1;
	this->_s2 = s2;
	_operation = op;
	_resultOperation = CalculateResultOperation(s1, s2, op);
	CalculateAccurateNumber();
}

ClientNumber::ClientNumber(string firstNumerator, string firstDenominator,
	string secondNumerator, string secondDenominator, Operation operation)
	: ClientNumber(ServerRationalNumber(RationalNumerics(firstNumerator, firstDenominator)),
		ServerRationalNumber(RationalNumerics(secondNumerator, secondDenominator)), operation)
{
}

ClientNumber ClientNumber::operator=(ClientNumber number)
{
	this->_s1 = number._s1;
	this->_s2 = number._s2;
	this->_operation = number._operation;
	this->_resultOperation = number._resultOperation;
	this->_accurateExponentialNumber = number._accurateExponentialNumber;
	return *this;
}

ServerRationalNumber ClientNumber::CalculateResultOperation(ServerRationalNumber s1,
	ServerRationalNumber s2, Operation operation)
{
	switch (operation)
	{
	case Operation::Plus:
		return s1 + s2;
	case Operation::Minus:
		return s1 - s2;
	case Operation::Multiplication:
		return s1 * s2;
	case Operation::Divide:
		return s1 / s2;
	default:
		break;
	}
}

void ClientNumber::IncreaseAccuracyResult(int numberDigits)
{
	//_s1 = ServerRationalNumber(_s1.GetRationalNumber(), _s1.GetCurrentCountDigitsNotWhole() + 1);
	//_s2 = ServerRationalNumber(_s2.GetRationalNumber(), _s2.GetCurrentCountDigitsNotWhole() + 1);
	// TODO: Сделать проверку, если точность уже нельзя увеличить, иначе сейчас будут просто добавляться нолики.
	_s1 = ServerRationalNumber(_s1.GetRationalNumber(), _s1.GetMaxCountDigitsNotWhole() + 1);
	_s2 = ServerRationalNumber(_s2.GetRationalNumber(), _s2.GetMaxCountDigitsNotWhole() + 1);
	_resultOperation = CalculateResultOperation(_s1, _s2, _operation);
}

int ClientNumber::GetAccuracy()
{
	return ExponentialNotation::GetAccuracy(_resultOperation.GetExponentionNumber(), _accurateExponentialNumber);
}

ServerRationalNumber ClientNumber::GetResultOperation()
{
	return _resultOperation;
}

ExponentialNotation ClientNumber::GetAccurateExponentialNumber()
{
	return _accurateExponentialNumber;
}

string ClientNumber::ToString()
{
	return	"\n ->s1:" + _s1.ToString() +
			"\n ->s2:" + _s2.ToString() +
			"\n" + ClientNumber::OperationToString(_operation) +
			"\nРезультат: " + _resultOperation.ToString();
}

ClientNumber::~ClientNumber()
{
}

void ClientNumber::CalculateAccurateNumber()
{
	_accurateExponentialNumber = ExponentialNotation(_resultOperation.GetRationalNumber(), MAX_ACCURACY);
}

ostream& operator<<(ostream& os, const ClientNumber& number)
{
	auto n = number;
	cout << n.ToString();
	return os;
}

string ClientNumber::OperationToString(Operation op)
{
	switch (op)
	{
	case Operation::Plus:   return "+";
	case Operation::Minus:   return "-";
	case Operation::Multiplication:   return "*";
	case Operation::Divide:   return "\\";
	default:      return "[Unknown Operation type]";
	}
}

Operation ClientNumber::CharToOperation(char op)
{
	switch (op)
	{
	case '/':
		return Operation::Divide;
	case '*':
		return Operation::Multiplication;
	case '+':
		return Operation::Plus;
	case '-':
		return Operation::Minus;
	default:
		throw "Invalid symbol in formula";
	}
}
