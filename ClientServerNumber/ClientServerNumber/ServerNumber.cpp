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
	// делю числитель на знаменатель, получается результат целочисленного деления
// показатель при этом равен нулю
	_significand = numerator / denominator;
	_exponent = 0;

	if (numerator == 0)
	{
		return;
	}

	if (BigInteger::Abs(_significand).ToString().size() > accuracy)
		// если точность полученного числа больше заданной, лишние разряды отсекаются
	{
		while (BigInteger::Abs(_significand).ToString().size() > accuracy)
		{
			// пока количество значащих цифр больше заданной точности
			_exponent++;
			_significand /= 10; // уменьшать количество знаков на один разряд путём деелния на 10
		}
	}
	else // иначе, точность будет либо равна нулю, либо меньше необходимой
	{
		while (BigInteger::Abs(_significand).ToString().size() < accuracy)
		{
			// пока количество значащих цифр числа будет меньше заданной точности, выполнять цикл
			_exponent--; // уменьшать показатель на единицу
			_significand = (numerator * BigInteger(10).Pow(-_exponent)) / denominator; // таким образом увеличивается результат целочисленного деления num/den на количество разрядов, равное абсолютному значению показателя
		}
	}
}

bool operator==(const ServerNumber& left, const ServerNumber& right)
{
	return left._significand == right._significand && left._exponent == right._exponent;
}
