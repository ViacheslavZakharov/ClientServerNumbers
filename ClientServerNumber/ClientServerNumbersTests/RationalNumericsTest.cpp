#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ClientServerNumbers/RationalNumerics.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClientServerNumbersTests
{
	TEST_CLASS(RationalNumericsTest)
	{
	public:
#pragma region Consts

		//  онстанты дл¤ тестировани¤ конструктора.
		const string SMALL_NUMERATOR_STRING_CASE_1 = "5";
		const string SMALL_DENOMINATOR_STRING_CASE_1 = "6";
		const string SMALL_RESULT_STRING_CASE_1 = "5/6";

		const string SMALL_NUMERATOR_STRING_CASE_2 = "-3";
		const string SMALL_DENOMINATOR_STRING_CASE_2 = "7";
		const string SMALL_RESULT_STRING_CASE_2 = "-3/7";

		const string SMALL_NUMERATOR_STRING_CASE_3 = "-9";
		const string SMALL_DENOMINATOR_STRING_CASE_3 = "-17";
		const string SMALL_RESULT_STRING_CASE_3 = "9/17";

		const string BIG_NUMBER_NUMERATOR_STRING_CASE_1 =   "1234567891113";
		const string BIG_NUMBER_DENOMINATOR_STRING_CASE_1 = "1314151617187";
		const string BIG_NUMBER_RESULT_STRING_CASE_1 = "1234567891113/1314151617187";

		const string BIG_NUMBER_NUMERATOR_STRING_CASE_2 =  "-1234567891113";
		const string BIG_NUMBER_DENOMINATOR_STRING_CASE_2 = "1314151617187";
		const string BIG_NUMBER_RESULT_STRING_CASE_2 = "-1234567891113/1314151617187";

		const string BIG_NUMBER_NUMERATOR_STRING_CASE_3 =   "-1234567891113";
		const string BIG_NUMBER_DENOMINATOR_STRING_CASE_3 = "-1314151617187";
		const string BIG_NUMBER_RESULT_STRING_CASE_3 = "1234567891113/1314151617187";

		const string SMALL_FRACTION_NUMERATOR_STRING_CASE_1 = "9";
		const string SMALL_FRACTION_DENOMINATOR_STRING_CASE_1 = "27";
		const string SMALL_FRACTION_RESULT_STRING_CASE_1 = "1/3";

		const string SMALL_FRACTION_NUMERATOR_STRING_CASE_2 = "9";
		const string SMALL_FRACTION_DENOMINATOR_STRING_CASE_2 = "-27";
		const string SMALL_FRACTION_RESULT_STRING_CASE_2 = "-1/3";

		const string BIG_NUMBER_FRACTION_NUMERATOR_STRING_CASE_1 =   "333333333333";
		const string BIG_NUMBER_FRACTION_DENOMINATOR_STRING_CASE_1 = "999999999999";
		const string BIG_NUMBER_FRACTION_RESULT_STRING_CASE_1 = "1/3";

		const string BIG_NUMBER_FRACTION_NUMERATOR_STRING_CASE_2 =   "999999999999";
		const string BIG_NUMBER_FRACTION_DENOMINATOR_STRING_CASE_2 = "333333333333";
		const string BIG_NUMBER_FRACTION_RESULT_STRING_CASE_2 =                 "3";

		//  онстанты дл¤ операторов сравнени¤.
		const string FIRST_COMPARISON_NUMERATOR_STRING_CASE_1 = "9";
		const string FIRST_COMPARISON_DENOMINATOR_STRING_CASE_1 = "27";
		const string SECOND_COMPARISON_NUMERATOR_STRING_CASE_1 = "27";
		const string SECOND_COMPARISON_DENOMINATOR_STRING_CASE_1 = "81";

		const string FIRST_COMPARISON_NUMERATOR_STRING_CASE_2 = "1";
		const string FIRST_COMPARISON_DENOMINATOR_STRING_CASE_2 = "3";
		const string SECOND_COMPARISON_NUMERATOR_STRING_CASE_2 = "-1";
		const string SECOND_COMPARISON_DENOMINATOR_STRING_CASE_2 = "3";

		const string FIRST_COMPARISON_NUMERATOR_STRING_CASE_3 = "-1";
		const string FIRST_COMPARISON_DENOMINATOR_STRING_CASE_3 = "3";
		const string SECOND_COMPARISON_NUMERATOR_STRING_CASE_3 = "1";
		const string SECOND_COMPARISON_DENOMINATOR_STRING_CASE_3 = "3";

		const string FIRST_COMPARISON_NUMERATOR_STRING_CASE_4 = "-1";
		const string FIRST_COMPARISON_DENOMINATOR_STRING_CASE_4 = "3";
		const string SECOND_COMPARISON_NUMERATOR_STRING_CASE_4 = "-1";
		const string SECOND_COMPARISON_DENOMINATOR_STRING_CASE_4 = "3";

		const string FIRST_COMPARISON_NUMERATOR_STRING_CASE_5 = "0";
		const string FIRST_COMPARISON_DENOMINATOR_STRING_CASE_5 = "19";
		const string SECOND_COMPARISON_NUMERATOR_STRING_CASE_5 = "0";
		const string SECOND_COMPARISON_DENOMINATOR_STRING_CASE_5 = "25";

		const string FIRST_COMPARISON_NUMERATOR_STRING_CASE_6 = "3";
		const string FIRST_COMPARISON_DENOMINATOR_STRING_CASE_6 = "4";
		const string SECOND_COMPARISON_NUMERATOR_STRING_CASE_6 = "2";
		const string SECOND_COMPARISON_DENOMINATOR_STRING_CASE_6 = "3";

#pragma endregion Consts

#pragma region Constructor.Tests

		TEST_METHOD(Constructor_NotParameters_ReturnCorrectResult)
		{
			RationalNumerics r1 = RationalNumerics();
			Assert::AreEqual(r1.Sign(), 0);
			Assert::AreEqual(r1 == RationalNumerics::Zero(), true);
		}

		TEST_METHOD(Constructor_DifferentType_ReturnSameResult)
		{
			RationalNumerics r1 = RationalNumerics(BigInteger(SMALL_NUMERATOR_STRING_CASE_1),
				BigInteger(SMALL_DENOMINATOR_STRING_CASE_1));

			RationalNumerics r2 = RationalNumerics(SMALL_NUMERATOR_STRING_CASE_1, SMALL_DENOMINATOR_STRING_CASE_1);
			Assert::AreEqual(r1 == r2, true);
		}

		TEST_METHOD(Constructor_SmallNumber_ReturnCorrectResult)
		{
			RationalNumerics r1(SMALL_NUMERATOR_STRING_CASE_1, SMALL_DENOMINATOR_STRING_CASE_1);
			Assert::AreEqual(r1.Sign(), 1);
			Assert::AreEqual(r1.ToString() == SMALL_RESULT_STRING_CASE_1, true);

			RationalNumerics r2(SMALL_NUMERATOR_STRING_CASE_2, SMALL_DENOMINATOR_STRING_CASE_2);
			Assert::AreEqual(r2.Sign(), -1);
			Assert::AreEqual(r2.ToString() == SMALL_RESULT_STRING_CASE_2, true);

			RationalNumerics r3(SMALL_NUMERATOR_STRING_CASE_3, SMALL_DENOMINATOR_STRING_CASE_3);
			Assert::AreEqual(r3.Sign(), 1);
			Assert::AreEqual(r3.ToString() == SMALL_RESULT_STRING_CASE_3, true);
		}

		TEST_METHOD(Constructor_BigNumber_ReturnCorrectResult)
		{
			RationalNumerics r1(BIG_NUMBER_NUMERATOR_STRING_CASE_1, BIG_NUMBER_DENOMINATOR_STRING_CASE_1);
			Assert::AreEqual(r1.Sign(), 1);
			Assert::AreEqual(r1.ToString() == BIG_NUMBER_RESULT_STRING_CASE_1, true);

			RationalNumerics r2(BIG_NUMBER_NUMERATOR_STRING_CASE_2, BIG_NUMBER_DENOMINATOR_STRING_CASE_2);
			Assert::AreEqual(r2.Sign(), -1);
			Assert::AreEqual(r2.ToString() == BIG_NUMBER_RESULT_STRING_CASE_2, true);

			RationalNumerics r3(BIG_NUMBER_NUMERATOR_STRING_CASE_3, BIG_NUMBER_DENOMINATOR_STRING_CASE_3);
			Assert::AreEqual(r3.Sign(), 1);
			Assert::AreEqual(r3.ToString() == BIG_NUMBER_RESULT_STRING_CASE_3, true);
		}

		TEST_METHOD(Constructor_ZeroDenominator_Exception)
		{
			try
			{
				RationalNumerics r1(BIG_NUMBER_NUMERATOR_STRING_CASE_1, "0");
				Assert::Fail();
			}
			catch (string actualExceptionString)
			{
				string expectedExceptionString = "Divide by zerro exception";
				Assert::AreEqual(actualExceptionString, expectedExceptionString);
			}
		}

		TEST_METHOD(Constructor_SimplifyFraction_ReturnCorrectResult)
		{
			RationalNumerics r1(SMALL_FRACTION_NUMERATOR_STRING_CASE_1, SMALL_FRACTION_DENOMINATOR_STRING_CASE_1);
			Assert::AreEqual(r1.ToString() == SMALL_FRACTION_RESULT_STRING_CASE_1, true);

			RationalNumerics r2(SMALL_FRACTION_NUMERATOR_STRING_CASE_2, SMALL_FRACTION_DENOMINATOR_STRING_CASE_2);
			Assert::AreEqual(r2.ToString() == SMALL_FRACTION_RESULT_STRING_CASE_2, true);

			RationalNumerics r3(BIG_NUMBER_FRACTION_NUMERATOR_STRING_CASE_1, BIG_NUMBER_FRACTION_DENOMINATOR_STRING_CASE_1);
			Assert::AreEqual(r3.ToString() == BIG_NUMBER_FRACTION_RESULT_STRING_CASE_1, true);

			RationalNumerics r4(BIG_NUMBER_FRACTION_NUMERATOR_STRING_CASE_2, BIG_NUMBER_FRACTION_DENOMINATOR_STRING_CASE_2);
			Assert::AreEqual(r4.ToString() == BIG_NUMBER_FRACTION_RESULT_STRING_CASE_2, true);
		}

#pragma endregion Constructor.Tests

#pragma region ComparisonOperators.Tests

		TEST_METHOD(EqualsEqualsOperator_DifferentNumber_CorrectResult)
		{
			RationalNumerics r1(FIRST_COMPARISON_NUMERATOR_STRING_CASE_1, FIRST_COMPARISON_DENOMINATOR_STRING_CASE_1);
			RationalNumerics r2(SECOND_COMPARISON_NUMERATOR_STRING_CASE_1, SECOND_COMPARISON_DENOMINATOR_STRING_CASE_1);
			Assert::AreEqual(r1 == r2, true);

			RationalNumerics r3(FIRST_COMPARISON_NUMERATOR_STRING_CASE_2, FIRST_COMPARISON_DENOMINATOR_STRING_CASE_2);
			RationalNumerics r4(SECOND_COMPARISON_NUMERATOR_STRING_CASE_2, SECOND_COMPARISON_DENOMINATOR_STRING_CASE_2);
			Assert::AreEqual(r3 == r4, false);

			RationalNumerics r5(FIRST_COMPARISON_NUMERATOR_STRING_CASE_3, FIRST_COMPARISON_DENOMINATOR_STRING_CASE_3);
			RationalNumerics r6(SECOND_COMPARISON_NUMERATOR_STRING_CASE_3, SECOND_COMPARISON_DENOMINATOR_STRING_CASE_3);
			Assert::AreEqual(r5 == r6, false);

			RationalNumerics r7(FIRST_COMPARISON_NUMERATOR_STRING_CASE_4, FIRST_COMPARISON_DENOMINATOR_STRING_CASE_4);
			RationalNumerics r8(SECOND_COMPARISON_NUMERATOR_STRING_CASE_4, SECOND_COMPARISON_DENOMINATOR_STRING_CASE_4);
			Assert::AreEqual(r7 == r8, true);

			RationalNumerics r9(FIRST_COMPARISON_NUMERATOR_STRING_CASE_5, FIRST_COMPARISON_DENOMINATOR_STRING_CASE_5);
			RationalNumerics r10(SECOND_COMPARISON_NUMERATOR_STRING_CASE_5, SECOND_COMPARISON_DENOMINATOR_STRING_CASE_5);
			Assert::AreEqual(r9 == r10, true);

			RationalNumerics r11(FIRST_COMPARISON_NUMERATOR_STRING_CASE_6, FIRST_COMPARISON_DENOMINATOR_STRING_CASE_6);
			RationalNumerics r12(SECOND_COMPARISON_NUMERATOR_STRING_CASE_6, SECOND_COMPARISON_DENOMINATOR_STRING_CASE_6);
			Assert::AreEqual(r11 == r12, false);
		}

		TEST_METHOD(LessOperator_DifferentNumber_CorrectResult)
		{
			RationalNumerics r1(FIRST_COMPARISON_NUMERATOR_STRING_CASE_1, FIRST_COMPARISON_DENOMINATOR_STRING_CASE_1);
			RationalNumerics r2(SECOND_COMPARISON_NUMERATOR_STRING_CASE_1, SECOND_COMPARISON_DENOMINATOR_STRING_CASE_1);
			Assert::AreEqual(r1 < r2, false);

			RationalNumerics r3(FIRST_COMPARISON_NUMERATOR_STRING_CASE_2, FIRST_COMPARISON_DENOMINATOR_STRING_CASE_2);
			RationalNumerics r4(SECOND_COMPARISON_NUMERATOR_STRING_CASE_2, SECOND_COMPARISON_DENOMINATOR_STRING_CASE_2);
			Assert::AreEqual(r3 < r4, false);

			RationalNumerics r5(FIRST_COMPARISON_NUMERATOR_STRING_CASE_3, FIRST_COMPARISON_DENOMINATOR_STRING_CASE_3);
			RationalNumerics r6(SECOND_COMPARISON_NUMERATOR_STRING_CASE_3, SECOND_COMPARISON_DENOMINATOR_STRING_CASE_3);
			Assert::AreEqual(r5 < r6, true);

			RationalNumerics r7(FIRST_COMPARISON_NUMERATOR_STRING_CASE_4, FIRST_COMPARISON_DENOMINATOR_STRING_CASE_4);
			RationalNumerics r8(SECOND_COMPARISON_NUMERATOR_STRING_CASE_4, SECOND_COMPARISON_DENOMINATOR_STRING_CASE_4);
			Assert::AreEqual(r7 < r8, false);

			RationalNumerics r9(FIRST_COMPARISON_NUMERATOR_STRING_CASE_5, FIRST_COMPARISON_DENOMINATOR_STRING_CASE_5);
			RationalNumerics r10(SECOND_COMPARISON_NUMERATOR_STRING_CASE_5, SECOND_COMPARISON_DENOMINATOR_STRING_CASE_5);
			Assert::AreEqual(r9 < r10, false);

			RationalNumerics r11(FIRST_COMPARISON_NUMERATOR_STRING_CASE_6, FIRST_COMPARISON_DENOMINATOR_STRING_CASE_6);
			RationalNumerics r12(SECOND_COMPARISON_NUMERATOR_STRING_CASE_6, SECOND_COMPARISON_DENOMINATOR_STRING_CASE_6);
			Assert::AreEqual(r12 < r11, true);
		}

#pragma endregion ComparisonOperators.Tests

#pragma PlusOperator

		static const int PLUS_TEST_CASE_COUNT = 2;
		string testCaseForPlus[PLUS_TEST_CASE_COUNT][7] =
		{
			{"1", "3", "1", "3", "0", "1", "2/3"}, // (1/3 - 0) + 1/3 = 2/3
			{"1", "3", "3", "4", "2", "3", "5/12"} // (1/3 - 2/3) + 3/4 = 5/12
		};
		TEST_METHOD(PlusOperator_DifferentNumber_CorrectResult)
		{
			for (int i = 0; i < PLUS_TEST_CASE_COUNT; i++) {
				RationalNumerics r1(testCaseForPlus[i][0], testCaseForPlus[i][1]);
				RationalNumerics r2(testCaseForPlus[i][2], testCaseForPlus[i][3]);
				r1 = r1 - RationalNumerics(testCaseForPlus[i][4], testCaseForPlus[i][5]);
				RationalNumerics result = r1 + r2;
				Assert::AreEqual(string(testCaseForPlus[i][6]), result.ToString());
			}
		}

#pragma endregion PlusOperator

	};
}