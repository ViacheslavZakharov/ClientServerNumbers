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
}

int ExponentialNotation::Sign()
{
    return _sign;
}

string ExponentialNotation::ToString(bool withPeriod)
{
	string resultString = "";
	if (_sign == 0)
	{
		return "0";
	}

	resultString = to_string(_significandWhole) + ",";
	string periodString = _period.ToString();
	if (periodString != "0" && withPeriod) {
		string digitsBeforePeriod = _digitsBeforePeriod.ToString();
		digitsBeforePeriod = digitsBeforePeriod == "0" ? "" : digitsBeforePeriod;
		resultString += digitsBeforePeriod + "(" + periodString + ")";
	}
	else {
		resultString += _significandNotWhole.ToString();
	}
	
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

int ExponentialNotation::GetSignificandWholePart()
{
    return _significandWhole;
}

BigInteger ExponentialNotation::GetSignificandNotWholePart()
{
    return _significandNotWhole;
}

int ExponentialNotation::GetCurrentCountDigitsNotWhole()
{
	return _currentCountDigitsNotWhole;
}

int ExponentialNotation::GetMaxCountDigitsNotWhole()
{
	return _maxCountDigitsNotWholePart;
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
	// Если целая часть числа больше нуля, вычислим разницу целой части числа и мантиссы (от 1 до 9) * 10^n.
	_significandWhole = CalculateSignificandWhole(wholePart);
	BigInteger remainderWholePart = _significandWhole == 0 
		? BigInteger()
		: wholePart - _significandWhole * BigInteger(FUNDAMENT).Pow(_exponent);

	CalculateSignificandNotWhole(rational, remainderWholePart);
	RoundExponentialNotation();
}

ExponentialNotation ExponentialNotation::Abs(const ExponentialNotation& number)
{
	ExponentialNotation result = number;
	if (result.Sign() < 0)
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

int ExponentialNotation::GetAccuracy(ExponentialNotation number, ExponentialNotation idealNumber)
{
	ExponentialNotation diff = ExponentialNotation::Abs(idealNumber) - ExponentialNotation::Abs(number);
	if (diff.Sign() == 0) {
		return number.GetMaxCountDigitsNotWhole();
	}
	int accuracy = std::abs(diff._exponent) - 1;
	return accuracy;
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
				// Если без остатка делится на основание, то необходимо добавить 0 к началу нецелой части.
				if (tempSignificandWholePart % FUNDAMENT == 0)
				{
					_significandNotWhole.SetZerrosInStart(1);
				}
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
		_significandNotWhole = BigInteger(fullWholePart.substr(1, fullWholePart.length() - 1));
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
	// Определим список остатков для определения периода. Для знаменателя N остаток может иметь только N значений 0...N-1
	// Подробнее: https://purecodecpp.com/archives/2782.
	vector<BigInteger> reminderList;
	int indexStartPeriod = 0;
	int indexEndPeriod = 0;
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
				_significandNotWhole.SetZerrosInStart(countZerroInStart);
				countZerroInStart = ExponentialNotation::GetCountZerrosInStartStr(currentNotWhole);
				_significandNotWhole.SetZerrosInStart(countZerroInStart);
				_exponent--;
				if (indexEndPeriod != 0 && indexStartPeriod == 0) {
					indexStartPeriod = indexEndPeriod - 1;
					indexEndPeriod = indexStartPeriod + indexEndPeriod;
				}
			}
		}

		if (numerator == 0)
		{
			break;
		}

		vector<BigInteger>::iterator it = find(reminderList.begin(), reminderList.end(), numerator);
		if (it == reminderList.end() /*|| reminderList.size() < countZerroInStart ||*/) {
			reminderList.push_back(numerator);
		}
		else if(indexEndPeriod == 0) {
			BigInteger numberIterator = reminderList.begin() - it;
			indexStartPeriod = numberIterator.GetFirstIntNumber();
			// Если целая часть уже заполнена и не будет браться из нецелой и остаток находится не на нулевом месте,
			// То необходимо увеличить индекс начала периода на один, так как остатки отстают от чисел на 1 цифру.
			if (_significandWhole != 0 && indexStartPeriod != 0) {
				indexStartPeriod++;
				indexEndPeriod = _significandNotWhole.ToString().length();
			}
			else {
				indexEndPeriod = _significandNotWhole.ToString().length() - 1;
			}
		}
	}

	// Если число имеет количество знаков меньше, чем точность, то необходимо уменьшить точность.
	if (temporaryCountDigitsNotWhole < _currentCountDigitsNotWhole)
	{
		_currentCountDigitsNotWhole = temporaryCountDigitsNotWhole;
	}

	_significandNotWhole.SetZerrosInStart(countZerroInStart + currentCountZerrosInStart);
	if (indexEndPeriod == 0) {
		return;
	}

	indexStartPeriod += countZerroInStart + currentCountZerrosInStart;
	indexEndPeriod += countZerroInStart + currentCountZerrosInStart;
	string notWhole = _significandNotWhole.ToString();
	if (notWhole.length() >= indexEndPeriod) {
		_digitsBeforePeriod = BigInteger(notWhole.substr(0, indexStartPeriod));
		_period = BigInteger(notWhole.substr(indexStartPeriod, indexEndPeriod - indexStartPeriod));
		if (_digitsBeforePeriod != 0) {
			_digitsBeforePeriod.SetZerrosInStart(_significandNotWhole.GetZerroInStart());
		}
		else {
			_period.SetZerrosInStart(_significandNotWhole.GetZerroInStart());
		}
	}
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
	int countZerrosInStart = ExponentialNotation::GetCountZerrosInStartStr(resultStr.substr(1, resultStr.length() - 1));
	notWholeSignificand.SetZerrosInStart(countZerrosInStart);

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
	// Посчитаем количество нулей в начале нецелой части.
	int countZerroInStart = ExponentialNotation::GetCountZerrosInStartStr(notWholeSignificandStr);
	notWholeSignificand.SetZerrosInStart(countZerroInStart);

	// Определим результирующую точность как большую из левого и правого.
	// Подумать над правильностью этого действия.
	/*int currentCountDigitsNotWhole = std::max(l._currentCountDigitsNotWhole, r._currentCountDigitsNotWhole);*/
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

	/*int currentCountDigitsNotWhole = std::max(n._currentCountDigitsNotWhole, d._currentCountDigitsNotWhole);*/
	int currentCountDigitsNotWhole = std::max(n._maxCountDigitsNotWholePart, d._maxCountDigitsNotWholePart);
	int maxCountDigitsNotWholePart = currentCountDigitsNotWhole;

	// Добавляем к строке числителя количество нулей равное максимальной точности + 1, чтобы потом округлить.
	numeratorStr += string(currentCountDigitsNotWhole + 1, '0');
	BigInteger resultBigInt = BigInteger(numeratorStr) / BigInteger(denominatorStr);
	// Теперь нужно отделить целую от нецелой части.
	int sign = resultBigInt.Sign();
	string resultStr = resultBigInt.ToString();

	resultStr = sign < 0 ? resultStr.substr(1, resultStr.length() - 1) : resultStr;

	BigInteger notWholeResult = BigInteger(resultStr.substr(1, resultStr.length() - 1));
	int wholeResult = resultStr[0] - '0';
	int exponentResult = resultStr.length() - 1 - (currentCountDigitsNotWhole + 1);
	int countZerrosInStart = 0;

	// Результат получился 1 и больше - целая часть равна разнице с точностью.
	if (resultStr.length() > currentCountDigitsNotWhole + 1 && notWholeResult != 0)
	{
		countZerrosInStart = ExponentialNotation::GetCountZerrosInStartStr(resultStr.substr(1, resultStr.length() - 1));
		notWholeResult.SetZerrosInStart(countZerrosInStart);
	}

	ExponentialNotation result = ExponentialNotation(sign, wholeResult, notWholeResult, exponentResult, currentCountDigitsNotWhole,
		maxCountDigitsNotWholePart);
	result.RoundExponentialNotation();

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
