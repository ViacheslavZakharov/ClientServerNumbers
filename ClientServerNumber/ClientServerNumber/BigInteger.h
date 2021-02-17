#pragma once
#include <vector>
#include <string>
#include <ostream>
#include <iomanip>
#include <sstream>
#include <algorithm>
#include <math.h>


using namespace std;

/*
Класс, реализующий возможность работы с длинными целочисленными типами.

Число, описывающее длинный целочисленный тип, хранится в обратном порядке
по 9 цифр в одном элементе массива.
Полное описание работы методов класса https://habr.com/ru/post/172285/
*/

class BigInteger {

	// Основание системы счисления (1 000 000 000).
	static const int BASE = 1000000000;
	// Количество цифр в одном элементе массива.
	static const int COUNT_DIGITS_IN_ONE_ELEMENT = 9;

public:
	BigInteger();

	BigInteger(string);
	BigInteger(signed char);
	BigInteger(unsigned char);
	BigInteger(signed short);
	BigInteger(unsigned short);
	BigInteger(signed int);
	BigInteger(unsigned int);
	BigInteger(signed long);
	BigInteger(unsigned long);
	BigInteger(signed long long);
	BigInteger(unsigned long long);

	friend ostream& operator <<(ostream&, const BigInteger&);
	operator string() const;
	const BigInteger operator +() const;
	const BigInteger operator -() const;
	const BigInteger operator ++();
	const BigInteger operator ++(int);
	const BigInteger operator --();
	const BigInteger operator --(int);
	friend bool operator ==(const BigInteger&, const BigInteger&);
	friend bool operator <(const BigInteger&, const BigInteger&);
	friend bool operator !=(const BigInteger&, const BigInteger&);
	friend bool operator <=(const BigInteger&, const BigInteger&);
	friend bool operator >(const BigInteger&, const BigInteger&);
	friend bool operator >=(const BigInteger&, const BigInteger&);
	friend const BigInteger operator +(BigInteger, const BigInteger&);
	BigInteger& operator +=(const BigInteger&);
	friend const BigInteger operator -(BigInteger, const BigInteger&);
	BigInteger& operator -=(const BigInteger&);
	friend const BigInteger operator *(const BigInteger&, const BigInteger&);
	BigInteger& operator *=(const BigInteger&);
	friend const BigInteger operator /(const BigInteger&, const BigInteger&);
	BigInteger& operator /=(const BigInteger&);
	friend const BigInteger operator %(const BigInteger&, const BigInteger&);
	BigInteger& operator %=(const BigInteger&);

	bool Odd() const;
	bool Even() const;

	// Возведение в степень.
	const BigInteger Pow(BigInteger) const;

	// Получение знака числа.
	int Sign();

	string ToString();

	// Добавляет к началу числа заданное количество нулей.
	void SetZerrosInStart(int countZerro);

	// Получает количество нулей в начале числа.
	int GetZerroInStart();

	// Возвращает число 1.
	static BigInteger One();

	// Возвращает число 0.
	static BigInteger Zero();

	// Возвращает -1.
	static BigInteger MinusOne();

	// Делит два числа.
	static BigInteger Divide(BigInteger numerator, BigInteger denominator);

	// Получает остаток от деления.
	static BigInteger Remainder(BigInteger numerator, BigInteger denominator);

	// Получает модуль числа.
	static BigInteger Abs(const BigInteger& number);

	// Получает наибольший общий делитель.
	static BigInteger GreatestCommonDivisor(BigInteger numerator, BigInteger denominator);

	// Обрезает число по математическим правилам округления до переданного количества цифр.
	static BigInteger CutMathematic(BigInteger number, int countDigits);

	// Получает действительное количество символов с нулями.
	static int GetCountDigits(BigInteger number);
private:
	// внутреннее хранилище числа
	vector<int> _digits;

	// Флаг, описывающий знак числа.
	 /*-1 имеет отрицательное значение.
	 * 0 имеет значение нуль.
	 * 1 имеет положительное значение.
	 */
	int _sign;
	
	// Количество нулей вначале числа
	int _countZerroInStart;

	// Удаляет ведущие нули, т.е. нули в начале числа.
	void RemoveLeadingZeros();
	void _shiftRight();

	static BigInteger _one;

	static BigInteger _zero;

	static BigInteger _minusOne;
};
