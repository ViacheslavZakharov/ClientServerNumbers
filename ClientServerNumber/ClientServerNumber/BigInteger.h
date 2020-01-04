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
�����, ����������� ����������� ������ � �������� �������������� ������.

�����, ����������� ������� ������������� ���, �������� � �������� �������
�� 9 ���� � ����� �������� �������.
������ �������� ������ ������� ������ https://habr.com/ru/post/172285/
*/

class BigInteger {

	// ��������� ������� ��������� (1 000 000 000).
	static const int BASE = 1000000000;
	// ���������� ���� � ����� �������� �������.
	static const int COUNT_DIGITS_IN_ONE_ELEMENT = 9;

public:
	// �����-����������, ��������� ��� ������� �� ����
	//class DivideByZeroException : public exception {  };

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

	bool odd() const;
	bool even() const;

	// ���������� � �������.
	const BigInteger pow(BigInteger) const;

	// ��������� ����� �����.
	int Sign();

	string ToString();

	// ���������� ����� 1.
	static BigInteger One();

	// ���������� ����� 0.
	static BigInteger Zero();

	// ���������� -1.
	static BigInteger MinusOne();

	// ����� ��� �����.
	static BigInteger Divide(BigInteger numerator, BigInteger denominator);

	static BigInteger Remainder(BigInteger numerator, BigInteger denominator);
private:
	// ���������� ��������� �����
	vector<int> _digits;

	// ����, ����������� ���� �����.
	 /*-1 ����� ������������� ��������.
	 * 0 ����� �������� ����.
	 * 1 ����� ������������� ��������.
	 */
	int _sign;
	//bool _isNegative;

	// ������� ������� ����, �.�. ���� � ������ �����.
	void RemoveLeadingZeros();
	void _shift_right();

	static BigInteger _one;

	static BigInteger _zero;

	static BigInteger _minusOne;
};

// ������� ������� ����� ������������� ����� �� ��������� 0.
//BigInteger BigInteger :: _one = BigInteger("1");
