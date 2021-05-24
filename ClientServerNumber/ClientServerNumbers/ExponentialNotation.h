#pragma once
#include "BigInteger.h"
#include "RationalNumerics.h"
#include "Operation.h"


class ExponentialNotation
{
public:
	// Макисмальная точность числа.
	static const int MAX_ACCURACY = 1000;

	ExponentialNotation();
	ExponentialNotation(RationalNumerics rationalNumeric, int accuracy);
	ExponentialNotation(int sign, int significandWhole, BigInteger significandNotWhole,
		int exponent, int currentCountDigitsNotWhole, int maxCountDigitsNotWholePart);

	ExponentialNotation(string digitsBeforePeriodWhole, string digitsBeforePeriodNotWhole,
		string period, int accuracy, int sign);
	// Знак.
	int Sign();
	// Приведение к строке в виде нормальной экспоненциальной записи (x (от 0 до 9) ,... * 10^n).
	string ToString();
	// Проверяет существует ли период у числа.
	bool DoesExistsPeriodNumber();
	// Получает целую часть мантиссы
	int GetSignificandWholePart();
	// Получает нецелую часть мантиссы.
	BigInteger GetSignificandNotWholePart();
	// Получает степень.
	int GetExponent();
	// Получает текущую точность.
	int GetCurrentCountDigitsNotWhole();
	// Получает максимальную точность.
	int GetMaxCountDigitsNotWhole();
	// Получает цифры до периода
	BigInteger GetDigitsBeforePeriod();
	BigInteger GetPeriod();
	int GetCountDigitsBeforePeriod();
	// Формирует рациональное число из периода.
	RationalNumerics GetRationalNumberFromPeriod();
	// Преобразовывает к эспоненциалной записи.
	void ReformToExponentialNotation(RationalNumerics rational);
	// Устанавливает значение всех полей класса с помощью периода. Позволяет повышать точность у экспоненциальных чисел заданных периодом.
	void SetExponentialNotationFieldsFromPeriod(int wholePart, string digitsBeforePeriodNotWhole, string period,
		int accuracy, int exponent, int countDigitsBeforePeriod, int sign);

	// Получает модуль числа.
	static ExponentialNotation Abs(const ExponentialNotation& number);

	ExponentialNotation operator=(ExponentialNotation number);
	const ExponentialNotation operator -() const;

	friend const ExponentialNotation operator *(const ExponentialNotation&, const ExponentialNotation&);

	friend const ExponentialNotation operator /(const ExponentialNotation&, const ExponentialNotation&);

	friend const ExponentialNotation operator +(const ExponentialNotation&, const ExponentialNotation&);

	friend const ExponentialNotation operator -(const ExponentialNotation&, const ExponentialNotation&);

private:
	// Основание экспоненциальной записи.
	const int FUNDAMENT = 10;

	// Количество знаков нецелой части по умолчанию.
	static const int COUNT_DIGITS_NOT_WHOLE_DEFAULT = 3;

	int _sign;

	// Мантисса. Целая часть - имеет значения от 0 до 9.
	int _significandWhole;

	// Мантисса. (значимая часть числа) нецелая часть мантиссы.
	BigInteger _significandNotWhole;

	// Показатель.
	int _exponent;

	// Текущее количество знаков после запятой без учета показателя степени (т.е. если число 4,5467 * 10^1 => 4-1=3).
	int _currentCountDigitsNotWhole;

	// Количество знаков после запятой, которое может быть максимально быть. Задается серверным числом.
	int _maxCountDigitsNotWholePart;

	// Числа до периода.
	BigInteger _digitsBeforePeriod;
	// Период числа.
	BigInteger _period;
	// Переменная необходима, чтобы отличать числа типа 5,0(3) от 5,(3).
	int _countDigitsBeforePeriod;

	// Получает представления числа в виде BigInteger (можно сказать, что все цифры числа без запятой). 
	static BigInteger GetBigIntegerFromExponential(ExponentialNotation number);

	// Подсчитывает количество нулей в начале строки.
	static int GetCountZerrosInStartStr(string str);

	// Проверяет необходимость увеличить целую часть при округлении нецелой части.
	static bool IsNeedUIncreaseWholePart(BigInteger notWholePart, int countDigitsAfterComma);

	// Вычисляет значение для нецелой части числа. Также в этом методе устанавливается значение для экспоненты.
	void CalculateSignificandNotWhole(RationalNumerics rational, BigInteger remainderWholePart);

	// Округляет по правилам математики экспоненциальное число.
	void RoundExponentialNotation();

	// Получает результат операция сложения или вычитания.
	static ExponentialNotation GetOperationResultPlusOrMinus(Operation op, ExponentialNotation left, ExponentialNotation right);
};