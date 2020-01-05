#include "BigInteger.h"



// ������� ������� ����� ������������� ����� �� ��������� 0.
BigInteger::BigInteger()
{
	this->_sign = 0;
}

// ������� ������� ����� ����� �� ������.
BigInteger::BigInteger(string str)
{
	if (str.length() == 0)
	{
		this->_sign = 0;
	}
	else
	{
		// ���� ������ ������� �����, �� ���������� ����, ��� ����� �������������.
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

		// ������� push_back ��� ������� ��������� ������� � �����.
		// ������� atoi ��������� ������������� ������ � ����� (� ������, ���� �������������� �� �������, �� ���������� 0).
		for (long long i = str.length(); i > 0; i -= COUNT_DIGITS_IN_ONE_ELEMENT) {
			// ���� �������� �������� ������, ��� �������� ���������� ���� � ����� �������� �������.
			if (i < COUNT_DIGITS_IN_ONE_ELEMENT)
				this->_digits.push_back(atoi(str.substr(0, i).c_str()));
			else
				this->_digits.push_back(atoi(str.substr(i - COUNT_DIGITS_IN_ONE_ELEMENT, COUNT_DIGITS_IN_ONE_ELEMENT).c_str()));
		}

		this->RemoveLeadingZeros();
	}
}

// ������� ������� ����, �.�. ���� � ������ �����.
void BigInteger::RemoveLeadingZeros()
{
	// ������� back ��� ������� ���������� ������ �� ��������� �������.
	while (this->_digits.size() > 1 && this->_digits.back() == 0)
	{
		this->_digits.pop_back();
	}
}

// �������� ����� � ����� ������.
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

		// ������� fill ���������� ��� ����, ����� ����� ���������� ��� ��������.
		char old_fill = os.fill('0');
		for (long long i = static_cast<long long>(bi._digits.size()) - 2; i >= 0; --i)
		{
			// ������� setw ������������� ������ ����, �������������� ��� �������� ������.
			os << setw(bi.COUNT_DIGITS_IN_ONE_ELEMENT) << bi._digits[i];
		}
		os.fill(old_fill);
	}

	return os;
}

// ���������� ��� ����� �� ���������.
bool operator ==(const BigInteger& left, const BigInteger& right) {
	// ����� ������ ������ ����� �� �����.
	if (left._sign != right._sign)
	{
		return false;
	}
	// ���� ����� ����� ����.
	if (left._digits.empty())
	{
		// �.�.������� ����� �������������� ��� ������ ������ � ��� ������ ����� �������, ������ ����.
		// ���� ������ ����� ���� ����, �� ����� �����.
		if (right._digits.empty() || (right._digits.size() == 1 && right._digits[0] == 0))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	// ����������� ��������, ���� ����� ������� �������� �������.
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
	// ���� ������� �� ���������.
	if (left._digits.size() != right._digits.size())
	{
		return false;
	}
	// ��������� ������ �����.
	for (size_t i = 0; i < left._digits.size(); ++i)
	{
		if (left._digits[i] != right._digits[i])
		{
			return false;
		}
	}

	return true;
}

// ���������� ����� ����������� ����� (������� ����).
const BigInteger BigInteger::operator +() const {
	return BigInteger(*this);
}

// ���������� ���������� ����� � ��������������� ������ (������� �����).
const BigInteger BigInteger::operator -() const
{
	BigInteger copy(*this);
	copy._sign = (-1) * copy._sign;
	return copy;
}

// ���������, �������� �� ����� ������� ������ �������.
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

// C��������� ��� ����� �� �����������.
bool operator !=(const BigInteger& left, const BigInteger& right)
{
	return !(left == right);
}

// ���������, �������� �� ����� ������� ������ ���� ����� �������.
bool operator <=(const BigInteger& left, const BigInteger& right)
{
	return (left < right || left == right);
}

// ���������, �������� �� ����� ������� ������ �������.
bool operator >(const BigInteger& left, const BigInteger& right)
{
	return !(left <= right);
}

// ���������, �������� �� ����� ������� ������ ���� ����� �������.
bool operator >=(const BigInteger& left, const BigInteger& right)
{
	return !(left < right);
}

// C��������� ��� �����
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

// ���������� � �������� ����� �����.
BigInteger& BigInteger::operator +=(const BigInteger& value)
{
	return *this = (*this + value);
}

// ���������� ���������.
const BigInteger BigInteger::operator++()
{
	return (*this += 1);
}

// ����������� ����� � ������.
BigInteger::operator string() const
{
	stringstream ss;
	ss << *this;
	return ss.str();
}

// ����������� signed char � BigInteger.
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

// ����������� unsigned char � BigInteger.
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

// ����������� signed short � BigInteger.
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

// ����������� unsigned short � BigInteger.
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

// ����������� signed int � BigInteger.
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

// ����������� unsigned int � BigInteger.
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

// ����������� signed long � BigInteger.
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

// ����������� unsigned long � BigInteger.
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

// ����������� signed long long � BigInteger.
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

// ����������� unsigned long long � BigInteger.
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

// ����������� ���������.
const BigInteger BigInteger::operator ++(int)
{
	*this += 1;
	return *this - 1;
}

// ���������� ���������.
const BigInteger BigInteger::operator --()
{
	return *this -= 1;
}

// ����������� ���������.
const BigInteger BigInteger::operator --(int)
{
	*this -= 1;
	return *this + 1;
}

// �������� ��� �����.
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

// �������� �� �������� ����� �����.
BigInteger& BigInteger::operator -=(const BigInteger& value)
{
	return *this = (*this - value);
}

// ����������� ��� �����.
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

// ��������� ������� ����� �� ���������.
BigInteger& BigInteger::operator *=(const BigInteger& value)
{
	return *this = (*this * value);
}

// �������� ��� ������� �� 1 ������ (��������� �� BASE).
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

// ����� ��� �����.
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

// ����� ������� ����� �� ���������.
BigInteger& BigInteger::operator /=(const BigInteger& value)
{
	return *this = (*this / value);
}

// ���������� ������� �� ������� ���� �����.
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

// ����������� �������� ����� ������� �� ������� �� ������ �����.
BigInteger& BigInteger::operator %=(const BigInteger& value)
{
	return *this = (*this % value);
}

// ���������, �������� �� ������� ����� ��������.
bool BigInteger::odd() const
{
	if (this->_digits.size() == 0)
	{
		return false;
	}
	return this->_digits[0] & 1;
}

// ���������, �������� �� ������� ����� ������.
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

// �������� ������� ����� � ��������� �������.
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