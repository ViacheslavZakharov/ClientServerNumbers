#include "ExponentialNotation.h"

ExponentialNotation::ExponentialNotation()
{
	_sign = 0;
	_exponent = 0;
	_significandWhole = 0;
	_significandNotWhole = 0;
	_currentAccuracy = 0;
}

ExponentialNotation::ExponentialNotation(RationalNumerics rationalNumeric, int accuracy)
{
	_sign = rationalNumeric.Sign();
	_exponent = 0;
	_significandWhole = 0;
	_significandNotWhole = 0;
	_currentAccuracy = accuracy;
	_maxCountDigitsNotWholePart = accuracy;
	ReformToExponentialNotation(rationalNumeric);
}

ExponentialNotation::ExponentialNotation(int sign, int significandWhole, BigInteger significandNotWhole,
	int exponent, int accuracy, int maxCountDigitsNotWholePart)
{
	_sign = sign;
	_significandWhole = significandWhole;
	_significandNotWhole = significandNotWhole;
	_exponent = exponent;
	_currentAccuracy = accuracy;
	_maxCountDigitsNotWholePart = maxCountDigitsNotWholePart;
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
		resultString = "0";
	}
	if (_sign == 1)
	{
		resultString = to_string(_significandWhole) + ",";
		resultString += _significandNotWhole.ToString();
		if (_exponent != 0)
		{
			resultString += " * " + to_string(FUNDAMENT) + "^" + to_string(_exponent);
		}
	}
	if (_sign == -1)
	{
		resultString = "-" + resultString;
	}
	return resultString;
}

int ExponentialNotation::GetSignificandWholePart()
{
    return _significandWhole;
}

BigInteger ExponentialNotation::GetSignificandNotWholePart()
{
    return _significandNotWhole;
}

int ExponentialNotation::GetCurrentAccuracy()
{
	return _currentAccuracy;
}

void ExponentialNotation::ReformToExponentialNotation(RationalNumerics rational)
{
	// Если рациональное число равно 0, то вычислени¤ бессмысленны.
	if (rational == 0)
	{
		_currentAccuracy = 0;
		return;
	}

	BigInteger wholePart = rational.GetWholePart();
	// Если целая часть числа больше нуля, вычислим разницу целой части числа и мантиссы (от 1 до 9) * 10^n.
	_significandWhole = CalculateSignificandWhole(wholePart);
	BigInteger remainderWholePart = _significandWhole == 0 
		? BigInteger()
		: wholePart - _significandWhole * BigInteger(FUNDAMENT).Pow(_exponent);

	_significandNotWhole = CalculateSignificandNotWhole(rational, remainderWholePart, _significandWhole);
	RoundExponentialNotation();
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

	return BigInteger(resultString);
}

int ExponentialNotation::GetMaxAccuracy(ExponentialNotation exp1, ExponentialNotation exp2)
{
	return exp1._currentAccuracy >= exp2._currentAccuracy
		? exp1._currentAccuracy
		: exp2._currentAccuracy;
}

ExponentialNotation ExponentialNotation::operator=(ExponentialNotation number)
{
	this->_significandNotWhole = number._significandNotWhole;
	this->_significandWhole = number._significandWhole;
	this->_exponent = number._exponent;
	this->_sign = number._sign;
	this->_currentAccuracy = number._currentAccuracy;
	this->_maxCountDigitsNotWholePart = number._maxCountDigitsNotWholePart;
	return *this;
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

int ExponentialNotation::CalculateSignificandWhole(BigInteger wholePart)
{
	int significandWhole = 0;
	// Если целая часть числа больше нуля, вычислим разницу целой части числа и мантиссы(от 1 до 9)* 10^n.
	if (wholePart != 0)
	{
		BigInteger tempSignificandWholePart = wholePart;
		if (tempSignificandWholePart >= FUNDAMENT)
		{
			while (tempSignificandWholePart >= FUNDAMENT)
			{
				tempSignificandWholePart /= FUNDAMENT;
				_exponent++;
			}
		}
		significandWhole = atoi(tempSignificandWholePart.ToString().c_str());
	}

	return significandWhole;
}

bool ExponentialNotation::IsNeedUIncreaseWholePart(BigInteger notWholePart, int countDigitsAfterComma)
{
	string notWholePartStr = notWholePart.ToString();
	// Когда длина нецелой части равна 1. Т.е. всего одна цифра. И округлить надо до целого
	if (countDigitsAfterComma == 0 /*&& notWholePartStr.length()  == 1*/) 
	{
		return notWholePartStr[0] - '0' >= 5;
	}
	BigInteger result = BigInteger::CutMathematic(notWholePart, countDigitsAfterComma);

	return result.ToString().length() > countDigitsAfterComma;
}

BigInteger ExponentialNotation::CalculateSignificandNotWhole(RationalNumerics rational,
	BigInteger remainderWholePart, int significandWhole)
{
	RationalNumerics fractionPart = rational.GetFractionPart();
	if (fractionPart == 0 && significandWhole == 0)
	{
		_currentAccuracy = 0;
		return BigInteger("0");
	}
	if (fractionPart == 0 && significandWhole != 0)
	{
		string fullWholePart = rational.GetWholePart().ToString();
		_exponent = fullWholePart.length() - 1;
		_currentAccuracy = 0;
		return BigInteger(fullWholePart.substr(1, fullWholePart.length() - 1));
	}
	BigInteger numerator = fractionPart.Numerator();
	BigInteger denominator = fractionPart.Denominator();
	BigInteger significandNotWhole = BigInteger();
	if (remainderWholePart != 0)
	{
		numerator += remainderWholePart * denominator;
	}

	int countZerroInStart = 0;
	int temporaryAccuracy = 0;
	// Считаем на одну больше, чтобы затем округлить.
	while (temporaryAccuracy < _currentAccuracy + 1)
	{
		while (numerator < denominator)
		{
			numerator *= FUNDAMENT;
			significandNotWhole *= FUNDAMENT;
			temporaryAccuracy++;
			// Если целая часть не равна 0, то в первый раз и когда деление дало в результате 0,
			// а остаток от деления сохраняется, то значит после целой части стоит значимый 0.
			if (significandNotWhole == 0 && _significandWhole != 0)
			{
				countZerroInStart++;
			}
			// Если число меньше единицы, то надо уменьшать степень 10 на единицу, если это не первый раз.
			if (significandNotWhole == 0 && _significandWhole == 0 && temporaryAccuracy > 1)
			{
				_exponent--;
			}
		}
		significandNotWhole += numerator / denominator;
		numerator %= denominator;

		// Если целая часть мантиссы равна 0, то надо взять первую цифру нецелой части для ее определения
		// и уменьшить степень.
		if (significandWhole == 0 && (temporaryAccuracy >= _currentAccuracy + 1 || numerator == 0)) 
		{
			string notWholeStr = significandNotWhole.ToString();
			if(notWholeStr.length() >= 2 || (notWholeStr.length() == 1 && notWholeStr[0] != '0'))
			{
				_significandWhole = atoi(notWholeStr.substr(0, 1).c_str());
				string currentNotWhole = notWholeStr.substr(1, notWholeStr.length() - 1);
				significandNotWhole = BigInteger(currentNotWhole);
				int countZerroInStart = ExponentialNotation::GetCountZerrosInStartStr(currentNotWhole);
				significandNotWhole.SetZerrosInStart(countZerroInStart);
				_exponent--;
			}
		}

		if (numerator == 0)
		{
			break;
		}
	}

	// Если число имеет количество знаков меньше, чем точность, то необходимо уменьшить точность.
	if (temporaryAccuracy < _currentAccuracy)
	{
		_currentAccuracy = temporaryAccuracy;
	}
	if (countZerroInStart > 0)
	{
		countZerroInStart--;
	}

	significandNotWhole.SetZerrosInStart(countZerroInStart);

	return significandNotWhole;
}

void ExponentialNotation::RoundExponentialNotation()
{
	// Проверим не повлияет ли округление на целую часть числа.
	int countDigitsToRound = _currentAccuracy + _exponent;
	bool isNeedIncreaseWholePart = ExponentialNotation::IsNeedUIncreaseWholePart(_significandNotWhole,
		countDigitsToRound);
	// Если целая часть числа меньше 9 и при округлении она должна увеличиться.
	if (isNeedIncreaseWholePart && _significandWhole < FUNDAMENT - 1)
	{
		_significandWhole++;
		_significandNotWhole = BigInteger();
		_currentAccuracy = 0;
		return;
	}

	// Если целая часть равна 9 и при округлении она должна увеличиться.
	if (isNeedIncreaseWholePart && _significandWhole == FUNDAMENT - 1)
	{
		_significandWhole = 1;
		_significandNotWhole = BigInteger();
		_exponent++;
		_currentAccuracy = 0;
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

const ExponentialNotation operator*(const ExponentialNotation& left, const ExponentialNotation& right)
{
	// Получаем BigInteger из экспоненциального числа, в случае необходимости добьет нулями до максимального количества.
	BigInteger leftBigInteger = ExponentialNotation::GetBigIntegerFromExponential(left);
	BigInteger rightBigInteger = ExponentialNotation::GetBigIntegerFromExponential(right);
	// Получение результата без правильного раставления запятой.
	BigInteger resultBigInt = leftBigInteger * rightBigInteger;
	// Считаем десятки.
	string resultString = resultBigInt.ToString();

	if (resultString.length() <= 1)
	{
		return ExponentialNotation();
	}

	// Определяем количество нецелых цифр как сумма максимального количества,
	// потому что GetBigIntegerFromExponential добивает нулями до максимального.
	int resultNotWholeDigits = left._maxCountDigitsNotWholePart + right._maxCountDigitsNotWholePart;

	// Результирующий показатель степени расчитывается как: 
	// общая длина числа - 1 (для целой части) - длина нецелой части.
	int resultExponent = resultString.length() - 1 - resultNotWholeDigits;

	// Берем первый символ от получившейся строки.
	int wholeSignificand = resultString[0] - '0';
	string notWholeSignificandStr = resultString.substr(1, resultString.length() - 1);
	BigInteger notWholeSignificand = BigInteger(notWholeSignificandStr);
	// Посчитаем количество нулей в начале нецелой части.
	int countZerroInStart = ExponentialNotation::GetCountZerrosInStartStr(notWholeSignificandStr);
	notWholeSignificand.SetZerrosInStart(countZerroInStart);

	// Определяем знак.
	int sign = left._sign == right._sign ? 1 : -1;
	// Определим результирующую точность как большую из левого и правого.
	int currentAccuracy = ExponentialNotation::GetMaxAccuracy(left, right);
	int maxCountDigitsNotWholePart = currentAccuracy;
	ExponentialNotation result = ExponentialNotation(sign, wholeSignificand, notWholeSignificand, resultExponent,
		currentAccuracy, maxCountDigitsNotWholePart);
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

	BigInteger numeratorBI = ExponentialNotation::GetBigIntegerFromExponential(numerator);
	string numeratorStr = numeratorBI.ToString();
	BigInteger denominatorBI = ExponentialNotation::GetBigIntegerFromExponential(denominator);
	string denominatorStr = denominatorBI.ToString();

	int maxAccuracy = ExponentialNotation::GetMaxAccuracy(numerator, denominator);

	// Добавляем к строке числителя количество нулей равное максимальной точности + 1, чтобы потом округлить.
	numeratorStr += string(maxAccuracy + 1, '0');
	BigInteger resultBigInt = BigInteger(numeratorStr) / BigInteger(denominatorStr);
	// Теперь нужно отделить целую от нецелой части.
	string resultStr = resultBigInt.ToString();
	BigInteger notWholeResult = BigInteger(resultStr.substr(1, resultStr.length() - 1));
	int wholeResult = resultStr[0] - '0';
	int exponentResult = resultStr.length() - 1 - (maxAccuracy + 1);
	int countZerrosInStart = 0;

	// Результат получился 1 и больше - целая часть равна разнице с точностью.
	if (resultStr.length() > maxAccuracy + 1 && notWholeResult != 0)
	{
		countZerrosInStart = ExponentialNotation::GetCountZerrosInStartStr(resultStr.substr(1, resultStr.length() - 1));
		notWholeResult.SetZerrosInStart(countZerrosInStart);
	}

	string notWholeStr = notWholeResult.ToString();
	int sign = numerator._sign == denominator._sign ? 1 : -1;
	int maxCountDigitsNotWholePart = maxAccuracy;
	ExponentialNotation result = ExponentialNotation(sign, wholeResult, notWholeResult, exponentResult, maxAccuracy,
		maxCountDigitsNotWholePart);
	result.RoundExponentialNotation();

	return result;
}

const ExponentialNotation operator+(const ExponentialNotation&, const ExponentialNotation&)
{
	return ExponentialNotation();
}
