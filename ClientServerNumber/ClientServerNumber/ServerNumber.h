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
	// ��������. (�������� ����� �����)
	BigInteger _significand;

	// ����������.
	int _exponent;
	// ������������ �����.
	RationalNumerics _rational;

	const int ACCURACY_DEFAULT = 16;

	// ������������� � �������������� ������.
	void ReformToExponentialNotation(BigInteger numerator, BigInteger denominator, int accuracy);
};
