#pragma once
#include "RationalNumerics.h"
#include "ExponentialNotation.h"

class ServerRationalNumber 
{
public:
	// Количество знаков нецелой части по умолчанию.
	static const int COUNT_DIGITS_NOT_WHOLE_DEFAULT = 3;

	ServerRationalNumber();
	// Конструтор позволяет увеличить или уменьшить точность числа.
	ServerRationalNumber(RationalNumerics rationalNumeric, int countDigitsNotWhole);
	ServerRationalNumber(RationalNumerics rationalNumeric);
	ServerRationalNumber(string numerator, string denominator);
	ServerRationalNumber(string numerator);
	ServerRationalNumber(ExponentialNotation exponentialNumber, RationalNumerics rationalNumber, int countDigitsNotWhole);

	friend bool operator ==(const ServerRationalNumber&, const ServerRationalNumber&);
	friend bool operator <(const ServerRationalNumber&, const ServerRationalNumber&);
	friend bool operator !=(const ServerRationalNumber&, const ServerRationalNumber&);
	friend bool operator <=(const ServerRationalNumber&, const ServerRationalNumber&);
	friend bool operator >(const ServerRationalNumber&, const ServerRationalNumber&);
	friend bool operator >=(const ServerRationalNumber&, const ServerRationalNumber&);
	
	friend const ServerRationalNumber operator +(const ServerRationalNumber&, const ServerRationalNumber&);
	friend const ServerRationalNumber operator -(const ServerRationalNumber&, const ServerRationalNumber&);
	friend const ServerRationalNumber operator *(const ServerRationalNumber&, const ServerRationalNumber&);
	friend const ServerRationalNumber operator /(const ServerRationalNumber&, const ServerRationalNumber&);

	ServerRationalNumber operator=(ServerRationalNumber number);

	// Приведение к строке в виде нормальной экспоненциальной записи (x (от 1 до 9) ,... * 10^n).
	string ToString();

	// Получает рациональное число.
	RationalNumerics GetRationalNumber();

	// Получает число в нормальной экспоненциальной форме.
	ExponentialNotation GetExponentionNumber();

	// Получает текущее количество знаков после запятой.
	int GetCurrentCountDigitsNotWhole();

	int GetMaxCountDigitsNotWhole();

	~ServerRationalNumber();

private:

	// Рациональное число.
	RationalNumerics _rational;

	// Текущее количество знаков после запятой без учета показателя степени (т.е. если число 4,5467 * 10^1 => 4-1=3).
	int _currentCountDigitsNotWhole;

	ExponentialNotation _exponentialNotation;

	// Получает результат бинарной операции.
	static ServerRationalNumber GetOperationResult(Operation op, ServerRationalNumber left, ServerRationalNumber right);

	// Получает текущую точность числа до количества переданных чисел.
	//BigInteger SetCurrentAccuracy(int countDigits);
};