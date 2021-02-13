#include "ServerRationalNumber.h"

ServerRationalNumber::ServerRationalNumber() : ServerRationalNumber(RationalNumerics())
{
}

ServerRationalNumber::ServerRationalNumber(RationalNumerics rationalNumeric)
{
	_rational = rationalNumeric;
	_exponentialNotation = ExponentialNotation(rationalNumeric, ACCURACY_DEFAULT);
	_currentAccuracy = _exponentialNotation.GetCurrentAccuracy();
}

ServerRationalNumber::ServerRationalNumber(string numerator, string denominator)
	:ServerRationalNumber(RationalNumerics(numerator, denominator))
{ }

ServerRationalNumber::ServerRationalNumber(string numerator) : 
	ServerRationalNumber(RationalNumerics(numerator))
{ }

ServerRationalNumber::ServerRationalNumber(ExponentialNotation exponentialNumber, RationalNumerics rationalNumber,
	int accuracy)
{
	_exponentialNotation = exponentialNumber;
	_rational = rationalNumber;
	_currentAccuracy = accuracy;
}

//ServerRationalNumber::ServerRationalNumber(int significandWholePart, BigInteger significandNotWholePart, int exponent)
//{
//	_significandWholePart = significandWholePart;
//	_significandNotWholePart = significandNotWholePart;
//	_exponent = exponent;
//}

//BigInteger ServerRationalNumber::SetCurrentAccuracy(int countDigits)
//{
//	return BigInteger::CutMathematic(_significandNotWholePart, countDigits);
//}

string ServerRationalNumber::ToString()
{
	return _exponentialNotation.ToString();
}

//void ServerRationalNumber::IncreaseCurrentAccuracy(int numberDigits)
//{
//	int currentNumberDigits = _currentAccuracy.ToString().size();
//	_currentAccuracy = SetCurrentAccuracy(currentNumberDigits + numberDigits);
//}



RationalNumerics ServerRationalNumber::GetRationalNumber()
{
	return _rational;
}

int ServerRationalNumber::GetCurrentAccuracy()
{
	return _currentAccuracy;
}

//BigInteger ServerRationalNumber::GetCurrentAccuracy()
//{
//	return _currentAccuracy;
//}

ServerRationalNumber ServerRationalNumber::operator=(ServerRationalNumber number)
{
	this->_rational = number._rational;
	this->_currentAccuracy = number._currentAccuracy;
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
	return left._rational + right._rational;
}

const ServerRationalNumber operator-(const ServerRationalNumber& left, const ServerRationalNumber& right)
{
	return left._rational - right._rational;
}

const ServerRationalNumber operator*(const ServerRationalNumber& left, const ServerRationalNumber& right)
{
	ExponentialNotation resultExponential = left._exponentialNotation * right._exponentialNotation;
	RationalNumerics rationalResult = left._rational * right._rational;
	return ServerRationalNumber(resultExponential, rationalResult, resultExponential.GetCurrentAccuracy());
}

const ServerRationalNumber operator/(const ServerRationalNumber& left, const ServerRationalNumber& right)
{
	return left._rational / right._rational;
}

const ServerRationalNumber operator%(const ServerRationalNumber& left, const ServerRationalNumber& right)
{
	return left._rational % right._rational;
}

ServerRationalNumber::~ServerRationalNumber()
{
}
