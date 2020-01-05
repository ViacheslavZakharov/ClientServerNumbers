//#pragma once
//#include "BigInteger.h"
#include "RationalNumerics.h"

class ServerNumber 
{
public:
	ServerNumber();
	ServerNumber(BigInteger numerator, BigInteger denominator, int accuracy);

	friend bool operator ==(const ServerNumber&, const ServerNumber&);
private:
	// Мантисса. (значимая часть числа)
	BigInteger _significand;

	// Показатель.
	int _exponent;
	// Рациональное число.
	RationalNumerics _rational;

	const int ACCURACY_DEFAULT = 16;

	// Преобразовать к эспоненциалной записи.
	void ReformToExponentialNotation(BigInteger numerator, BigInteger denominator, int accuracy);
};
