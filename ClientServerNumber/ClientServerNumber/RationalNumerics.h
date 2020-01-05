#pragma once
#include "BigInteger.h"

class RationalNumerics
{
public:

	RationalNumerics();
	// �����������, ����������� ��������� � �����������.
	RationalNumerics(BigInteger numerator, BigInteger denominator);

	// �����������, ����������� ��������� � ����������� � ���� ������.
	RationalNumerics(string numerator, string denominator);

	// ����������� ����������� ������ ����� �����, ����������� = 1.
	RationalNumerics(BigInteger numerator);

	// ����.
	static RationalNumerics Zero();

	// ����.
	static RationalNumerics One();

	// ���������.
	BigInteger Numerator();

	// �����������.
	BigInteger Denominator();

	// ����.
	int Sign();

	string ToString();

	// �������� ����� �����.
	BigInteger GetWholePart();

	// �������� ������� �����.
	RationalNumerics GetFractionPart();

	// ��������� �����.
	void SimplifyFraction();

	const RationalNumerics operator +() const;
	const RationalNumerics operator -() const;
	const RationalNumerics operator ++();
	//const RationalNumerics operator ++(int);
	const RationalNumerics operator --();
	//const RationalNumerics operator --(int);
	//     a/b = c/d, iff ad = bc
	friend bool operator ==(const RationalNumerics&, const RationalNumerics&);
	friend bool operator <(const RationalNumerics&, const RationalNumerics&);
	friend bool operator !=(const RationalNumerics&, const RationalNumerics&);
	friend bool operator <=(const RationalNumerics&, const RationalNumerics&);
	friend bool operator >(const RationalNumerics&, const RationalNumerics&);
	friend bool operator >=(const RationalNumerics&, const RationalNumerics&);

	friend const RationalNumerics operator +(RationalNumerics, const RationalNumerics&);
	friend const RationalNumerics operator -(RationalNumerics, const RationalNumerics&);
	friend const RationalNumerics operator *(RationalNumerics, const RationalNumerics&);
	friend const RationalNumerics operator /(RationalNumerics, const RationalNumerics&);
	friend const RationalNumerics operator %(RationalNumerics, const RationalNumerics&);

	friend ostream& operator <<(ostream&, const RationalNumerics&);
	operator string() const;

	~RationalNumerics();

private:

	static RationalNumerics _zero;

	static RationalNumerics _one;

	BigInteger _numerator;

	BigInteger _denominator;

	int _sign;
};

