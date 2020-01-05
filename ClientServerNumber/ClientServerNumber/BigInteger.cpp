#include "BigInteger.h"



// Создает длинное целое положительное число со значением 0.
BigInteger::BigInteger()
{
	this->_sign = 0;
}

// Создает длинное целое число из строки.
BigInteger::BigInteger(string str)
{
	if (str.length() == 0)
	{
		this->_sign = 0;
	}
	else
	{
		// Если первый элемент минус, то выставляем флаг, что число отрицательное.
		if (str[0] == '-')
		{
			str = str.substr(1);
			this->_sign = -1;
		}
		else if (str.length() == 1 && str[0] == '0')
		{
			this->_sign = 0;
		}
		else
		{
			this->_sign = 1;
		}

		// Функция push_back для вектора вставляет элемент в конец.
		// Функция atoi позволяет преобразовать строку в число (в случае, если преобразование не удается, то возвращает 0).
		for (long long i = str.length(); i > 0; i -= COUNT_DIGITS_IN_ONE_ELEMENT) {
			// Если осталось символов меньше, чем заданное количество цифр в одном элементе массива.
			if (i < COUNT_DIGITS_IN_ONE_ELEMENT)
				this->_digits.push_back(atoi(str.substr(0, i).c_str()));
			else
				this->_digits.push_back(atoi(str.substr(i - COUNT_DIGITS_IN_ONE_ELEMENT, COUNT_DIGITS_IN_ONE_ELEMENT).c_str()));
		}

		this->RemoveLeadingZeros();
	}
}

// Удаляет ведущие нули, т.е. нули в начале числа.
void BigInteger::RemoveLeadingZeros()
{
	// Функция back для вектора возвращает ссылку на последний элемент.
	while (this->_digits.size() > 1 && this->_digits.back() == 0)
	{
		this->_digits.pop_back();
	}
}

// Печатает число в поток вывода.
ostream& operator <<(ostream& os, const BigInteger& bi)
{
	if (bi._digits.empty())
	{
		os << 0;
	}
	else {
		if (bi._sign == -1)
		{
			os << '-';
		}
		os << bi._digits.back();

		// Функция fill необходима для того, чтобы цифры печатались без разрывов.
		char old_fill = os.fill('0');
		for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; --i)
		{
			// Функция setw устанавливает ширину поля, использующуюся для операции вывода.
			os << setw(bi.COUNT_DIGITS_IN_ONE_ELEMENT) << bi._digits[i];
		}
		os.fill(old_fill);
	}

	return os;
}

// Сравнивает два числа на равенство.
bool operator ==(const BigInteger& left, const BigInteger& right) {
	// Числа разных знаков точно не равны.
	if (left._sign != right._sign)
	{
		return false;
	}
	// Если левое равно нулю.
	if (left._digits.empty())
	{
		// Т.к.нулевое число представляется как пустой вектор и как первое число вектора, равное нулю.
		// Если второе число тоже ноль, то числа равны.
		if (right._digits.empty() || (right._digits.size() == 1 && right._digits[0] == 0))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// Аналогичная проверка, если левый элемент является нулевым.
	if (right._digits.empty()) {
		if (left._digits.size() == 1 && left._digits[0] == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// Если размеры не совпадают.
	if (left._digits.size() != right._digits.size())
	{
		return false;
	}
	// Проверяем каждую цифру.
	for (size_t i = 0; i < left._digits.size(); ++i)
	{
		if (left._digits[i] != right._digits[i])
		{
			return false;
		}
	}

	return true;
}

// Возвращает копию переданного числа (унарный плюс).
const BigInteger BigInteger::operator +() const {
	return BigInteger(*this);
}

// Возвращает переданное число с противоположным знаком (унарный минус).
const BigInteger BigInteger::operator -() const
{
	BigInteger copy(*this);
	copy._sign = (-1) * copy._sign;
	return copy;
}

// Проверяет, является ли левый операнд меньше правого.
bool operator <(const BigInteger& left, const BigInteger& right)
{
	if (left == right)
	{
		return false;
	}
	if (left._sign == -1) {
		if (right._sign == -1)
		{
			return ((-right) < (-left));
		}
		else
		{
			return true;
		}
	}
	else if (right._sign == -1)
	{
		return false;
	}
	else
	{
		if (left._digits.size() != right._digits.size())
		{
			return left._digits.size() < right._digits.size();
		}
		else
		{
			for (long long i = left._digits.size() - 1; i >= 0; --i)
			{
				if (left._digits[i] != right._digits[i])
				{
					return left._digits[i] < right._digits[i];
				}
			}

			return false;
		}
	}
}

// Cравнивает два числа на неравенство.
bool operator !=(const BigInteger& left, const BigInteger& right)
{
	return !(left == right);
}

// Проверяет, является ли левый операнд меньше либо равен правого.
bool operator <=(const BigInteger& left, const BigInteger& right)
{
	return (left < right || left == right);
}

// Проверяет, является ли левый операнд больше правого.
bool operator >(const BigInteger& left, const BigInteger& right)
{
	return !(left <= right);
}

// Проверяет, является ли левый операнд больше либо равен правого.
bool operator >=(const BigInteger& left, const BigInteger& right)
{
	return !(left < right);
}

// Cкладывает два числа
const BigInteger operator +(BigInteger left, const BigInteger& right)
{
	if (left._sign == -1)
	{
		if (right._sign == -1)
		{
			return -(-left + (-right));
		}
		else
		{
			return right - (-left);
		}
	}
	else if (right._sign == -1)
	{
		return left - (-right);
	}
	int carry = 0;
	for (size_t i = 0; i < max(left._digits.size(), right._digits.size()) || carry != 0; ++i)
	{
		if (i == left._digits.size())
		{
			left._digits.push_back(0);
		}
		left._digits[i] += carry + (i < right._digits.size() ? right._digits[i] : 0);
		carry = left._digits[i] >= BigInteger::BASE;
		if (carry != 0)
		{
			left._digits[i] -= BigInteger::BASE;
		}
	}

	if (left._digits.size() == 1 && left._digits[0] == 0)
	{
		left._sign = 0;
	}
	else if (left > 0)
	{
		left._sign = 1;
	}
	else
	{
		left._sign = -1;
	}
	return left;
}

// Прибавляет к текущему числу новое.
BigInteger& BigInteger::operator +=(const BigInteger& value)
{
	return *this = (*this + value);
}

// Префиксный инкремент.
const BigInteger BigInteger::operator++()
{
	return (*this += 1);
}

// Преобразует число к строке.
BigInteger::operator string() const
{
	stringstream ss;
	ss << *this;
	return ss.str();
}

// Преобразует signed char к BigInteger.
BigInteger::BigInteger(signed char c)
{
	if (c < 0)
	{
		this->_sign = -1;
	}
	else if (c > 0)
	{
		this->_sign = 1;
	}
	else
	{
		this->_sign = 0;
	}

	this->_digits.push_back(abs(c));
}

// Преобразует unsigned char к BigInteger.
BigInteger::BigInteger(unsigned char c)
{
	if (c == 0)
	{
		this->_sign = 0;
	}
	else
	{
		this->_sign = 1;
	}
	this->_digits.push_back(c);
}

// Преобразует signed short к BigInteger.
BigInteger::BigInteger(signed short s)
{
	if (s < 0)
	{
		this->_sign = -1;
	}
	else if (s > 0)
	{
		this->_sign = 1;
	}
	else
	{
		this->_sign = 0;
	}

	this->_digits.push_back(abs(s));
}

// Преобразует unsigned short к BigInteger.
BigInteger::BigInteger(unsigned short s)
{
	if (s == 0)
	{
		this->_sign = 0;
	}
	else
	{
		this->_sign = 1;
	}
	this->_digits.push_back(s);
}

// Преобразует signed int к BigInteger.
BigInteger::BigInteger(signed int i) {
	if (i < 0)
	{
		this->_sign = 1;
	}
	else if (i > 0)
	{
		this->_sign = 1;
	}
	else
	{
		this->_sign = 0;
	}
	this->_digits.push_back(abs(i) % BigInteger::BASE);
	i /= BigInteger::BASE;
	if (i != 0)
	{
		this->_digits.push_back(abs(i));
	}
}

// Преобразует unsigned int к BigInteger.
BigInteger::BigInteger(unsigned int i)
{
	if (i == 0)
	{
		this->_sign = 0;
	}
	else
	{
		this->_sign = 1;
	}
	this->_digits.push_back(i % BigInteger::BASE);
	i /= BigInteger::BASE;
	if (i != 0)
	{
		this->_digits.push_back(i);
	}
}

// Преобразует signed long к BigInteger.
BigInteger::BigInteger(signed long l)
{
	if (l < 0)
	{
		this->_sign = -1;
	}
	else if (l > 0)
	{
		this->_sign = 1;
	}
	else
	{
		this->_sign = 0;
	}
	this->_digits.push_back(abs(l) % BigInteger::BASE);
	l /= BigInteger::BASE;
	if (l != 0)
	{
		this->_digits.push_back(abs(l));
	}
}

// Преобразует unsigned long к BigInteger.
BigInteger::BigInteger(unsigned long l)
{
	if (l == 0)
	{
		this->_sign = 0;
	}
	else
	{
		this->_sign = 1;
	}
	this->_digits.push_back(l % BigInteger::BASE);
	l /= BigInteger::BASE;
	if (l != 0)
	{
		this->_digits.push_back(l);
	}
}

// преобразует signed long long к BigInteger.
BigInteger::BigInteger(signed long long l)
{
	if (l < 0)
	{
		this->_sign = -1;
		l = -l;
	}
	else if (l > 0)
	{
		this->_sign = 1;
	}
	else
	{
		this->_sign = 0;
	}
	do {
		this->_digits.push_back(l % BigInteger::BASE);
		l /= BigInteger::BASE;
	} while (l != 0);
}

// Преобразует unsigned long long к BigInteger.
BigInteger::BigInteger(unsigned long long l)
{
	if (l == 0)
	{
		this->_sign = 0;
	}
	else
	{
		this->_sign = 1;
	}
	this->_sign = 1;
	do {
		this->_digits.push_back(l % BigInteger::BASE);
		l /= BigInteger::BASE;
	} while (l != 0);
}

// Постфиксный инкремент.
const BigInteger BigInteger::operator ++(int)
{
	*this += 1;
	return *this - 1;
}

// Префиксный декремент.
const BigInteger BigInteger::operator --()
{
	return *this -= 1;
}

// Постфиксный декремент.
const BigInteger BigInteger::operator --(int)
{
	*this -= 1;
	return *this + 1;
}

// Вычитает два числа.
const BigInteger operator -(BigInteger left, const BigInteger& right)
{
	if (right._sign == -1)
	{
		return left + (-right);
	}
	else if (left._sign == -1)
	{
		return -(-left + right);
	}
	else if (left < right)
	{
		return -(right - left);
	}
	int carry = 0;
	for (size_t i = 0; i < right._digits.size() || carry != 0; ++i)
	{
		left._digits[i] -= carry + (i < right._digits.size() ? right._digits[i] : 0);
		carry = left._digits[i] < 0;
		if (carry != 0)
		{
			left._digits[i] += BigInteger::BASE;
		}
	}

	left.RemoveLeadingZeros();

	if (left._digits.size() == 1 && left._digits[0] == 0)
	{
		left._sign = 0;
	}
	else if (left > 0)
	{
		left._sign = 1;
	}
	else
	{
		left._sign = -1;
	}
	return left;
}

// Вычитает из текущего числа новое.
BigInteger& BigInteger::operator -=(const BigInteger& value)
{
	return *this = (*this - value);
}

// Перемножает два числа.
const BigInteger operator *(const BigInteger& left, const BigInteger& right)
{
	BigInteger result;
	result._digits.resize(left._digits.size() + right._digits.size());
	for (size_t i = 0; i < left._digits.size(); ++i)
	{
		int carry = 0;
		for (size_t j = 0; j < right._digits.size() || carry != 0; ++j)
		{
			long long cur = result._digits[i + j] +
				left._digits[i] * 1LL * (j < right._digits.size() ? right._digits[j] : 0) + carry;
			result._digits[i + j] = static_cast<int>(cur % BigInteger::BASE);
			carry = static_cast<int>(cur / BigInteger::BASE);
		}
	}

	if (left == 0 || right == 0)
	{
		result._sign = 0;
	}
	else if (left._sign != right._sign)
	{
		result._sign = -1;
	}
	else
	{
		result._sign = 1;
	}

	result.RemoveLeadingZeros();
	return result;
}

// Домножает текущее число на указанное.
BigInteger& BigInteger::operator *=(const BigInteger& value)
{
	return *this = (*this * value);
}

// Сдвигает все разряды на 1 вправо (домножает на BASE).
void BigInteger::_shift_right()
{
	if (this->_digits.size() == 0)
	{
		this->_digits.push_back(0);
		return;
	}
	this->_digits.push_back(this->_digits[this->_digits.size() - 1]);
	for (size_t i = this->_digits.size() - 2; i > 0; --i)
	{
		this->_digits[i] = this->_digits[i - 1];
	}
	this->_digits[0] = 0;
}

// Делит два числа.
const BigInteger operator /(const BigInteger& left, const BigInteger& right)
{
	if (right == 0)
	{
		throw "Divide by zerro exception";/*BigInteger::DivideByZeroException();*/
	}
	BigInteger b = right;
	b._sign = 1;
	BigInteger result, current;
	result._digits.resize(left._digits.size());
	for (long long i = static_cast<long long>(left._digits.size()) - 1; i >= 0; --i)
	{
		current._shift_right();
		current._digits[0] = left._digits[i];
		current._sign = left._sign;
		current.RemoveLeadingZeros();
		int x = 0, l = 0, r = BigInteger::BASE;
		while (l <= r)
		{
			int m = (l + r) / 2;
			BigInteger t = b * m;
			if (t <= current)
			{
				x = m;
				l = m + 1;
			}
			else r = m - 1;
		}

		result._digits[i] = x;
		current = current - b * x;
	}

	if (left._digits.size() == 1 && left._digits[0] == 0)
	{
		result._sign = 0;
	}
	else if (left._sign != right._sign)
	{
		result._sign = -1;
	}
	else
	{
		result._sign = 1;
	}
	result.RemoveLeadingZeros();
	return result;
}

// Делит текущее число на указанное.
BigInteger& BigInteger::operator /=(const BigInteger& value)
{
	return *this = (*this / value);
}

// Возвращает остаток от деления двух чисел.
const BigInteger operator %(const BigInteger& left, const BigInteger& right)
{
	BigInteger result = left - (left / right) * right;
	if (result._sign == -1)
	{
		result += right;
	}
	if (result._digits.size() == 1 && result._digits[0] == 0)
	{
		result._sign = 0;
	}
	else if (result > 0)
	{
		result._sign = 1;
	}
	else
	{
		result._sign = -1;
	}

	return result;
}

// Присваивает текущему числу остаток от деления на другое число.
BigInteger& BigInteger::operator %=(const BigInteger& value)
{
	return *this = (*this % value);
}

// Проверяет, является ли текущее число нечетным.
bool BigInteger::odd() const
{
	if (this->_digits.size() == 0)
	{
		return false;
	}
	return this->_digits[0] & 1;
}

// Проверяет, является ли текущее число четным.
bool BigInteger::even() const
{
	return !this->odd();
}

int BigInteger::Sign()
{
	return this->_sign;
}

string BigInteger::ToString()
{
	stringstream ss;
	ss << *this;
	return ss.str();
}

BigInteger BigInteger::_one = BigInteger("1");

BigInteger BigInteger::One()
{
	return _one;
}

BigInteger BigInteger::_zero = BigInteger("0");

BigInteger BigInteger::Zero()
{
	return _zero;
}

BigInteger BigInteger::_minusOne = BigInteger("-1");

BigInteger BigInteger::MinusOne()
{
	return _minusOne;
}

BigInteger BigInteger::Divide(BigInteger numerator, BigInteger denominator)
{
	return numerator / denominator;
}

BigInteger BigInteger::Remainder(BigInteger numerator, BigInteger denominator)
{
	return numerator % denominator;
}

BigInteger BigInteger::Abs(BigInteger number)
{
	if (number.Sign() < 0)
	{
		number._sign = 1;
	}
	return number;
}

BigInteger BigInteger::GreatestCommonDivisor(BigInteger numerator, BigInteger denominator)
{
	numerator = BigInteger::Abs(numerator);
	denominator = BigInteger::Abs(denominator);

	while (numerator != 0 && denominator != 0)
	{
		if (numerator > denominator)
		{
			numerator %= denominator;
		}
		else
		{
			denominator %= numerator;
		}
	}
	return numerator+denominator;
}

// Возводит текущее число в указанную степень.
const BigInteger BigInteger::pow(BigInteger n) const
{
	BigInteger a(*this), result(1);
	while (n != 0)
	{
		if (n.odd())
		{
			result *= a;
		}
		a *= a;
		n /= 2;
	}

	return result;
}