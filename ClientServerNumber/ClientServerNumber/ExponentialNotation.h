#pragma once
#include "BigInteger.h"
#include "RationalNumerics.h"
#include "Operation.h"


class ExponentialNotation
{
public:
	ExponentialNotation();
	ExponentialNotation(RationalNumerics rationalNumeric, int accuracy);
	ExponentialNotation(int sign, int significandWhole, BigInteger significandNotWhole,
		int exponent, int accuracy, int maxCountDigitsNotWholePart);

	// Знак.
	int Sign();

	// Приведение к строке в виде нормальной экспоненциальной записи (x (от 0 до 9) ,... * 10^n).
	string ToString();

	// Получает целую часть мантиссы
	int GetSignificandWholePart();

	// Получает нецелую часть мантиссы.
	BigInteger GetSignificandNotWholePart();

	// Получает текущую точность.
	int GetCurrentAccuracy();

	// Преобразовывает к эспоненциалной записи.
	void ReformToExponentialNotation(RationalNumerics rational);

	ExponentialNotation operator=(ExponentialNotation number);
	const ExponentialNotation operator -() const;

	friend const ExponentialNotation operator *(const ExponentialNotation&, const ExponentialNotation&);

	friend const ExponentialNotation operator /(const ExponentialNotation&, const ExponentialNotation&);

	friend const ExponentialNotation operator +(const ExponentialNotation&, const ExponentialNotation&);

	friend const ExponentialNotation operator -(const ExponentialNotation&, const ExponentialNotation&);

private:
	// Основание экспоненциальной записи.
	const int FUNDAMENT = 10;

	int _sign;

	// Мантисса. Целая часть - имеет значения от 0 до 9.
	int _significandWhole;

	// Мантисса. (значимая часть числа) нецелая часть мантиссы.
	BigInteger _significandNotWhole;

	// Показатель.
	int _exponent;

	// Текущая точность числа (количество знаков после запятой без учета показателя степени).
	int _currentAccuracy;

	// Количество знаков после запятой, которое может быть максимально быть. Задается серверным числом.
	int _maxCountDigitsNotWholePart;

	// Получает представления числа в виде BigInteger (можно сказать, что все цифры числа без запятой). 
	static BigInteger GetBigIntegerFromExponential(ExponentialNotation number);

	// Получает максимальную точность среди двух чисел.
	static int GetMaxAccuracy(ExponentialNotation exp1, ExponentialNotation exp2);

	// Подсчитывает количество нулей в начале строки.
	static int GetCountZerrosInStartStr(string str);

	// Получает значение для целой части.
	int CalculateSignificandWhole(BigInteger wholePart);

	// Проверяет необходимость увеличить целую часть при округлении нецелой части.
	static bool IsNeedUIncreaseWholePart(BigInteger notWholePart, int countDigitsAfterComma);

	// Вычисляет значение для нецелой части числа. Также в этом методе устанавливается значение для экспоненты.
	void CalculateSignificandNotWhole(RationalNumerics rational, BigInteger remainderWholePart);

	// Округляет по правилам математики экспоненциальное число.
	void RoundExponentialNotation();

	// Получает результат операция сложения или вычитания.
	static ExponentialNotation GetOperationResultPlusOrMinus(Operation op, ExponentialNotation left, ExponentialNotation right);
};

