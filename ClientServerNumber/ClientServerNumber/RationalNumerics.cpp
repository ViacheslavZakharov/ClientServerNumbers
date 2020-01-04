#include "RationalNumerics.h"

RationalNumerics::RationalNumerics(BigInteger numerator, BigInteger denominator)
{
	_numerator = numerator;
	_denominator = denominator;
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

RationalNumerics::~RationalNumerics()
{
}
