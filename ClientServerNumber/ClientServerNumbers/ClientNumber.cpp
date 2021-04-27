#include "pch.h"
#include "framework.h"
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

void ClientNumber::SetAccuracyResult(int numberDigits)
{
	_s1 = GetServerRationalNumberWithNewAccuracy(_s1, numberDigits);
	_s2 = GetServerRationalNumberWithNewAccuracy(_s2, numberDigits);
	_resultOperation = CalculateResultOperation(_s1, _s2, _operation);
}

ServerRationalNumber ClientNumber::GetResultOperation()
{
	return _resultOperation;
}

ServerRationalNumber ClientNumber::GetLeftServerNumber()
{
	return _s1;
}

ServerRationalNumber ClientNumber::GetRightServerNumber()
{
	return _s2;
}

Operation ClientNumber::GetOperation()
{
	return _operation;
}

ExponentialNotation ClientNumber::GetAccurateExponentialNumber()
{
	return _accurateExponentialNumber;
}

string ClientNumber::ToString()
{
	return	"\n-------------------------\n ->s1:" + _s1.ToString() +
			"\n ->s2:" + _s2.ToString() +
			"\nОперация:" + ClientNumber::OperationToString(_operation) +
			"\nРезультат: " + _resultOperation.ToString();
}

int ClientNumber::GetRealAccuracyNumber()
{
	ExponentialNotation diff = ExponentialNotation::Abs(
		ExponentialNotation::Abs(_accurateExponentialNumber) - 
		ExponentialNotation::Abs(_resultOperation.GetExponentionNumber()));
		return std::abs(diff.GetExponent());
}

ClientNumber::~ClientNumber()
{
}

void ClientNumber::CalculateAccurateNumber()
{
	_accurateExponentialNumber = ExponentialNotation(_resultOperation.GetRationalNumber(), ExponentialNotation::MAX_ACCURACY);
}

ServerRationalNumber ClientNumber::GetServerRationalNumberWithNewAccuracy(ServerRationalNumber srn, int accuracy)
{
	ExponentialNotation exp1 = srn.GetExponentionNumber();
	if (exp1.DoesExistsPeriodNumber()) {
		RationalNumerics rn = srn.GetRationalNumber();
		int significandWhole = exp1.GetSignificandWholePart();
		string digitsBeforePeriod = exp1.GetDigitsBeforePeriod().ToString();
		string period = exp1.GetPeriod().ToString();
		int countDigitsBeforePeriod = exp1.GetCountDigitsBeforePeriod();
		exp1.SetExponentialNotationFieldsFromPeriod(significandWhole, digitsBeforePeriod, period, accuracy,
			exp1.GetExponent(), countDigitsBeforePeriod, exp1.Sign());
		srn = ServerRationalNumber(exp1, rn, accuracy);
	}
	else {
		srn = ServerRationalNumber(srn.GetRationalNumber(), accuracy);
	}

	return srn;
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
	case Operation::Divide:   return "/";
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
