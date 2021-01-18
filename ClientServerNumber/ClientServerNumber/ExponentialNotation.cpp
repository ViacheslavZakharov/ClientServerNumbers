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
	ReformToExponentialNotation(rationalNumeric);
}

ExponentialNotation::ExponentialNotation(int sign, int significandWhole, BigInteger significandNotWhole,
	int exponent, int accuracy)
{
	_sign = sign;
	_significandWhole = significandWhole;
	_significandNotWhole = significandNotWhole;
	_exponent = exponent;
	_currentAccuracy = accuracy;
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
	// ≈сли рациональное число равно 0, то вычислени¤ бессмысленны.
	if (rational == 0)
	{
		return;
	}

	BigInteger wholePart = rational.GetWholePart();
	// Если целая часть числа больше нуля, вычислим разницу целой части числа и мантиссы(от 1 до 9)* 10^n.
	_significandWhole = CalculateSignificandWhole(rational);
	BigInteger remainderWholePart = _significandWhole == 0 
		? BigInteger()
		: wholePart - _significandWhole * BigInteger(FUNDAMENT).Pow(_exponent);

	_significandNotWhole = CalculateSignificandNotWhole(rational, remainderWholePart, _significandWhole);
}

BigInteger ExponentialNotation::GetBigIntegerFromExponential(ExponentialNotation number)
{
	int significandWhole = number.GetSignificandWholePart();
	BigInteger notWholeSignificand = number.GetSignificandNotWholePart();

	string notWholeSignificandStr = notWholeSignificand.ToString();
	notWholeSignificandStr = notWholeSignificandStr == "0" ? "" : notWholeSignificandStr;
	string resultString = significandWhole != 0 ? to_string(significandWhole) : "";
	resultString += notWholeSignificandStr;
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

int ExponentialNotation::CalculateSignificandWhole(RationalNumerics rational)
{
	BigInteger wholePart = rational.GetWholePart();
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

BigInteger ExponentialNotation::CalculateSignificandNotWhole(RationalNumerics rational,
	BigInteger remainderWholePart, int significandWhole)
{
	RationalNumerics fractionPart = rational.GetFractionPart();
	if (fractionPart == 0 && significandWhole == 0)
	{
		return BigInteger("0");
	}
	if (fractionPart == 0 && significandWhole != 0)
	{
		string fullWholePart = rational.GetWholePart().ToString();
		_exponent = fullWholePart.length() - 1;
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
			if (significandNotWhole == 0 && significandWhole != 0)
			{
				countZerroInStart++;
			}
			// Если число меньше единицы, то надо уменьшать степень 10 на единицу, если это не первый раз.
			if (significandNotWhole == 0 && significandWhole == 0 && temporaryAccuracy > 1)
			{
				_exponent--;
			}
		}
		significandNotWhole += numerator / denominator;
		numerator %= denominator;
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
	significandNotWhole = BigInteger::CutMathematic(significandNotWhole, _currentAccuracy + _exponent);

	return significandNotWhole;
}

const ExponentialNotation operator*(const ExponentialNotation& left, const ExponentialNotation& right)
{
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
	int leftNotWholeDigits = left._significandNotWhole == 0
		? 0
		: BigInteger::GetCountDigits(left._significandNotWhole) - left._exponent;
	int rightNotWholeDigits = right._significandNotWhole == 0
		? 0
		: BigInteger::GetCountDigits(right._significandNotWhole) - right._exponent;
	int resultNotWholeDigits = leftNotWholeDigits + rightNotWholeDigits;

	// Результирующий показатель степени расчитывается как: 
	// общая длина числа - 1 (для целой части) - длина нецелой части.
	int resultExponent = resultString.length() - 1 - resultNotWholeDigits;

	// Ѕерем первый символ от получившейся строки.
	int wholeSignificand = resultString[0] - '0';
	string notWholeSignificandStr = resultString.substr(1, resultString.length() - 1);
	BigInteger notWholeSignificand = BigInteger(notWholeSignificandStr);
	// Посчитаем количество нулей в начале нецелой части.
	int countZerroInStart = ExponentialNotation::GetCountZerrosInStartStr(notWholeSignificandStr);
	notWholeSignificand.SetZerrosInStart(countZerroInStart);
	notWholeSignificand = BigInteger::CutMathematic(notWholeSignificand, left._currentAccuracy + resultExponent);
	// Определяем знак.
	int sign = left._sign == right._sign ? 1 : -1;
	// Определим результирующую точность как большую из левого и правого.
	int accuracy = ExponentialNotation::GetMaxAccuracy(left, right);
	return ExponentialNotation(sign, wholeSignificand, notWholeSignificand, resultExponent, accuracy);
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
	// Подсчитаем количество нулей (степень 10), которое надо добавить (умножить на 10) к числителю.
	// Для этого определим количество цифр целой и нецелых частей для числителя и знаменателя.
	int numeratorCountNotWhole = numerator._significandNotWhole == 0
		? 0
		: BigInteger::GetCountDigits(numerator._significandNotWhole) - numerator._exponent;
	int denominatorCountNotWhole = denominator._significandNotWhole == 0
		? 0
		: BigInteger::GetCountDigits(denominator._significandNotWhole) - denominator._exponent;
	int maxAccuracy = ExponentialNotation::GetMaxAccuracy(numerator, denominator);
	
	if (denominatorCountNotWhole > numeratorCountNotWhole)
	{
		numeratorStr += string(denominatorCountNotWhole - numeratorCountNotWhole, '0');
	}

	if (numeratorCountNotWhole > denominatorCountNotWhole)
	{
		denominatorStr += string(numeratorCountNotWhole - denominatorCountNotWhole, '0');
	}

	// Добавляем к строке числителя количество нулей равное максимальной точности + 1, чтобы потом округлить.
	numeratorStr += string(maxAccuracy + 1, '0');
	BigInteger result = BigInteger(numeratorStr) / BigInteger(denominatorStr);
	// Теперь нужно отделить целую от нецелой части.
	string resultStr = result.ToString();
	BigInteger notWholeResult = BigInteger(resultStr.substr(1, resultStr.length() - 1));
	int wholeResult = resultStr[0] - '0';
	int exponentResult = resultStr.length() - 1 - (maxAccuracy + 1);
	int countZerrosInStart = 0;

	// Результат получился 1 и больше - целая часть равна разнице с точностью.
	if (resultStr.length() > maxAccuracy + 1)
	{
		countZerrosInStart = ExponentialNotation::GetCountZerrosInStartStr(resultStr.substr(1, resultStr.length() - 1));
		notWholeResult.SetZerrosInStart(countZerrosInStart);
	}
	string notWholeStr = notWholeResult.ToString();
	if (notWholeStr.length() > 1)
	{
		notWholeResult = BigInteger::CutMathematic(notWholeResult, resultStr.length() - 2);
	}
	else if (notWholeStr.length() == 1 ) //  Тогда одна цифра в нецелой части и ее надо округлить.
	{
		notWholeResult = 0;
		wholeResult = notWholeStr[0] - '0' >= 5 ? wholeResult + 1 : wholeResult;
	}

	int sign = numerator._sign == denominator._sign ? 1 : -1;
	return ExponentialNotation(sign, wholeResult, notWholeResult, exponentResult, maxAccuracy);
}
