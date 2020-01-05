#include "RationalNumerics.h"

RationalNumerics::RationalNumerics(BigInteger numerator, BigInteger denominator)
{
	if (denominator.Sign() == 0)
	{
		throw "Divide by zerro exception";
	}
	else if (numerator.Sign() == 0)
	{
		this->_sign = 0;
		_numerator = BigInteger::Zero();
		_denominator = denominator;
	}
	else if(numerator.Sign() == denominator.Sign())
	{
		this->_sign = 1;
		_numerator = BigInteger::Abs(numerator);
		_denominator = BigInteger::Abs(denominator);
	}
	else
	{
		this->_sign = -1;
		_numerator = BigInteger::Abs(numerator);
		_denominator = BigInteger::Abs(denominator);
	}
}

RationalNumerics::RationalNumerics(BigInteger numerator)
{
	_numerator = numerator;
	_denominator = BigInteger::One();
	_sign = _numerator.Sign();
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

BigInteger RationalNumerics::GetWholePart()
{
	return BigInteger::Divide(_numerator, _denominator);
}

// Сокращает дробь.
void RationalNumerics::SimplifyFraction()
{
}

RationalNumerics::~RationalNumerics()
{
}
