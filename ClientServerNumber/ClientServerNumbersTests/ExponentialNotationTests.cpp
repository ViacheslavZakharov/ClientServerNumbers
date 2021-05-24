#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include "../ClientServerNumbers/ExponentialNotation.h"

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
		static const int MULTIPLY_TEST_CASE_COUNT = 10;
		string testCaseForMultiply[MULTIPLY_TEST_CASE_COUNT][6] =
		{
			{"1", "43", "7", "158", "1,0 * 10^-3", "3"}, // 0,023 * 0,044 = 0,001
			{"2587", "7", "346", "5", "2,5574313 * 10^4", "3"}, // 369,571 * 69,2 = 25 574,313
			{"1", "3", "1", "3", "1,11 * 10^-1", "3"}, // 0,333 * 0,333 = 0,111
			{"-1", "3", "1", "3", "-1,11 * 10^-1", "3"}, // -0,333 * 0,333 = -0,111
			{"1", "3", "-1", "3", "-1,11 * 10^-1", "3"}, // 0,333 * -0,333 = -0,111
			{"-1", "3", "-1", "3", "1,11 * 10^-1", "3"}, // -0,333 * -0,333 = -0,111
			{"400589", "100000", "5008956", "1000000", "2,0066 * 10^1", "3"}, // 4,00589 * 5,008956 = 20,066
			{"400999", "100000", "5009999", "1000000", "2,0090 * 10^1", "3"}, // 4,00999 * 5,009999 = 20,090
			{"108", "1", "5", "1", "5,40000 * 10^2", "3"}, // 108 / 5 = 21,6
			{"108025", "10", "34", "1", "3,67285000 * 10^5", "3"} // 10802,5 / 34 = 317,721
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

		static const int DEVIDE_TEST_CASE_COUNT = 15;
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
			{"588", "1", "3", "1", "1,96 * 10^2", "3"}, // 588,0 / 3,0 = 196
			{"99999", "10000", "1", "1", "1,0 * 10^1", "3"}, // 9,9999 / 1 = 10
			{"50484", "1000", "3", "10", "1,6828 * 10^2", "3"}, // 50,484 / 0,3 = 168,28
			{"108", "1", "5", "1", "2,16 * 10^1", "3"}, // 108 / 5 = 21,6
			{"108", "1", "3", "1", "3,6 * 10^1", "3"}, // 108 / 3 = 36
			{"1085", "10", "34", "1", "3,191", "3"}, // 108,5 / 34 = 3,191
			{"108025", "10", "34", "1", "3,17721 * 10^2", "3"} // 10802,5 / 34 = 317,721
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

		static const int PLUS_TEST_CASE_COUNT = 10;
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
			{"100", "1", "380", "1", "4,80000 * 10^2", "3"} // 100 + 380 = 480
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

#pragma region GetRationalNumberFromPeriod

		static const int RATIONAL_NUMBER_FROM_PERIOD_TEST_CASE_COUNT = 10;
		string testCaseForRationalNumberFromPeriod[RATIONAL_NUMBER_FROM_PERIOD_TEST_CASE_COUNT][5] =
		{								 
			{"56", "8", "3", "5", "5,683333 * 10^1"}, // 56,8(3) точность 5 = 5,683333 * 10^1
			{"5782", "365", "447", "10", "5,7823654474474 * 10^3"}, // проверка с большим периодом и большим количеством чисел перед периодом.
			{"5782", "365", "457", "10", "5,7823654574575 * 10^3"}, // доп проверка с округлением последнего.
			{"506", "7", "3", "5", "5,0673333 * 10^2"}, // проверка с 0 в целой части переходящим в нецелую.
			{"5", "0", "3", "5", "5,03333"}, // 5,0(3) проверка с 0 в цифрах перед периодом.
			{"5", "0000", "3", "10", "5,0000333333"}, // 5,0(3) проверка с 0 в цифрах перед периодом.
			{"5", "", "3", "5", "5,33333"}, // 5,(3) проверка с пустой строкой в цифрах перед периодом.
			{"5", "", "012", "5", "5,01201"}, // 5,(012) проверка с пустой строкой в цифрах перед периодом и нулем в периоде.
			
			{"513", "", "38", "12", "5,13383838383838 * 10^2"},
			{"0", "0", "03", "12", "3,030303030 * 10^-3"},
		};

		TEST_METHOD(GetRationalNumberFromPeriod_CorrectData_CorrectResult)
		{
			for (int i = 0; i < RATIONAL_NUMBER_FROM_PERIOD_TEST_CASE_COUNT; i++) 
			{
				int accuracy = atoi(testCaseForRationalNumberFromPeriod[i][3].c_str());
				ExponentialNotation expWithPeriod = ExponentialNotation(testCaseForRationalNumberFromPeriod[i][0],
					testCaseForRationalNumberFromPeriod[i][1], testCaseForRationalNumberFromPeriod[i][2], accuracy, 1);
				// Проверяем, что создалось корректное экспоненциальное число.
				Assert::AreEqual(string(testCaseForRationalNumberFromPeriod[i][4]), expWithPeriod.ToString());
				RationalNumerics rn = expWithPeriod.GetRationalNumberFromPeriod();
				// Создадим из получившегося рационального числа экспоненциальное и проверим, что результаты совпадают.
				ExponentialNotation newExpNotation = ExponentialNotation(rn, accuracy);
				Assert::AreEqual(string(testCaseForRationalNumberFromPeriod[i][4]), newExpNotation.ToString());
			}
		}

#pragma endregion

#pragma region ConstructorFromPeriod

		static const int CONSTRUCTOR_FROM_PERIOD_TEST_CASE_COUNT = 25;
		string testCaseForConstructorFromPeriod[CONSTRUCTOR_FROM_PERIOD_TEST_CASE_COUNT][7] =
		{//Целая=0 | До периода=пусто | Период=с нулями		| Еще проверим, что _digitsBeforePeriod и _countDigitsBeforePeriod имеют корректные значения.
			{"0", "", "003", "9", "3,003003 * 10^-3",			"0", "0"}, // 0,(003) точность 9 = 3,003003 * 10^-3
			{"0", "", "0031", "11", "3,10031003 * 10^-3",		"1", "1"}, // 0,(0031) точность 10 = 3,10031003 * 10^-3
		 //Целая=0 | До периода=пусто | Период=без нулей
			{"0", "", "3", "8", "3,3333333 * 10^-1",			"0", "0"}, // 0,(3) точность 8 = 3,3333333 * 10^-1
			{"0", "", "3123", "11", "3,1233123312 * 10^-1",		"123", "3"}, // 0,(3123) точность 11 = 3,1233123312 * 10^-1
		 //Целая=0 | До периода=нули | Период=с нулями	
			{"0", "00", "003", "12", "3,0030030 * 10^-5",		"0", "0"}, // 0,00(003) точность 12 = 3,0030030 * 10^-4
			{"0", "00", "03170", "15", "3,17003170032 * 10^-4",	"170", "3"}, // 0,00(03170) точность 15 = 3,17003170031 * 10^-4
		 //Целая=0 | До периода=нули | Период=без нулей
			{"0", "00", "3", "7", "3,3333 * 10^-3",				"0", "0"}, // 0,00(3) точность 7 = 3,3333 * 10^-3
			{"0", "000", "317", "11", "3,1731732 * 10^-4",		"17", "2"}, // 0,000(317) точность 11 = 3,1731732 * 10^-4
		 //Целая=0 | До периода=с нулями | Период=с нулями
			{"0", "020", "03", "9", "2,0030303 * 10^-2",		"0", "1"}, // 0,020(03) точность 9 = 2,0030303 * 10^-2
			{"0", "0270", "0317", "11", "2,700317032 * 10^-2",	"70", "2"}, // 0,0270(0317) точность 11 = 2,700317032 * 10^-2
		 //Целая=0 | До периода=с нулями | Период=без нулей
			{"0", "020", "3", "6", "2,0333 * 10^-2",			"0", "1"}, // 0,020(3) точность 6 = 2,0333 * 10^-2
			{"0", "0270", "317", "9", "2,7031732 * 10^-2",		"70", "2"}, // 0,0270(317) точность 9 = 2,7031732 * 10^-2
		 //Целая=0 | До периода=без нулей | Период=с нулями
			{"0", "20", "03", "8", "2,0030303 * 10^-1",			"0", "1"}, // 0,20(03) точность 8 = 2,0030303 * 10^-1
			{"0", "275", "0317", "10", "2,750317032 * 10^-1",	"75", "2"}, // 0,275(0317) точность 10 = 2,750317032 * 10^-1
		 //Целая=0 | До периода=без нулей | Период=без нулей
			{"0", "27", "38", "7", "2,738384 * 10^-1",			"7", "1"}, // 0,27(38) точность 7 = 2,738384 * 10^-1
		 //Целая != 0 | До периода=пусто | Период=с нулями
			{"5", "", "003", "6", "5,003003",					"0", "0"}, // 5,(003) точность 6 = 5,003003
			{"50", "", "0317", "7", "5,00317032 * 10^1",		"0", "1"}, // 50,(0317) точность 7 = 5,00317032 * 10^1
			{"501", "", "0317", "7", "5,010317032 * 10^2",		"01", "2"}, // 501,(0317) точность 7 = 5,010317032 * 10^2
		 //Целая != 0 | До периода=пусто | Период=без нулей
			{"50", "", "37", "6", "5,0373737 * 10^1",			"0", "1"}, // 50,(37) точность 6 = 5,0373737 * 10^1
		 //Целая != 0 | До периода=нули | Период=с нулями
			{"5", "00", "003", "8", "5,00003003",				"0", "2"}, // 5,00(003) точность 8 = 5,00003003
		 //Целая != 0 | До периода=нули | Период=без нулей
			{"5", "00", "37", "7", "5,0037374",					"0", "2"}, // 5,00(37) точность 7 = 5,0037374
		 //Целая != 0 | До периода=с нулями | Период=с нулями
			{"5", "021", "037", "9", "5,021037037",				"021", "3"}, // 5,021(037) точность 9 = 5,021037037
		 //Целая != 0 | До периода=с нулями | Период=без нулей
			{"5", "021", "37", "7", "5,0213737",				"021", "3"}, // 5,021(37) точность 7 = 5,0213737
		 //Целая != 0 | До периода=без нулей | Период=с нулями
			{"5", "21", "037", "7", "5,2103704",				"21", "2"}, // 5,21(037) точность 7 = 5,2103704
		 //Целая != 0 | До периода=без нулей | Период=без нулей
			{"5", "21", "37", "6", "5,213737",					"21", "2"}, // 5,21(37) точность 6 = 5,213737
		};

		TEST_METHOD(ConstructorFromPeriod_CorrectData_CorrectResult)
		{
			for (int i = 0; i < CONSTRUCTOR_FROM_PERIOD_TEST_CASE_COUNT; i++)
			{
				int accuracy = atoi(testCaseForConstructorFromPeriod[i][3].c_str());
				ExponentialNotation expWithPeriod = ExponentialNotation(testCaseForConstructorFromPeriod[i][0],
					testCaseForConstructorFromPeriod[i][1], testCaseForConstructorFromPeriod[i][2], accuracy, 1);
				// Проверяем, что создалось корректное экспоненциальное число.
				Assert::AreEqual(string(testCaseForConstructorFromPeriod[i][4]), expWithPeriod.ToString());
				// Проверяем, что составляющие части периода также имеют корректные значения.
				Assert::AreEqual(string(testCaseForConstructorFromPeriod[i][2]), expWithPeriod.GetPeriod().ToString());
				Assert::AreEqual(string(testCaseForConstructorFromPeriod[i][5]), expWithPeriod.GetDigitsBeforePeriod().ToString());
				Assert::AreEqual(string(testCaseForConstructorFromPeriod[i][6]), to_string(expWithPeriod.GetCountDigitsBeforePeriod()));
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