#include "pch.h"
#include "framework.h"
#include "ServerRationalNumber.h"

ServerRationalNumber::ServerRationalNumber() : ServerRationalNumber(RationalNumerics())
{
}

ServerRationalNumber::ServerRationalNumber(RationalNumerics rationalNumeric,
	int countDigitsNotWhole)
{
	_rational = rationalNumeric;
	_exponentialNotation = ExponentialNotation(rationalNumeric, countDigitsNotWhole);
	_currentCountDigitsNotWhole = _exponentialNotation.GetCurrentCountDigitsNotWhole();
}

ServerRationalNumber::ServerRationalNumber(RationalNumerics rationalNumeric) 
	: ServerRationalNumber(rationalNumeric, COUNT_DIGITS_NOT_WHOLE_DEFAULT)
{
}

ServerRationalNumber::ServerRationalNumber(string numerator, string denominator)
	:ServerRationalNumber(RationalNumerics(numerator, denominator))
{ }

ServerRationalNumber::ServerRationalNumber(string numerator) : 
	ServerRationalNumber(RationalNumerics(numerator))
{ }

ServerRationalNumber::ServerRationalNumber(string digitsBeforePeriodWhole, string digitsBeforePeriodNotWhole, string period)
{
	_exponentialNotation = ExponentialNotation(digitsBeforePeriodWhole, digitsBeforePeriodNotWhole,
		period, COUNT_DIGITS_NOT_WHOLE_DEFAULT);
	_rational = _exponentialNotation.GetRationalNumberFromPeriod();
	_currentCountDigitsNotWhole = _exponentialNotation.GetCurrentCountDigitsNotWhole();
}

ServerRationalNumber::ServerRationalNumber(ExponentialNotation exponentialNumber, RationalNumerics rationalNumber,
	int countDigitsNotWhole)
{
	_exponentialNotation = exponentialNumber;
	_rational = rationalNumber;
	_currentCountDigitsNotWhole = countDigitsNotWhole;
}

string ServerRationalNumber::ToString()
{
	bool doesExistsPeriod = _exponentialNotation.DoesExistsPeriodNumber();
	string resultString = _exponentialNotation.ToString();
	//if (doesExistsPeriod)
	//{
	//	resultString += " или в виде числа с периодом: " + _exponentialNotation.ToString(true);
	//}
	return resultString;
}

RationalNumerics ServerRationalNumber::GetRationalNumber()
{
	return _rational;
}

ExponentialNotation ServerRationalNumber::GetExponentionNumber()
{
	return _exponentialNotation;
}

int ServerRationalNumber::GetCurrentCountDigitsNotWhole()
{
	return _currentCountDigitsNotWhole;
}

int ServerRationalNumber::GetMaxCountDigitsNotWhole()
{
	return _exponentialNotation.GetMaxCountDigitsNotWhole();
}

ServerRationalNumber ServerRationalNumber::operator=(ServerRationalNumber number)
{
	this->_rational = number._rational;
	this->_currentCountDigitsNotWhole = number._currentCountDigitsNotWhole;
	this->_exponentialNotation = number._exponentialNotation;
	return *this;
}

bool operator==(const ServerRationalNumber& left, const ServerRationalNumber& right)
{
	return left._rational == right._rational;
}

bool operator<(const ServerRationalNumber& left, const ServerRationalNumber& right)
{
	return left._rational < right._rational;
}

bool operator!=(const ServerRationalNumber& left, const ServerRationalNumber& right)
{
	return left._rational != right._rational;
}

bool operator<=(const ServerRationalNumber& left, const ServerRationalNumber& right)
{
	return left._rational <= right._rational;
}

bool operator>(const ServerRationalNumber& left, const ServerRationalNumber& right)
{
	return left._rational > right._rational;
}

bool operator>=(const ServerRationalNumber& left, const ServerRationalNumber& right)
{
	return left._rational >= right._rational;
}

const ServerRationalNumber operator+(const ServerRationalNumber& left, const ServerRationalNumber& right)
{
	return ServerRationalNumber::GetOperationResult(Operation::Plus, left, right);
}

const ServerRationalNumber operator-(const ServerRationalNumber& left, const ServerRationalNumber& right)
{
	return ServerRationalNumber::GetOperationResult(Operation::Minus, left, right);
}

const ServerRationalNumber operator*(const ServerRationalNumber& left, const ServerRationalNumber& right)
{
	return ServerRationalNumber::GetOperationResult(Operation::Multiplication, left, right);
}

const ServerRationalNumber operator/(const ServerRationalNumber& left, const ServerRationalNumber& right)
{
	return ServerRationalNumber::GetOperationResult(Operation::Divide, left, right);
}

ostream& operator<<(ostream& os, const ServerRationalNumber& number)
{
	ServerRationalNumber s = number;
	cout << s.ToString();
	return os;
}

ServerRationalNumber::~ServerRationalNumber()
{
}

ServerRationalNumber ServerRationalNumber::GetOperationResult(Operation op, ServerRationalNumber left, ServerRationalNumber right)
{
	ExponentialNotation resultExponential = ExponentialNotation();
	RationalNumerics rationalResult = RationalNumerics();
	
	switch (op)
	{
	case Operation::Plus:
	{
		rationalResult = left._rational + right._rational;
		resultExponential = left._exponentialNotation + right._exponentialNotation;
		break;
	}
	case Operation::Minus:
	{
		rationalResult = left._rational - right._rational;
		resultExponential = left._exponentialNotation - right._exponentialNotation;
		break;
	}
	case Operation::Multiplication:
	{
		rationalResult = left._rational * right._rational;
		resultExponential = left._exponentialNotation * right._exponentialNotation;
		break;
	}
	case Operation::Divide:
	{
		rationalResult = left._rational / right._rational;
		resultExponential = left._exponentialNotation / right._exponentialNotation;
		break;
	}
	default:
		string exceptionMessage = "Not correct operation exception";
		throw (exceptionMessage);
	}

	return ServerRationalNumber(resultExponential, rationalResult, resultExponential.GetCurrentCountDigitsNotWhole());
}
