#include "ServerNumber.h"

ServerNumber::ServerNumber() : ServerNumber(BigInteger::Zero(), BigInteger::One(), ACCURACY_DEFAULT)
{ }

ServerNumber::ServerNumber(BigInteger numerator, BigInteger denominator, int accuracy)
{
	ReformToExponentialNotation(numerator, denominator, accuracy);
	_rational = RationalNumerics(numerator, denominator);
}

void ServerNumber::ReformToExponentialNotation(BigInteger numerator, BigInteger denominator, int accuracy)
{
	// ���� ��������� �� �����������, ���������� ��������� �������������� �������
// ���������� ��� ���� ����� ����
	_significand = numerator / denominator;
	_exponent = 0;

	if (numerator == 0)
	{
		return;
	}

	if (BigInteger::Abs(_significand).ToString().size() > accuracy)
		// ���� �������� ����������� ����� ������ ��������, ������ ������� ����������
	{
		while (BigInteger::Abs(_significand).ToString().size() > accuracy)
		{
			// ���� ���������� �������� ���� ������ �������� ��������
			_exponent++;
			_significand /= 10; // ��������� ���������� ������ �� ���� ������ ���� ������� �� 10
		}
	}
	else // �����, �������� ����� ���� ����� ����, ���� ������ �����������
	{
		while (BigInteger::Abs(_significand).ToString().size() < accuracy)
		{
			// ���� ���������� �������� ���� ����� ����� ������ �������� ��������, ��������� ����
			_exponent--; // ��������� ���������� �� �������
			_significand = (numerator * BigInteger(10).pow(-_exponent)) / denominator; // ����� ������� ������������� ��������� �������������� ������� num/den �� ���������� ��������, ������ ����������� �������� ����������
		}
	}
}

bool operator==(const ServerNumber& left, const ServerNumber& right)
{
	return left._significand == right._significand && left._exponent == right._exponent;
}
