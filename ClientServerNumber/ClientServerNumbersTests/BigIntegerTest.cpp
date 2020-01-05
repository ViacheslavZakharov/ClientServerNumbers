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

		const string LONG_POSITIVE_STRING = "1234567891011121314";
		const string OTHER_LONG_POSITIVE_STRING = "2222222222222222";

		const int SHORT_POSITIVE_INT = 1234;
		const long long LONG_POSITIVE_LONG = 1234567891011121314L;

		const string SHORT_NEGATIVE_STRING = "-1234";
		const string LONG_NEGATIVE_STRING = "-1234567891011121314";

		TEST_METHOD(Constructor_DifferentType_ReturnSameResult)
		{
			//string str1 = "123";
			//int int1 = 123;
			BigInteger b1(SHORT_POSITIVE_STRING);
			BigInteger b2(SHORT_POSITIVE_INT);
			Assert::AreEqual(b1.ToString(), b2.ToString());
			Assert::AreEqual(b1.Sign(), b2.Sign());
			Assert::AreEqual(b1.Sign(), 1);

			//string longStr = "1234567891011121314";
			//long long longLong = 1234567891011121314;
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
		}
	};
}