#pragma once
#include "RationalNumerics.h"
#include "ExponentialNotation.h"

class ServerRationalNumber 
{
public:
	// Количество знаков для точности по умолчанию.
	const int ACCURACY_DEFAULT = 3;

	ServerRationalNumber();
	ServerRationalNumber(RationalNumerics rationalNumeric);
	ServerRationalNumber(string numerator, string denominator);
	ServerRationalNumber(string numerator);
	ServerRationalNumber(ExponentialNotation exponentialNumber, RationalNumerics rationalNumber, int accuracy);
	//ServerRationalNumber(int significandWholePart, BigInteger significandNotWholePart, int exponent);

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
	friend const ServerRationalNumber operator %(const ServerRationalNumber&, const ServerRationalNumber&);

	ServerRationalNumber operator=(ServerRationalNumber number);

	// Приведение к строке в виде нормальной экспоненциальной записи (x (от 0 до 9) ,... * 10^n).
	string ToString();

	// Увеличивает текущую точность числа на указанное количество знаков.
	//void IncreaseCurrentAccuracy(int numberDigits);

	// Получает целую часть мантиссы
	//int GetSignificandWholePart();

	// Получает нецелую часть мантиссы.
	//BigInteger GetSignificandNotWholePart();

	// Получает показатель степени.
	//int GetExponent();

	// Получает рациональное число.
	RationalNumerics GetRationalNumber();

	// Получает текущую точность.
	int GetCurrentAccuracy();

	//ServerRationalNumber operator=(const ServerRationalNumber& number);
	~ServerRationalNumber();

private:
	// Мантисса. (значимая часть числа) нецелая часть мантиссы.
	//BigInteger _significandNotWholePart;

	// Мантисса. Целая часть - имеет значения от 0 до 9.
	//int _significandWholePart;

	// Показатель.
	//int _exponent;
	
	// Основание экспоненциальной записи.
//	const int FUNDAMENT = 10;

	// Макисмальная точность числа.
	const int MAX_ACCURACY = 16;

	// Рациональное число.
	RationalNumerics _rational;

	// Текущая точность числа (количество знаков после запятой без учета показателя степени).
	int _currentAccuracy;

	// Количество нулей вначале числа
	//int _countZerroInStart = 0;

	ExponentialNotation _exponentialNotation;

	// Преобразовывает к эспоненциалной записи.
//	void ReformToExponentialNotation();

	// Получает текущую точность числа до количества переданных чисел.
	//BigInteger SetCurrentAccuracy(int countDigits);
};