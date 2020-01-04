#include "BigInteger.h"

class RationalNumerics
{
public:
	// Конструктор, принимающий числитель и знаменатель.
	RationalNumerics(BigInteger numerator, BigInteger denominator);

	// Конструктор принимающий только целое число, знаменатель = 1.
	RationalNumerics(BigInteger numerator);

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

	// Получить целую часть.
	BigInteger GetWholePart();

	~RationalNumerics();

private:

	static RationalNumerics _zero;

	static RationalNumerics _one;

	BigInteger _numerator;

	BigInteger _denominator;

	int _sign;

};

