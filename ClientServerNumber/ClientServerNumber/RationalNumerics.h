#include "BigInteger.h"

class RationalNumerics
{
public:
	// �����������, ����������� ��������� � �����������.
	RationalNumerics(BigInteger numerator, BigInteger denominator);

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

	// �������� ����� �����.
	BigInteger GetWholePart();

	~RationalNumerics();

private:

	static RationalNumerics _zero;

	static RationalNumerics _one;

	BigInteger _numerator;

	BigInteger _denominator;

	int _sign;

};

