#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ClientServerNumber/ServerRationalNumber.h"
#include "../ClientServerNumber/ServerRationalNumber.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClientServerNumbersTests
{
	// TODO: Переделать тесты
	TEST_CLASS(ServerRationalNumberTest)
	{
	public:

#pragma region Constructor.Tests

		TEST_METHOD(Constructor_EmptyParameters_ReturnCorrectResult)
		{
			ServerRationalNumber s1 = ServerRationalNumber();
			Assert::AreEqual(string("0"), s1.ToString());
		}

		TEST_METHOD(Constructor_1On3_ReturnCorrectResult)
		{
			ServerRationalNumber s1 = ServerRationalNumber("1","3");
			Assert::AreEqual(string("3,33 * 10^-1"), s1.ToString());
		}

		//TEST_METHOD(Constructor_1On133_ReturnCorrectResult)
		//{
		//	ServerRationalNumber s1 = ServerRationalNumber("1", "133");
		//	Assert::AreEqual(string("0,752 * 10^-2"), s1.ToString());
		//}

		TEST_METHOD(Constructor_1On4_ReturnCorrectResult)
		{
			ServerRationalNumber s1 = ServerRationalNumber("1", "4");
			Assert::AreEqual(string("2,5 * 10^-1"), s1.ToString());
		}

		TEST_METHOD(Constructor_100_ReturnCorrectResult)
		{
			ServerRationalNumber s1 = ServerRationalNumber("100");
			Assert::AreEqual(string("1,0 * 10^2"), s1.ToString());
		}

		TEST_METHOD(Constructor_144On133_ReturnCorrectResult)
		{
			ServerRationalNumber s1 = ServerRationalNumber("144","133");
			Assert::AreEqual(string("1,083"), s1.ToString());
		}

		//TEST_METHOD(Constructor_1000On3_ReturnCorrectResult)
		//{
		//	ServerRationalNumber s1 = ServerRationalNumber("1000", "3");
		//	Assert::AreEqual(string("3,333 * 10^2"), s1.ToString());
		//}

		TEST_METHOD(Constructor_1000On300_ReturnCorrectResult)
		{
			ServerRationalNumber s1 = ServerRationalNumber("1000", "300");
			Assert::AreEqual(string("3,333"), s1.ToString());
		}

		TEST_METHOD(Constructor_1000On303_ReturnCorrectResult)
		{
			ServerRationalNumber s1 = ServerRationalNumber("1000", "303");
			Assert::AreEqual(string("3,300"), s1.ToString());
		}

		//TEST_METHOD(Constructor_10000On303_ReturnCorrectResult)
		//{
		//	ServerRationalNumber s1 = ServerRationalNumber("10000", "303");
		//	Assert::AreEqual(string("3,300 * 10^1"), s1.ToString());
		//}

		//TEST_METHOD(Constructor_100000On39_ReturnCorrectResult)
		//{
		//	ServerRationalNumber s1 = ServerRationalNumber("100000", "39");
		//	Assert::AreEqual(string("2,564 * 10^3"), s1.ToString());
		//}

		//TEST_METHOD(Constructor_158On3_ReturnCorrectResult)
		//{
		//	ServerRationalNumber s1 = ServerRationalNumber("158", "3");
		//	Assert::AreEqual(string("5,267 * 10^1"), s1.ToString());
		//}

#pragma endregion Constructor.Tests

#pragma IncreaseAccuracy.Tests

		//TEST_METHOD(IncreaseAccuracy_IncreaseOnOneDigit_ReturnCorrectResult)
		//{
		//	ServerRationalNumber s1 = ServerRationalNumber("158", "3");
		//	Assert::AreEqual(string("5,267 * 10^1"), s1.ToString());
		////	s1.IncreaseCurrentAccuracy(1);
		//	Assert::AreEqual(string("5,2667 * 10^1"), s1.ToString());
		//}

		//TEST_METHOD(IncreaseAccuracy_IncreaseOnFiveDigits_ReturnCorrectResult)
		//{
		//	ServerRationalNumber s1 = ServerRationalNumber("100000", "39");
		//	Assert::AreEqual(string("2,564 * 10^3"), s1.ToString());
		////	s1.IncreaseCurrentAccuracy(5);
		//	Assert::AreEqual(string("2,56410256 * 10^3"), s1.ToString());
		//}

#pragma endregion IncreaseAccuracy.Tests

#pragma Operators

		TEST_METHOD(PlusOperator_1On3And1On3_ReturnCorrectResult)
		{
			ServerRationalNumber s1 = ServerRationalNumber("1", "3");
			ServerRationalNumber s2 = ServerRationalNumber("1", "3");
			ServerRationalNumber result = s1 + s2;

			Assert::AreEqual(string("6,66 * 10^-1"), result.ToString());
		}

		TEST_METHOD(PlusOperator_2On3And2On3_ReturnCorrectResult)
		{
			ServerRationalNumber s1 = ServerRationalNumber("2", "3");
			ServerRationalNumber s2 = ServerRationalNumber("2", "3");
			ServerRationalNumber result = s1 + s2;

			Assert::AreEqual(string("1,334"), result.ToString());
		}

		//TEST_METHOD(PlusOperator_100On7And100On7_ReturnCorrectResult)
		//{
		//	ServerRationalNumber s1 = ServerRationalNumber("100", "7");
		//	ServerRationalNumber s2 = ServerRationalNumber("100", "7");
		//	ServerRationalNumber result = s1 + s2;

		//	Assert::AreEqual(string("2,857 * 10^1"), result.ToString());
		//}

		TEST_METHOD(PlusOperator_2On3And1On4_ReturnCorrectResult)
		{
			ServerRationalNumber s1 = ServerRationalNumber("2", "3");
			ServerRationalNumber s2 = ServerRationalNumber("1", "4");
			ServerRationalNumber result = s1 + s2;

			Assert::AreEqual(string("9,17 * 10^-1"), result.ToString());
		}

		TEST_METHOD(PlusOperator_3On2And2On3_ReturnCorrectResult)
		{
			ServerRationalNumber s1 = ServerRationalNumber("3", "2");
			ServerRationalNumber s2 = ServerRationalNumber("2", "3");
			ServerRationalNumber result = s1 + s2;

			Assert::AreEqual(string("2,167"), result.ToString());
		}

		TEST_METHOD(MinusOperator_3On2And2On3_ReturnCorrectResult)
		{
			ServerRationalNumber s1 = ServerRationalNumber("3", "2");
			ServerRationalNumber s2 = ServerRationalNumber("2", "3");
			ServerRationalNumber result = s1 - s2;

			Assert::AreEqual(string("8,33 * 10^-1"), result.ToString());
		}

		//TEST_METHOD(MultiplyOperator_3On2And2On3_ReturnCorrectResult)
		//{
		//	ServerRationalNumber s1 = ServerRationalNumber("3", "2");
		//	ServerRationalNumber s2 = ServerRationalNumber("3", "17");
		//	ServerRationalNumber result = s1 * s2;

		//	Assert::AreEqual(string("0,265"), result.ToString());
		//}

		//TEST_METHOD(DivideOperator_2On3And38On17_ReturnCorrectResult)
		//{
		//	ServerRationalNumber s1 = ServerRationalNumber("2", "3");
		//	ServerRationalNumber s2 = ServerRationalNumber("38", "17");
		//	ServerRationalNumber result = s1 / s2;

		//	Assert::AreEqual(string("0,298"), result.ToString());

		////	result.IncreaseCurrentAccuracy(5);
		//	Assert::AreEqual(string("0,29824561"), result.ToString());
		//}

		TEST_METHOD(EqualEqualOperator_3On2And3On2_True)
		{
			ServerRationalNumber s1 = ServerRationalNumber("3", "2");
			ServerRationalNumber s2 = ServerRationalNumber("3", "2");
			bool result = s1 == s2;
			Assert::AreEqual(true, result);


			s1 = ServerRationalNumber("-3", "2");
			s2 = ServerRationalNumber("-3", "2");
			result = s1 == s2;
			Assert::AreEqual(true, result);

			s1 = ServerRationalNumber("3", "-2");
			s2 = ServerRationalNumber("3", "-2");
			result = s1 == s2;
			Assert::AreEqual(true, result);

			s1 = ServerRationalNumber("-3", "-2");
			s2 = ServerRationalNumber("3", "2");
			result = s1 == s2;
			Assert::AreEqual(true, result);

			s1 = ServerRationalNumber("3", "2");
			s2 = ServerRationalNumber("-3", "-2");
			result = s1 == s2;
			Assert::AreEqual(true, result);

			s1 = ServerRationalNumber("-3", "-2");
			s2 = ServerRationalNumber("-3", "-2");
			result = s1 == s2;
			Assert::AreEqual(true, result);
		}

		TEST_METHOD(EqualEqualOperator_3On2And3On2_False)
		{
			ServerRationalNumber s1 = ServerRationalNumber("-3", "2");
			ServerRationalNumber s2 = ServerRationalNumber("3", "2");
			bool result = s1 == s2;

			Assert::AreEqual(false, result);

			s1 = ServerRationalNumber("3", "-2");
			s2 = ServerRationalNumber("3", "2");
			result = s1 == s2;

			Assert::AreEqual(false, result);

			s1 = ServerRationalNumber("3", "2");
			s2 = ServerRationalNumber("-3", "2");
			result = s1 == s2;

			Assert::AreEqual(false, result);

			s1 = ServerRationalNumber("3", "2");
			s2 = ServerRationalNumber("3", "-2");
			result = s1 == s2;

			Assert::AreEqual(false, result);

			s1 = ServerRationalNumber("-3", "-2");
			s2 = ServerRationalNumber("3", "-2");
			result = s1 == s2;

			Assert::AreEqual(false, result);
		}

		TEST_METHOD(MoreAndLessAndNotEqualOperators_2On3And3On2_ReturnCorrectResult)
		{
			ServerRationalNumber s1 = ServerRationalNumber("2", "3");
			ServerRationalNumber s2 = ServerRationalNumber("3", "2");
			bool result = s1 > s2;

			Assert::AreEqual(false, result);

			result = s2 > s1;
			Assert::AreEqual(true, result);

			result = s2 > s2;
			Assert::AreEqual(false, result);

			result = s2 >= s1;
			Assert::AreEqual(true, result);

			result = s2 >= s2;
			Assert::AreEqual(true, result);

			result = s1 < s2;
			Assert::AreEqual(true, result);

			result = s1 < s1;
			Assert::AreEqual(false, result);

			result = s1 <= s2;
			Assert::AreEqual(true, result);

			result = s1 <= s1;
			Assert::AreEqual(true, result);

			result = s1 != s1;
			Assert::AreEqual(false, result);
		}

#pragma endregion Operators
	};
}