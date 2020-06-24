#include "ServerRationalNumber.h"

ServerRationalNumber::ServerRationalNumber() : ServerRationalNumber(RationalNumerics())
{
}

ServerRationalNumber::ServerRationalNumber(RationalNumerics rationalNumeric)
{
	_rational = rationalNumeric;
	_exponent = 0;
	_significandWholePart = 0;
	_significandNotWholePart = 0;
	ReformToExponentialNotation();
	_currentAccuracy = SetCurrentAccuracy(COUNT_DIGITS_ACCURACY_DEFAULT);
}

ServerRationalNumber::ServerRationalNumber(string numerator, string denominator)
	:ServerRationalNumber(RationalNumerics(numerator, denominator))
{ }

ServerRationalNumber::ServerRationalNumber(string numerator) : 
	ServerRationalNumber(RationalNumerics(numerator))
{ }

void ServerRationalNumber::ReformToExponentialNotation()
{
	// Если рациональное число равно 0, то вычисления бессмысленны.
	if (_rational == 0)
	{
		return;
	}

	BigInteger wholePart = _rational.GetWholePart();
	// Если целая часть числа больше нуля, вычислим разницу целой части числа и мантиссы(от 0 до 9)* 10^n.
	BigInteger reminderWholePart = BigInteger();
	if (wholePart == 0)
	{
		_significandWholePart = 0;
	}
	else
	{
		BigInteger tempSignificandWholePart = wholePart;
		if (tempSignificandWholePart >= FUNDAMENT)
		{
			while (tempSignificandWholePart >= FUNDAMENT)
			{
				tempSignificandWholePart /= FUNDAMENT;
				_exponent++;
			}
		}
		_significandWholePart = atoi(tempSignificandWholePart.ToString().c_str());
		reminderWholePart = wholePart - _significandWholePart * BigInteger(FUNDAMENT).Pow(_exponent);
	}

	RationalNumerics fractionPart = _rational.GetFractionPart();
	// Если дробная часть равна 0, то дальнейшие вычисления бесполезны.
	if (fractionPart == 0)
	{
		return;
	}

	BigInteger numerator = fractionPart.Numerator();
	BigInteger denominator = fractionPart.Denominator();
	if (reminderWholePart != 0)
	{
		numerator += reminderWholePart * denominator;
	}

	int temporaryAccuracy = abs(_exponent);
	while (temporaryAccuracy < MAX_ACCURACY)
	{
		while (numerator < denominator)
		{
			numerator *= FUNDAMENT;
			_significandNotWholePart *= FUNDAMENT;
			temporaryAccuracy++;
			// Если число больше 1, то в первый раз, при умножении числителя на знаменатель
			// И если неравенство numerator < denominator не выполняется,
			// То надо добавить к началу нецелой части нужное количество нулей.
			if (_significandNotWholePart == 0 && _significandWholePart != 0)
			{
				_countZerroInStart++;
			}
			// Если число меньше единицы, то надо уменьшать степень 10 на единицу, если это не первый раз.
			if (_significandNotWholePart == 0 && _significandWholePart == 0 && temporaryAccuracy > 1)
			{
				_exponent--;
			}
		}
		_significandNotWholePart += numerator / denominator;
		numerator %= denominator;
		if (numerator == 0)
		{ break; }
	}
	_countZerroInStart--;
	_significandNotWholePart.SetZerrosInStart(_countZerroInStart);
}

BigInteger ServerRationalNumber::SetCurrentAccuracy(int countDigits)
{
	return 
		BigInteger::CutMathematic(_significandNotWholePart, countDigits);
}

string ServerRationalNumber::ToString()
{
	string resultString = "";
	if (_rational.Sign() == 0)
	{
		resultString = "0";
	}
	if (_rational.Sign() == 1)
	{
		resultString = to_string(_significandWholePart) + ",";
		for (int i = 0; i < _countZerroInStart; i++)
		{
			resultString += "0";
		}
		resultString += _currentAccuracy.ToString();
		if (_exponent != 0)
		{
			resultString += " * " + to_string(FUNDAMENT) + "^" + to_string(_exponent);
		}
	}
	if (_rational.Sign() == -1)
	{
		resultString = "-" + resultString;
	}
	return resultString;
}

void ServerRationalNumber::IncreaseCurrentAccuracy(int numberDigits)
{
	int currentNumberDigits = _currentAccuracy.ToString().size();
	_currentAccuracy = SetCurrentAccuracy(currentNumberDigits + numberDigits);
}

ServerRationalNumber ServerRationalNumber::operator=(ServerRationalNumber number)
{
	this->_significandNotWholePart = number._significandNotWholePart;
	this->_significandWholePart = number._significandWholePart;
	this->_exponent = number._exponent;
	this->_rational = number._rational;
	this->_currentAccuracy = number._currentAccuracy;
	this->_countZerroInStart = number._countZerroInStart;
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
	return left._rational * right._rational;
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
