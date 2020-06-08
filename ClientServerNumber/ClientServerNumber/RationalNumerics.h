#pragma once
#include "BigInteger.h"

class RationalNumerics
{
public:

	RationalNumerics();
	// Конструктор, принимающий числитель и знаменатель.
	RationalNumerics(BigInteger numerator, BigInteger denominator);

	// Конструктор, принимающий числитель и знаменатель в виде строки.
	RationalNumerics(string numerator, string denominator);

	// Конструктор принимающий только целое число, знаменатель = 1.
	RationalNumerics(BigInteger numerator);

	RationalNumerics(int numerator);
	RationalNumerics(string numerator);

	// Ноль.
	static RationalNumerics Zero();

	// Один.
	static RationalNumerics One();

	// Числитель.
	BigInteger Numerator();

	// Знаменатель.
	BigInteger Denominator();

	// Знак.
	int Sign();

	string ToString();

	// Получить целую часть.
	BigInteger GetWholePart();

	// Получить дробную часть.
	RationalNumerics GetFractionPart();

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

	// Сокращает дробь.
	void SimplifyFraction();
};

