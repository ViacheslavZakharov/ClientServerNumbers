#include "pch.h"
#include "framework.h"
#include "ExponentialNotation.h"

ExponentialNotation::ExponentialNotation()
{
	_sign = 0;
	_exponent = 0;
	_significandWhole = 0;
	_significandNotWhole = 0;
	_currentCountDigitsNotWhole = 0;
	_maxCountDigitsNotWholePart = 0;

	_digitsBeforePeriod = 0;
	_period = 0;
	_countDigitsBeforePeriod = 0;
}

ExponentialNotation::ExponentialNotation(RationalNumerics rationalNumeric, int accuracy)
{
	_sign = rationalNumeric.Sign();
	_exponent = 0;
	_significandWhole = 0;
	_significandNotWhole = 0;
	_currentCountDigitsNotWhole = accuracy;
	_maxCountDigitsNotWholePart = accuracy;

	_digitsBeforePeriod = 0;
	_period = 0;
	_countDigitsBeforePeriod = 0;

	ReformToExponentialNotation(rationalNumeric);
}

ExponentialNotation::ExponentialNotation(int sign, int significandWhole, BigInteger significandNotWhole,
	int exponent, int currentCountDigitsNotWhole, int maxCountDigitsNotWholePart)
{
	_sign = sign;
	_significandWhole = significandWhole;
	_significandNotWhole = significandNotWhole;
	_exponent = exponent;
	_currentCountDigitsNotWhole = currentCountDigitsNotWhole;
	_maxCountDigitsNotWholePart = maxCountDigitsNotWholePart;

	_digitsBeforePeriod = 0;
	_period = 0;
	_countDigitsBeforePeriod = 0;
}

ExponentialNotation::ExponentialNotation(string digitsBeforePeriodWhole, string digitsBeforePeriodNotWhole,
	string period, int accuracy, int sign)
{
	if (period == "")
	{
		throw "Период у числа не задан, невозможно определить экспоненциальную запись числа.";
	}

	if (digitsBeforePeriodWhole == "")
	{
		throw "Некорректно задано число через период, невозможно определить экспоненциальную запись числа.";
	}

	int countDigitsBeforePeriod = digitsBeforePeriodNotWhole.length();
	int significandWhole = 0;
	int countZerroInStartBeforeWhole = ExponentialNotation::GetCountZerrosInStartStr(digitsBeforePeriodNotWhole);
	int exponent = 0;
	// Проверим если число < 1, то надо передвинуть цифры, чтобы целая часть была от 1 до 9 и скорректировать степень и другие составляющие числа.
	bool isWholeZerroNotWholeOnlyZerros = digitsBeforePeriodWhole == "0" && countDigitsBeforePeriod != 0 && countZerroInStartBeforeWhole == countDigitsBeforePeriod;
	bool isWholeZerroNotWholeEmpty = digitsBeforePeriodWhole == "0" && countDigitsBeforePeriod == 0;
	bool isWholeZerroNotWholeNotOnlyZerros = digitsBeforePeriodWhole == "0" && countDigitsBeforePeriod != 0 && countZerroInStartBeforeWhole != countDigitsBeforePeriod;
	if (isWholeZerroNotWholeOnlyZerros)
	{
		exponent = exponent - countZerroInStartBeforeWhole;
	}
	if (isWholeZerroNotWholeEmpty || isWholeZerroNotWholeOnlyZerros)
	{
		countZerroInStartBeforeWhole = ExponentialNotation::GetCountZerrosInStartStr(period);
		exponent = exponent - countZerroInStartBeforeWhole - 1;
		significandWhole = atoi(period.substr(countZerroInStartBeforeWhole, 1).c_str());
		digitsBeforePeriodNotWhole = period.substr(countZerroInStartBeforeWhole + 1, period.length() - countZerroInStartBeforeWhole - 1);
	}
	else if (isWholeZerroNotWholeNotOnlyZerros)
	{
		exponent = exponent - countZerroInStartBeforeWhole - 1;
		significandWhole = atoi(digitsBeforePeriodNotWhole.substr(countZerroInStartBeforeWhole, 1).c_str());
		// Отрежим все лишние нули, т.к. они уже учтены в степени.
		digitsBeforePeriodNotWhole = digitsBeforePeriodNotWhole.substr(countZerroInStartBeforeWhole + 1, digitsBeforePeriodNotWhole.length() - countZerroInStartBeforeWhole - 1);
		
	}
	else if (digitsBeforePeriodWhole != "0")
	{
		significandWhole = atoi(digitsBeforePeriodWhole.substr(0, 1).c_str());
		string extraNotWhole = digitsBeforePeriodWhole.substr(1, digitsBeforePeriodWhole.length() - 1); // Если строка меньше длиной, то вернется пустая строка.
		exponent = extraNotWhole.length();
		digitsBeforePeriodNotWhole = extraNotWhole + digitsBeforePeriodNotWhole;
	}

	SetExponentialNotationFieldsFromPeriod(significandWhole, digitsBeforePeriodNotWhole, period, accuracy, exponent, digitsBeforePeriodNotWhole.length(), sign);
}

void ExponentialNotation::SetExponentialNotationFieldsFromPeriod(int wholePart, string digitsBeforePeriodNotWhole, string period,
	int accuracy, int exponent, int countDigitsBeforePeriod, int sign)
{
	string significandNotWhole = digitsBeforePeriodNotWhole.substr(0, accuracy + exponent);
	// Добавим цифр для нецелой части если неоходимо из периода. Для этого определим сколько необходимо цифр периода.
	int countAdditionalNotWholeDigits = accuracy - significandNotWhole.length() + exponent;
	if (countAdditionalNotWholeDigits != 0)
	{
		// Если длина периодической части меньше, чем необходимо цифр,
		// то сгенерируем на основании периода столько сколько необходимо цифр.
		string additionalDigits = period;
		while (additionalDigits.length() < countAdditionalNotWholeDigits)
		{
			additionalDigits += period;
		}

		significandNotWhole += additionalDigits;
	}

	// Инициализируем все поля.
	_sign = sign;
	_significandWhole = wholePart;
	_significandNotWhole = BigInteger(significandNotWhole);
	int countZerroBeforeNotWhole = GetCountZerrosInStartStr(significandNotWhole);
	if (_significandNotWhole != 0)
	{
		_significandNotWhole.SetZerrosInStart(countZerroBeforeNotWhole);
		_significandNotWhole = BigInteger::CutMathematic(_significandNotWhole, accuracy + exponent);
	}
	_exponent = exponent;
	_currentCountDigitsNotWhole = accuracy;
	_maxCountDigitsNotWholePart = accuracy;
	// Заполняем часть относящуюся к периоду.
	countZerroBeforeNotWhole = GetCountZerrosInStartStr(digitsBeforePeriodNotWhole);
	_digitsBeforePeriod = BigInteger(digitsBeforePeriodNotWhole);
	_period = BigInteger(period);
	if (_digitsBeforePeriod != 0) {
		_digitsBeforePeriod.SetZerrosInStart(countZerroBeforeNotWhole);
	}

	countZerroBeforeNotWhole = GetCountZerrosInStartStr(period);
	_period.SetZerrosInStart(countZerroBeforeNotWhole);
	_countDigitsBeforePeriod = countDigitsBeforePeriod;
}

int ExponentialNotation::Sign()
{
    return _sign;
}

string ExponentialNotation::ToString()
{
	string resultString = "";
	if (_sign == 0)
	{
		return "0";
	}

	resultString = to_string(_significandWhole) + ",";
	resultString += _significandNotWhole.ToString();
	
	if (_exponent != 0)
	{
		resultString += " * " + to_string(FUNDAMENT) + "^" + to_string(_exponent);
	}

	if (_sign == -1)
	{
		resultString = "-" + resultString;
	}
	return resultString;
}

bool ExponentialNotation::DoesExistsPeriodNumber()
{
	return _period != 0;
}

int ExponentialNotation::GetSignificandWholePart()
{
    return _significandWhole;
}

BigInteger ExponentialNotation::GetSignificandNotWholePart()
{
    return _significandNotWhole;
}

int ExponentialNotation::GetExponent()
{
	return _exponent;
}

int ExponentialNotation::GetCurrentCountDigitsNotWhole()
{
	return _currentCountDigitsNotWhole;
}

int ExponentialNotation::GetMaxCountDigitsNotWhole()
{
	return _maxCountDigitsNotWholePart;
}

BigInteger ExponentialNotation::GetDigitsBeforePeriod()
{
	return _digitsBeforePeriod;
}

BigInteger ExponentialNotation::GetPeriod()
{
	return _period;
}

int ExponentialNotation::GetCountDigitsBeforePeriod()
{
	return _countDigitsBeforePeriod;
}

RationalNumerics ExponentialNotation::GetRationalNumberFromPeriod()
{
	if (_period == 0)
	{
		return RationalNumerics();
	}

	string digitsBeforePeriod = "";
	if (_digitsBeforePeriod != 0)
	{
		digitsBeforePeriod = _digitsBeforePeriod.ToString();
	}
	// Если есть один или больше нулей перед периодом, то добавим их.
	else if (_digitsBeforePeriod == 0 && _countDigitsBeforePeriod != 0) 
	{
		digitsBeforePeriod = string(_countDigitsBeforePeriod, '0');
	}

	string numerator = to_string(_significandWhole) + digitsBeforePeriod;
	string period = _period.ToString();
	while (numerator.length() < RationalNumerics::MAX_LENGTH_NUMERATOR + _exponent)
	{
		if (numerator.length() + period.length() > RationalNumerics::MAX_LENGTH_NUMERATOR + _exponent)
		{
			string periodPart = period.substr(0,  period.length() - (RationalNumerics::MAX_LENGTH_NUMERATOR + _exponent - numerator.length()));
			numerator += periodPart;
			break;
		}
		numerator += period;
	}

	string denominator = "1" + string(RationalNumerics::MAX_LENGTH_NUMERATOR - 1, '0');
	numerator = _sign == -1 ? "-" + numerator : numerator;
	return RationalNumerics(numerator, denominator);
}

void ExponentialNotation::ReformToExponentialNotation(RationalNumerics rational)
{
	// Если рациональное число равно 0, то вычисления бессмысленны.
	if (rational == 0)
	{
		_currentCountDigitsNotWhole = 0;
		return;
	}

	BigInteger wholePart = rational.GetWholePart();
	if (wholePart != 0) {
		string wholePartStr = BigInteger::Abs(wholePart).ToString();
		_significandWhole = wholePartStr[0] - '0';
		string withoutWholePart = wholePartStr.substr(1, wholePartStr.length() - 1);
		BigInteger withoutWholePartBI = BigInteger(withoutWholePart);
		RationalNumerics fraction = rational.GetFractionPart();
		if (withoutWholePartBI != 0 || (fraction != 0 && withoutWholePartBI == 0)) {
			int countZerroInStart = GetCountZerrosInStartStr(withoutWholePart);
			_significandNotWhole.SetZerrosInStart(countZerroInStart);
		}
		_exponent += withoutWholePart.length();
	}
	// Если целая часть числа больше нуля, вычислим разницу целой части числа и мантиссы (от 1 до 9) * 10^n.
	BigInteger remainderWholePart = _significandWhole == 0 
		? BigInteger()
		: wholePart - _significandWhole * BigInteger(FUNDAMENT).Pow(_exponent);

	CalculateSignificandNotWhole(rational, remainderWholePart);
	RoundExponentialNotation();
}

ExponentialNotation ExponentialNotation::Abs(const ExponentialNotation& number)
{
	ExponentialNotation result = number;
	if (result._sign < 0)
	{
		result._sign = 1;
	}
	return result;
}

BigInteger ExponentialNotation::GetBigIntegerFromExponential(ExponentialNotation number)
{
	string notWholeSignificandStr = number._significandNotWhole.ToString();
	notWholeSignificandStr = notWholeSignificandStr == "0" ? "" : notWholeSignificandStr;
	string resultString = number._significandWhole != 0 ? to_string(number._significandWhole) : "";
	resultString += notWholeSignificandStr;
	int notWholeLength = notWholeSignificandStr.length();
	if (number._exponent >= notWholeLength)
	{
		resultString += string(number._exponent - notWholeLength + number._maxCountDigitsNotWholePart, '0');
	}
	else
	{
		resultString += string(number._maxCountDigitsNotWholePart - (notWholeLength - number._exponent), '0');
	}

	if (number._sign == -1) {
		resultString = "-" + resultString;
	}

	return BigInteger(resultString);
}

ExponentialNotation ExponentialNotation::operator=(ExponentialNotation number)
{
	this->_significandNotWhole = number._significandNotWhole;
	this->_significandWhole = number._significandWhole;
	this->_exponent = number._exponent;
	this->_sign = number._sign;
	this->_currentCountDigitsNotWhole = number._currentCountDigitsNotWhole;
	this->_maxCountDigitsNotWholePart = number._maxCountDigitsNotWholePart;

	this->_digitsBeforePeriod = number._digitsBeforePeriod;
	this->_period = number._period;
	this->_countDigitsBeforePeriod = number._countDigitsBeforePeriod;
	return *this;
}

// Возвращает переданное число с противоположным знаком (унарный минус).
const ExponentialNotation ExponentialNotation::operator-() const
{
	ExponentialNotation copy(*this);
	copy._sign = (-1) * copy._sign;
	return copy;
}

int ExponentialNotation::GetCountZerrosInStartStr(string str)
{
	int countZerroInStart = 0;
	for (int i = 0; i < str.length(); i++)
	{
		int currentDigit = str[i] - '0';
		if (currentDigit != 0)
		{
			break;
		}
		else
		{
			countZerroInStart++;
		}
	}

	return countZerroInStart;
}

bool ExponentialNotation::IsNeedUIncreaseWholePart(BigInteger notWholePart, int countDigitsAfterComma)
{
	string notWholePartStr = notWholePart.ToString();

	if (countDigitsAfterComma == 0) 
	{
		return notWholePartStr[0] - '0' >= 5;
	}
	BigInteger result = BigInteger::CutMathematic(notWholePart, countDigitsAfterComma);

	return result.ToString().length() > countDigitsAfterComma;
}

void ExponentialNotation::CalculateSignificandNotWhole(RationalNumerics rational, BigInteger remainderWholePart)
{
	RationalNumerics fractionPart = rational.GetFractionPart();
	if (fractionPart == 0 && _significandWhole == 0)
	{
		_currentCountDigitsNotWhole = 0;
		_significandNotWhole = BigInteger();
		return;
	}
	if (fractionPart == 0 && _significandWhole != 0)
	{
		string fullWholePart = rational.GetWholePart().ToString();
		_exponent = fullWholePart.length() - 1;
		_currentCountDigitsNotWhole = 0;
		int countZerroInStart = _significandNotWhole.GetZerroInStart();
		_significandNotWhole = BigInteger(fullWholePart.substr(1, fullWholePart.length() - 1));
		_significandNotWhole.SetZerrosInStart(countZerroInStart);
		return;
	}
	BigInteger numerator = fractionPart.Numerator();
	BigInteger denominator = fractionPart.Denominator();

	if (remainderWholePart != 0)
	{
		numerator += remainderWholePart * denominator;
	}

	int countZerroInStart = 0;
	int temporaryCountDigitsNotWhole = 0;
	int currentCountZerrosInStart = _significandNotWhole.GetZerroInStart();
	// Считаем на одну больше, чтобы затем округлить.
	while (temporaryCountDigitsNotWhole < _currentCountDigitsNotWhole + 1)
	{
		while (numerator < denominator)
		{
			numerator *= FUNDAMENT;
			_significandNotWhole *= FUNDAMENT;
			temporaryCountDigitsNotWhole++;
			// Если целая часть не равна 0, то в первый раз и когда деление дало в результате 0,
			// а остаток от деления сохраняется, то значит после целой части стоит значимый 0.
			if (_significandNotWhole == 0 && _significandWhole != 0 && temporaryCountDigitsNotWhole > 1)
			{
				countZerroInStart++;
			}
			// Если число меньше единицы, то надо уменьшать степень 10 на единицу, если это не первый раз.
			if (_significandNotWhole == 0 && _significandWhole == 0 && temporaryCountDigitsNotWhole > 1)
			{
				_exponent--;
			}
		}

		_significandNotWhole += numerator / denominator;
		numerator %= denominator;

		if (_significandWhole == 0 && (temporaryCountDigitsNotWhole >= _currentCountDigitsNotWhole + 1 || numerator == 0)) 
		{
			string notWholeStr = _significandNotWhole.ToString();
			if (notWholeStr.length() >= 2 || (notWholeStr.length() == 1 && notWholeStr[0] != '0'))
			{
				_significandWhole = atoi(notWholeStr.substr(0, 1).c_str());
				string currentNotWhole = notWholeStr.substr(1, notWholeStr.length() - 1);
				_significandNotWhole = BigInteger(currentNotWhole);
				//_significandNotWhole.SetZerrosInStart(countZerroInStart);
				int countZerroInStartNotWhole = ExponentialNotation::GetCountZerrosInStartStr(currentNotWhole);
				_significandNotWhole.SetZerrosInStart(countZerroInStartNotWhole);
				_exponent--;
			}
		}

		if (numerator == 0)
		{
			break;
		}
	}

	// Если число имеет количество знаков меньше, чем точность, то необходимо уменьшить точность.
	if (temporaryCountDigitsNotWhole < _currentCountDigitsNotWhole)
	{
		_currentCountDigitsNotWhole = temporaryCountDigitsNotWhole;
	}

	_significandNotWhole.SetZerrosInStart(countZerroInStart + currentCountZerrosInStart);
}

void ExponentialNotation::RoundExponentialNotation()
{
	// Проверим не повлияет ли округление на целую часть числа.
	int countDigitsToRound = _currentCountDigitsNotWhole + _exponent;
	bool isNeedIncreaseWholePart = ExponentialNotation::IsNeedUIncreaseWholePart(_significandNotWhole,
		countDigitsToRound);
	// Если целая часть числа меньше 9 и при округлении она должна увеличиться.
	if (isNeedIncreaseWholePart && _significandWhole < FUNDAMENT - 1)
	{
		_significandWhole++;
		_significandNotWhole = BigInteger();
		_currentCountDigitsNotWhole = 0;
		return;
	}

	// Если целая часть равна 9 и при округлении она должна увеличиться.
	if (isNeedIncreaseWholePart && _significandWhole == FUNDAMENT - 1)
	{
		_significandWhole = 1;
		_significandNotWhole = BigInteger();
		_exponent++;
		_currentCountDigitsNotWhole = 0;
		return;
	}
	// Если количество цифр после запятой должно быть равно 0 и целую часть не надо увеличивать, то надо просто вернуть ноль.
	if (countDigitsToRound == 0) 
	{
		_significandNotWhole = BigInteger();
		return;
	}
	// Если округление не влияет на целую часть, то округляем нецелую на необходимое количество знаков.
	_significandNotWhole = BigInteger::CutMathematic(_significandNotWhole, countDigitsToRound);
}

ExponentialNotation ExponentialNotation::GetOperationResultPlusOrMinus(Operation op, ExponentialNotation left, ExponentialNotation right)
{
	int maxCountDigitsNotWhole = std::max(left._maxCountDigitsNotWholePart, right._maxCountDigitsNotWholePart);
	left._maxCountDigitsNotWholePart = maxCountDigitsNotWhole;
	right._maxCountDigitsNotWholePart = maxCountDigitsNotWhole;
	BigInteger leftBigInteger = ExponentialNotation::GetBigIntegerFromExponential(left);
	BigInteger rightBigInteger = ExponentialNotation::GetBigIntegerFromExponential(right);

	BigInteger resultBigInt = BigInteger();

	switch (op)
	{
		case Operation::Plus:
		{
			resultBigInt = leftBigInteger + rightBigInteger;
			break;
		}
		case Operation::Minus:
		{
			resultBigInt = leftBigInteger - rightBigInteger;
			break;
		}
		default:
		{
			string exceptionMessage = "Not correct operation exception";
			throw (exceptionMessage);
			break;
		}
	}

	if (resultBigInt == 0) {
		return ExponentialNotation();
	}

	// Определим результирующую точность как большую из левого и правого.
	int currentCountDigitsNotWhole = std::max(left._currentCountDigitsNotWhole, right._currentCountDigitsNotWhole); //ExponentialNotation::GetMaxCurrentCountDigitsNotWhole(left, right);

	// Определяем знак.
	int sign = resultBigInt.Sign();
	string resultStr = resultBigInt.ToString();
	resultStr = sign < 0 ? resultStr.substr(1, resultStr.length() - 1) : resultStr;

	int wholeSignificand = atoi(resultStr.substr(0, 1).c_str());
	BigInteger notWholeSignificand = BigInteger();
	int resultExponent = 0;
	int maxCountDigitsNotWholePart = std::max(left._maxCountDigitsNotWholePart, right._maxCountDigitsNotWholePart);

	resultExponent = (int)resultStr.length() - 1 - maxCountDigitsNotWholePart;

	notWholeSignificand = BigInteger(resultStr.substr(1, resultStr.length() - 1).c_str());
	if (notWholeSignificand != 0) {
		// Посчитаем количество нулей в начале нецелой части.
		int countZerrosInStart = ExponentialNotation::GetCountZerrosInStartStr(resultStr.substr(1, resultStr.length() - 1));
		notWholeSignificand.SetZerrosInStart(countZerrosInStart);
	}	

	ExponentialNotation result = ExponentialNotation(sign, wholeSignificand, notWholeSignificand, resultExponent,
		currentCountDigitsNotWhole, maxCountDigitsNotWholePart);

	return result;
}

const ExponentialNotation operator*(const ExponentialNotation& left, const ExponentialNotation& right)
{
	ExponentialNotation l = left;
	ExponentialNotation r = right;
	int maxCountDigitsNotWhole = std::max(left._maxCountDigitsNotWholePart, right._maxCountDigitsNotWholePart);
	l._maxCountDigitsNotWholePart = maxCountDigitsNotWhole;
	r._maxCountDigitsNotWholePart = maxCountDigitsNotWhole;
	// Получаем BigInteger из экспоненциального числа, в случае необходимости добьет нулями до максимального количества.
	BigInteger leftBigInteger = ExponentialNotation::GetBigIntegerFromExponential(l);
	BigInteger rightBigInteger = ExponentialNotation::GetBigIntegerFromExponential(r);
	// Получение результата без правильного раставления запятой.
	BigInteger resultBigInt = leftBigInteger * rightBigInteger;

	int sign = resultBigInt.Sign();
	// Считаем десятки.
	string resultString = resultBigInt.ToString();
	resultString = sign < 0 ? resultString.substr(1, resultString.length() - 1) : resultString;

	if (resultString == "0")
	{
		return ExponentialNotation();
	}

	// Определяем количество нецелых цифр как сумма максимального количества,
	// потому что GetBigIntegerFromExponential добивает нулями до максимального.
	int resultNotWholeDigits = l._maxCountDigitsNotWholePart + r._maxCountDigitsNotWholePart;

	// Результирующий показатель степени расчитывается как: 
	// общая длина числа - 1 (для целой части) - длина нецелой части.
	int resultExponent = resultString.length() - 1 - resultNotWholeDigits;

	// Берем первый символ от получившейся строки.
	int wholeSignificand = resultString[0] - '0';
	string notWholeSignificandStr = resultString.substr(1, resultString.length() - 1);
	BigInteger notWholeSignificand = BigInteger(notWholeSignificandStr);
	if (notWholeSignificand != 0) {
		// Посчитаем количество нулей в начале нецелой части.
		int countZerroInStart = ExponentialNotation::GetCountZerrosInStartStr(notWholeSignificandStr);
		notWholeSignificand.SetZerrosInStart(countZerroInStart);
	}

	// Определим результирующую точность как большую из левого и правого.
	int currentCountDigitsNotWhole = std::max(l._maxCountDigitsNotWholePart, r._maxCountDigitsNotWholePart);
	int maxCountDigitsNotWholePart = currentCountDigitsNotWhole;
	ExponentialNotation result = ExponentialNotation(sign, wholeSignificand, notWholeSignificand, resultExponent,
		currentCountDigitsNotWhole, maxCountDigitsNotWholePart);
	result.RoundExponentialNotation();
	return result;
}

const ExponentialNotation operator/(const ExponentialNotation& numerator, const ExponentialNotation& denominator)
{
	// на ноль делить нельзя.
	if (denominator._sign == 0)
	{
		string exceptionMessage = "Divide by zerro exception";
		throw (exceptionMessage);
	}

	// Если числитель ноль - то результат равен 0.
	if (numerator._sign == 0)
	{
		return ExponentialNotation();
	}

	ExponentialNotation n = numerator;
	ExponentialNotation d = denominator;
	int maxCountDigitsNotWhole = std::max(n._maxCountDigitsNotWholePart, d._maxCountDigitsNotWholePart);
	n._maxCountDigitsNotWholePart = maxCountDigitsNotWhole;
	d._maxCountDigitsNotWholePart = maxCountDigitsNotWhole;

	BigInteger numeratorBI = ExponentialNotation::GetBigIntegerFromExponential(numerator);
	string numeratorStr = numeratorBI.ToString();
	BigInteger denominatorBI = ExponentialNotation::GetBigIntegerFromExponential(denominator);
	string denominatorStr = denominatorBI.ToString();
	RationalNumerics rational = RationalNumerics(numeratorBI, denominatorBI);
	int accuracy = std::max(n._currentCountDigitsNotWhole, d._currentCountDigitsNotWhole);
	accuracy = accuracy < ExponentialNotation::COUNT_DIGITS_NOT_WHOLE_DEFAULT 
		? ExponentialNotation::COUNT_DIGITS_NOT_WHOLE_DEFAULT 
		: accuracy;
	ExponentialNotation result = ExponentialNotation(rational, accuracy);
	return result;
}

const ExponentialNotation operator+(const ExponentialNotation& left, const ExponentialNotation& right)
{
	return ExponentialNotation::GetOperationResultPlusOrMinus(Operation::Plus, left, right);
}

const ExponentialNotation operator-(const ExponentialNotation& left, const ExponentialNotation& right)
{
	return ExponentialNotation::GetOperationResultPlusOrMinus(Operation::Minus, left, right);
}
