#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ClientServerNumber/BigInteger.h"
#include "../ClientServerNumber/BigInteger.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClientServerNumbersTests
{		
	TEST_CLASS(BigIntegerTest)
	{
	public:
		const string SHORT_POSITIVE_STRING = "1234";
		const string OTHER_SHORT_POSITIVE_STRING = "4";

		const string LONG_POSITIVE_STRING =		  "1234567891011121314";
		const string OTHER_LONG_POSITIVE_STRING = "2222222222222222";
		const string OTHER2_LONG_POSITIVE_STRING= "1000000000000004";
		
		const int SHORT_POSITIVE_INT = 1234;
		const long long LONG_POSITIVE_LONG = 1234567891011121314L;

		const string SHORT_NEGATIVE_STRING = "-1234";
		const string LONG_NEGATIVE_STRING = "-1234567891011121314";

		TEST_METHOD(Constructor_DifferentType_ReturnSameResult)
		{
			BigInteger b1(SHORT_POSITIVE_STRING);
			BigInteger b2(SHORT_POSITIVE_INT);
			Assert::AreEqual(b1.ToString(), b2.ToString());
			Assert::AreEqual(b1.Sign(), b2.Sign());
			Assert::AreEqual(b1.Sign(), 1);

			BigInteger b3(LONG_POSITIVE_STRING);
			BigInteger b4(LONG_POSITIVE_LONG);
			Assert::AreEqual(b3.ToString(), b4.ToString());
			Assert::AreEqual(b3.Sign(), b4.Sign());
			Assert::AreEqual(b3.Sign(), 1);

			Assert::AreEqual(BigInteger().Sign(), 0);

			BigInteger b6(SHORT_NEGATIVE_STRING);
			Assert::AreEqual(b6.Sign(), -1);

			BigInteger b7(LONG_NEGATIVE_STRING);
			Assert::AreEqual(b7.Sign(), -1);

		}

		TEST_METHOD(EqualsEqualsOperator_DifferentNumber_False)
		{
			BigInteger b1(SHORT_POSITIVE_STRING);
			BigInteger b2(OTHER_SHORT_POSITIVE_STRING);
			Assert::AreEqual(b1 == b2, false);

			BigInteger b3(SHORT_POSITIVE_STRING);
			BigInteger b4(SHORT_POSITIVE_STRING);
			Assert::AreEqual(b3 == b4, true);

			BigInteger b5(LONG_POSITIVE_STRING);
			BigInteger b6(OTHER_LONG_POSITIVE_STRING);
			Assert::AreEqual(b5 == b6, false);

			BigInteger b7(LONG_POSITIVE_STRING);
			BigInteger b8(LONG_POSITIVE_STRING);
			Assert::AreEqual(b7 == b8, true);

			BigInteger b9(LONG_POSITIVE_STRING);
			BigInteger b10(LONG_NEGATIVE_STRING);
			Assert::AreEqual(b9 == b10, false);

			Assert::AreEqual(BigInteger("0") == 0, true);

		}

		TEST_METHOD(LessOperator_DifferentNumber_False)
		{
			BigInteger b1(SHORT_POSITIVE_STRING);
			BigInteger b2(OTHER_SHORT_POSITIVE_STRING);
			Assert::AreEqual(b2 > b1, false);

			BigInteger b3(SHORT_POSITIVE_STRING);
			BigInteger b4(SHORT_POSITIVE_STRING);
			Assert::AreEqual(b3 > b4, false);

			BigInteger b5(LONG_POSITIVE_STRING);
			BigInteger b6(OTHER_LONG_POSITIVE_STRING);
			Assert::AreEqual(b5 > b6, true);

			BigInteger b7(LONG_POSITIVE_STRING);
			BigInteger b8(LONG_NEGATIVE_STRING);
			Assert::AreEqual(b7 > b8, true);

			BigInteger b9(SHORT_NEGATIVE_STRING);
			BigInteger b10(LONG_NEGATIVE_STRING);
			Assert::AreEqual(b9 > b10, true);

		}
		//TODO: Сделать тесты для всех операторов.

		TEST_METHOD(PlusOperator_BigNumbers_CorrectResult)
		{
			BigInteger b1(OTHER_LONG_POSITIVE_STRING);
			BigInteger b2(OTHER2_LONG_POSITIVE_STRING);
			Assert::AreEqual(b1 + b2 == BigInteger("3222222222222226"), true);
		}

		TEST_METHOD(MinusOperator_BigNumbers_CorrectResult)
		{
			BigInteger b1(OTHER_LONG_POSITIVE_STRING);
			BigInteger b2(OTHER2_LONG_POSITIVE_STRING);
			Assert::AreEqual(b1 - b2 == BigInteger("1222222222222218"), true);
		}

		TEST_METHOD(MultiplyOperator_BigNumbers_CorrectResult)
		{
			BigInteger b1(OTHER_LONG_POSITIVE_STRING);
			BigInteger b2(OTHER2_LONG_POSITIVE_STRING);
			Assert::AreEqual(b1 * b2 == BigInteger("2222222222222230888888888888888"), true);
		}

		TEST_METHOD(DivideOperator_BigNumbers_CorrectResult)
		{
			BigInteger b1(OTHER_LONG_POSITIVE_STRING);
			BigInteger b2(OTHER2_LONG_POSITIVE_STRING);
			Assert::AreEqual(b1 / b2 == BigInteger("2"), true);
		}

		TEST_METHOD(RemindOperator_BigNumbers_CorrectResult)
		{
			BigInteger b1(OTHER_LONG_POSITIVE_STRING);
			BigInteger b2(OTHER2_LONG_POSITIVE_STRING);
			Assert::AreEqual(b1 % b2 == BigInteger("222222222222214"), true);
		}

		TEST_METHOD(GreatestCommonDivisor_BigNumbers_CorrectResult)
		{
			BigInteger b1(OTHER2_LONG_POSITIVE_STRING);
			BigInteger b2(OTHER_SHORT_POSITIVE_STRING);
			Assert::AreEqual(BigInteger::GreatestCommonDivisor(b1, b2) == BigInteger("4"), true);
		}
	};
}