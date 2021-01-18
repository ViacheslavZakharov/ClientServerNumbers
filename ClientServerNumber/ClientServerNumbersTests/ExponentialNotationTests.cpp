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
		// Количество знаков для точности по умолчанию.
		const int ACCURACY_DEFAULT = 5;
		/*
		*1) 1 / 43 * 7 / 158
		* 2) 2587 / 7 * 346 / 5
		* 3) 1 / 3 * 1 / 3
		* 4) 400589 / 100000 * 5008956 / 1000000
		* 5) 400999 / 100000 * 5009999 / 1000000
		*/
		// Количество кейсов.
		static const int MULTIPLY_TEST_CASE_COUNT = 5;
		string testCaseForMultiply[MULTIPLY_TEST_CASE_COUNT][6] =
		{
			{"1", "43", "7", "158", "1,0 * 10^-3", "3"},
			{"2587", "7", "346", "5", "2,5574313 * 10^4", "3"},
			{"1", "3", "1", "3", "1,11 * 10^-1", "3"},
			{"400589", "100000", "5008956", "1000000", "2,0066 * 10^1", "3"},
			{"400999", "100000", "5009999", "1000000", "2,0090 * 10^1", "3"}
		};

		static const int DEVIDE_TEST_CASE_COUNT = 6;
		string testCaseForDevide[DEVIDE_TEST_CASE_COUNT][6] =
		{
			{"53834", "1000", "38401", "1000", "1,402", "3"},
			{"4827", "100", "38401", "1000", "1,257", "3"},
			{"834572", "1000", "384", "10", "2,1734 * 10^1", "3"},
			{"5834", "1000", "3489401", "1000", "2,0 * 10^-3", "3"},
			{"583", "100", "348540158", "100000", "1,67 * 10^-3", "5"},
			{"588", "1", "3", "1", "1,96000 * 10^2", "3"}
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