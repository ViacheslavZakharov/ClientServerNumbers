#include "RationalNumerics.h"

RationalNumerics::RationalNumerics()
{
	_numerator = BigInteger::Zero();
	_denominator = BigInteger::One();
	_sign = 0;
}

RationalNumerics::RationalNumerics(BigInteger numerator, BigInteger denominator)
{
	if (denominator.Sign() == 0)
	{
		string exceptionMessage = "Divide by zerro exception";
		throw (exceptionMessage);
	}
	else if (numerator.Sign() == 0)
	{
		_sign = 0;
		_numerator = BigInteger::Zero();
		_denominator = denominator;
	}
	else if (numerator.Sign() == denominator.Sign())
	{
		_sign = 1;
		_numerator = BigInteger::Abs(numerator);
		_denominator = BigInteger::Abs(denominator);
	}
	else
	{
		this->_sign = -1;
		this->_numerator = BigInteger::Abs(numerator);
		this->_denominator = BigInteger::Abs(denominator);
	}
	SimplifyFraction();
}

RationalNumerics::RationalNumerics(string numerator, string denominator)
	: RationalNumerics(BigInteger(numerator), BigInteger(denominator))
{
}

RationalNumerics::RationalNumerics(BigInteger numerator)
{
	_numerator = numerator;
	_denominator = BigInteger::One();
	_sign = _numerator.Sign();
}

RationalNumerics::RationalNumerics(int numerator) : RationalNumerics(BigInteger(numerator))
{
}

RationalNumerics::RationalNumerics(string numerator) : RationalNumerics(BigInteger(numerator))
{
}

RationalNumerics RationalNumerics::_zero = RationalNumerics(BigInteger::Zero());

RationalNumerics RationalNumerics::Zero()
{
	return _zero;
}

RationalNumerics RationalNumerics::_one = RationalNumerics(BigInteger::One());

RationalNumerics RationalNumerics::One()
{
	return _one;
}

BigInteger RationalNumerics::Numerator()
{
	return _numerator;
}


BigInteger RationalNumerics::Denominator()
{
	return _denominator;
}

int RationalNumerics::Sign()
{
	return _sign;
}

string RationalNumerics::ToString()
{
	stringstream ss;
	ss << *this;
	return ss.str();
}

BigInteger RationalNumerics::GetWholePart()
{
	BigInteger wholePart = BigInteger::Divide(_numerator, _denominator);
	return wholePart;
}

RationalNumerics RationalNumerics::GetFractionPart()
{
	return RationalNumerics(BigInteger::Remainder(_numerator, _denominator), _denominator);
}

// Сокращает дробь.
void RationalNumerics::SimplifyFraction()
{
	if (_numerator == BigInteger::Zero())
	{
		_denominator = BigInteger::One();
	}

	BigInteger gcd = BigInteger::GreatestCommonDivisor(_numerator, _denominator);
	if (gcd > BigInteger::One())
	{
		_numerator = _numerator / gcd;
		_denominator = _denominator / gcd;
	}
}

const RationalNumerics RationalNumerics::operator+() const
{
	return RationalNumerics(*this);
}

const RationalNumerics RationalNumerics::operator-() const
{
	return RationalNumerics(-this->_numerator, this->_denominator);
}

const RationalNumerics RationalNumerics::operator++()
{
	return *this + RationalNumerics::One();
}

const RationalNumerics RationalNumerics::operator--()
{
	return *this - RationalNumerics::One();
}

//     a/b = c/d, iff ad = bc
bool operator ==(const RationalNumerics& left, const RationalNumerics& right)
{
	return left._sign == right._sign &&
		left._numerator * right._denominator == right._numerator * left._denominator;
}

bool operator<(const RationalNumerics& left, const RationalNumerics& right)
{
	return (left._sign == right._sign &&
		left._numerator * right._denominator < right._numerator * left._denominator) ||
		left._sign < right._sign;
}

bool operator !=(const RationalNumerics& left, const RationalNumerics& right)
{
	return left._sign != right._sign &&
		left._numerator * right._denominator != right._numerator * left._denominator;
}

bool operator>(const RationalNumerics& left, const RationalNumerics& right)
{
	return (left._sign == right._sign &&
		left._numerator * right._denominator > right._numerator * left._denominator) ||
		left._sign > right._sign;
}

bool operator<=(const RationalNumerics& left, const RationalNumerics& right)
{
	return left._numerator * right._denominator <= right._numerator * left._denominator;
}

bool operator>=(const RationalNumerics& left, const RationalNumerics& right)
{
	return left._numerator * right._denominator >= right._numerator * left._denominator;
}

// a/b + c/d  == (ad + bc)/bd
const RationalNumerics operator+(RationalNumerics left, const RationalNumerics& right)
{
	BigInteger leftNumerator = left._numerator * right._denominator;
	BigInteger rightNumerator = left._denominator * right._numerator;

	if (left._sign == -1)
	{
		leftNumerator = -leftNumerator;
	}
	if (right._sign == -1)
	{
		rightNumerator = -rightNumerator;
	}
	
	return RationalNumerics(leftNumerator + rightNumerator, left._denominator * right._denominator);
}

// a/b - c/d  == (ad - bc)/bd
const RationalNumerics operator-(RationalNumerics left, const RationalNumerics& right)
{
	BigInteger leftNumerator = left._numerator * right._denominator;
	BigInteger rightNumerator = left._denominator * right._numerator;

	if (left._sign == -1)
	{
		leftNumerator = -leftNumerator;
	}
	if (right._sign == -1)
	{
		rightNumerator = -rightNumerator;
	}

	return RationalNumerics(leftNumerator - rightNumerator, left._denominator * right._denominator);
}

// a/b * c/d  == (ac)/(bd)
const RationalNumerics operator*(RationalNumerics left, const RationalNumerics& right)
{
	BigInteger numerator = left._numerator * right._numerator;
	numerator = left._sign != right._sign ? -numerator : numerator;
	return RationalNumerics(numerator, (left._denominator * right._denominator));
}

// a/b / c/d  == (ad)/(bc)
const RationalNumerics operator/(RationalNumerics left, const RationalNumerics& right)
{
	BigInteger numerator = left._numerator * right._denominator;
	numerator = left._sign != right._sign ? -numerator : numerator;
	return RationalNumerics(numerator, (left._denominator * right._numerator));
}

// a/b % c/d  == (ad % bc)/bd
const RationalNumerics operator%(RationalNumerics left, const RationalNumerics& right)
{
	BigInteger leftNumerator = left._numerator * right._denominator;
	BigInteger rightNumerator = left._denominator * right._numerator;

	if (left._sign == -1)
	{
		leftNumerator = -leftNumerator;
	}
	if (right._sign == -1)
	{
		rightNumerator = -rightNumerator;
	}
	return RationalNumerics(leftNumerator % rightNumerator, (left._denominator * right._denominator));
}

RationalNumerics RationalNumerics::operator=(RationalNumerics number)
{
	this->_numerator = number._numerator;
	this->_denominator = number._denominator;
	this->_sign = number._sign;
	return *this;
}

ostream& operator<<(ostream& os, const RationalNumerics& rn)
{
	if (rn._numerator == 0)
	{
		os << 0;
	}
	else
	{
		if (rn._sign == -1)
		{
			os << '-';
		}
		if (rn._denominator == 1)
		{
			os << rn._numerator;
		}
		else
		{
			os << rn._numerator << '/' << rn._denominator;
		}
	}
	return os;
}

RationalNumerics::operator string() const
{
	stringstream ss;
	ss << *this;
	return ss.str();
}


RationalNumerics::~RationalNumerics()
{
}
