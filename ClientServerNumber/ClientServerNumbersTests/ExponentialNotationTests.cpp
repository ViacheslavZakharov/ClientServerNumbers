#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include "../ClientServerNumber/ExponentialNotation.h"
#include "../ClientServerNumber/ExponentialNotation.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClientServerNumbersTests
{
	TEST_CLASS(ExponentialNotationTests)
	{
	public:

#pragma region Multiply / Tests

		/*
*1) 1 / 43 * 7 / 158
* 2) 2587 / 7 * 346 / 5
* 3) 1 / 3 * 1 / 3
* 4) 400589 / 100000 * 5008956 / 1000000
* 5) 400999 / 100000 * 5009999 / 1000000
*/
// Количество кейсов.
		static const int MULTIPLY_TEST_CASE_COUNT = 8;
		string testCaseForMultiply[MULTIPLY_TEST_CASE_COUNT][6] =
		{
			{"1", "43", "7", "158", "1,0 * 10^-3", "3"}, // 0,023 * 0,044 = 0,001
			{"2587", "7", "346", "5", "2,5574313 * 10^4", "3"}, // 369,571 * 69,2 = 25 574,313
			{"1", "3", "1", "3", "1,11 * 10^-1", "3"}, // 0,333 * 0,333 = 0,111
			{"-1", "3", "1", "3", "-1,11 * 10^-1", "3"}, // -0,333 * 0,333 = -0,111
			{"1", "3", "-1", "3", "-1,11 * 10^-1", "3"}, // 0,333 * -0,333 = -0,111
			{"-1", "3", "-1", "3", "1,11 * 10^-1", "3"}, // -0,333 * -0,333 = -0,111
			{"400589", "100000", "5008956", "1000000", "2,0066 * 10^1", "3"}, // 4,00589 * 5,008956 = 20,066
			{"400999", "100000", "5009999", "1000000", "2,0090 * 10^1", "3"} // 4,00999 * 5,009999 = 20,090
		};

		TEST_METHOD(MultiplyOperator_CorrectData_CorrectResult)
		{
			ExponentialNotation result = ExponentialNotation();
			for (int i = 0; i < MULTIPLY_TEST_CASE_COUNT; i++) {
				result = GetExponentialNotation(testCaseForMultiply[i][0], testCaseForMultiply[i][1], testCaseForMultiply[i][5])
					* GetExponentialNotation(testCaseForMultiply[i][2], testCaseForMultiply[i][3], testCaseForMultiply[i][5]);
				Assert::AreEqual(string(testCaseForMultiply[i][4]), result.ToString());
			}
		}
#pragma endregion

#pragma region Devide / Tests

		static const int DEVIDE_TEST_CASE_COUNT = 11;
		string testCaseForDevide[DEVIDE_TEST_CASE_COUNT][6] =
		{
			{"53834", "1000", "38401", "1000", "1,402", "3"}, // 53,834 / 38,401 = 1,402
			{"-53834", "1000", "38401", "1000", "-1,402", "3"}, // -53,834 / 38,401 = -1,402
			{"53834", "1000", "-38401", "1000", "-1,402", "3"}, // 53,834 / -38,401 = -1,402
			{"-53834", "1000", "-38401", "1000", "1,402", "3"}, // -53,834 / -38,401 = 1,402
			{"4827", "100", "38401", "1000", "1,257", "3"}, // 48,27 / 38,407 = 1,257
			{"834572", "1000", "384", "10", "2,1734 * 10^1", "3"}, // 834,572 / 38,4 = 21,734
			{"5834", "1000", "3489401", "1000", "2,0 * 10^-3", "3"}, // 5,834 / 3489,401 = 0,002
			{"583", "100", "348540158", "100000", "1,67 * 10^-3", "5"}, //5,83 / 3485,40158 = 0,00167
			{"588", "1", "3", "1", "1,96000 * 10^2", "3"}, // 588,0 / 3,0 = 196
			{"99999", "10000", "1", "1", "1,0 * 10^1", "3"}, // 9,9999 / 1 = 10
			{"50484", "1000", "3", "10", "1,68280 * 10^2", "3"} // 50,484 / 0,3 = 168,280
		};

		TEST_METHOD(DevideOperator_CorrectData_CorrectResult)
		{
			ExponentialNotation result = ExponentialNotation();
			for (int i = 0; i < DEVIDE_TEST_CASE_COUNT; i++) {
				result = GetExponentialNotation(testCaseForDevide[i][0], testCaseForDevide[i][1],
					testCaseForDevide[i][5])
					/ GetExponentialNotation(testCaseForDevide[i][2], testCaseForDevide[i][3], testCaseForDevide[i][5]);
				Assert::AreEqual(string(testCaseForDevide[i][4]), result.ToString());
			}
		}

#pragma endregion

#pragma region Plus / Tests

		static const int PLUS_TEST_CASE_COUNT = 9;
		string testCaseForPlus[PLUS_TEST_CASE_COUNT][6] =
		{
			{"53834", "1000", "38401", "1000", "9,2235 * 10^1", "3"}, // 53,834 + 38,401 = 92,235
			{"4827", "100", "38407", "1000", "8,6677 * 10^1", "3"}, // 48,27 + 38,407 = 86,677
			{"834572", "1000", "384", "10", "8,72972 * 10^2", "3"}, // 834,572 + 38,4 = 872,972
			{"34", "1000", "29", "100", "3,24 * 10^-1", "3"}, // 0,034 + 0,29 = 0,324
			{"1583", "100", "348540158", "100000", "3,50123158 * 10^3", "5"}, //5,83 + 3485,40158 = 0,00167
			{"1", "1000", "9", "1000", "1,0 * 10^-2", "3"}, // 0,001 + 0,009 = 0,01
			{"-1", "1000", "9", "1000", "8,0 * 10^-3", "3"}, // -0,001 + 0,009 = 0,008
			{"-9", "1000", "9", "1000", "0", "3"}, // -0,009 + 0,009 = 0
			{"-9", "1000", "1", "1000", "-8,0 * 10^-3", "3"}, // -0,009 + 0,001 = -0,008
		};

		TEST_METHOD(PlusOperator_CorrectData_CorrectResult)
		{
			ExponentialNotation result = ExponentialNotation();
			for (int i = 0; i < PLUS_TEST_CASE_COUNT; i++) {
				result = GetExponentialNotation(testCaseForPlus[i][0], testCaseForPlus[i][1],
					testCaseForPlus[i][5])
					+ GetExponentialNotation(testCaseForPlus[i][2], testCaseForPlus[i][3], testCaseForPlus[i][5]);
				Assert::AreEqual(string(testCaseForPlus[i][4]), result.ToString());
			}
		}

#pragma endregion

#pragma region Minus / Tests

		static const int MINUS_TEST_CASE_COUNT = 9;
		string testCaseForMinus[MINUS_TEST_CASE_COUNT][6] =
		{
			{"53834", "1000", "38401", "1000", "1,5433 * 10^1", "3"}, // 53,834 - 38,401 = 15,433
			{"4827", "100", "38407", "1000", "9,863", "3"}, // 48,27 - 38,407 = 9,863
			{"834572", "1000", "384", "10", "7,96172 * 10^2", "3"}, // 834,572 - 38,4 = 796,172
			{"34", "1000", "29", "100", "-2,56 * 10^-1", "3"}, // 0,034 - 0,29 = 0,05
			{"583", "100", "348540158", "100000", "-3,47957158 * 10^3", "5"}, //5,83 - 3485,40158 = -3 479,57158
			{"1", "1000", "9", "1000", "-8,0 * 10^-3", "3"}, // 0,001 - 0,009 = -0,008
			{"-1", "1000", "9", "1000", "-1,0 * 10^-2", "3"}, // -0,001 - 0,009 = -0,01
			{"-9", "1000", "-9", "1000", "0", "3"}, // -0,009 - (-0,009) = 0
			{"50333", "1000", "332", "1000", "5,0001 * 10^1", "3"}, // 50,333 - 0,332 = 50,001
		};

		TEST_METHOD(MinusOperator_CorrectData_CorrectResult)
		{
			ExponentialNotation result = ExponentialNotation();
			for (int i = 0; i < MINUS_TEST_CASE_COUNT; i++) {
				result = GetExponentialNotation(testCaseForMinus[i][0], testCaseForMinus[i][1],
					testCaseForMinus[i][5])
					- GetExponentialNotation(testCaseForMinus[i][2], testCaseForMinus[i][3], testCaseForMinus[i][5]);
				Assert::AreEqual(string(testCaseForMinus[i][4]), result.ToString());
			}
		}

#pragma endregion

	private:

		// Получает число в экспоненциальной форме из числителя и знаменателя.
		ExponentialNotation GetExponentialNotation(string numerator, string denominator, string accuracyStr)
		{
			int accuracy = atoi(accuracyStr.c_str());
			RationalNumerics rn = RationalNumerics(numerator, denominator);
			return ExponentialNotation(rn, accuracy);
		}
	};
}