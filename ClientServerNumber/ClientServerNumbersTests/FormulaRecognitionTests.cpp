#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include "../ClientServerNumbers/FormulaRecognition.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClientServerNumbersTests
{
	TEST_CLASS(FormulaRecognitionTests)
	{
	public:

#pragma region ConvertPPN / Tests

		static const int CONVERT_PPN_TEST_CASE_COUNT = 8;
		const string _testCaseForConvertPPN[CONVERT_PPN_TEST_CASE_COUNT][2] =
		{
			// input string									// expected output formula
			{"2+25*29-4",									"2 25 29 *+4 -"},
			{"(8+2*5)/(1+3*2-4)",							"8 2 5 *+1 3 2 *+4 -/"},
			{"(380+20*5)/(10+30*2-40)",						"380 20 5 *+10 30 2 *+40 -/"},
			{"(42+(108/5)*12)/3",							"42 108 5 /12 *+3 /"},
			{"(317/7+5/7)*(3/11)-481/3+(8/7)/(3/5)-8/3",	"317 7 /5 7 /+3 11 /*481 3 /-8 7 /3 5 //+8 3 /-"},
			{"5-2,5(38)+0,(3)*0,(4)",						"5 2,5(38) -0,(3) 0,(4) *+"},
			{"(513,(38)-20,3(8))*(0,0(03)-0,(1))",			"513,(38) 20,3(8) -0,0(03) 0,(1) -*"},
			{"0,(013)*(25/3)-5,(011)/(3/7)",				"0,(013) 25 3 /*5,(011) 3 7 //-"}
		};

		TEST_METHOD(ConvertPPN_CorrectData_CorrectResult)
		{
			for (int i = 0; i < CONVERT_PPN_TEST_CASE_COUNT; i++) {
				string actualResult = FormulaRecognition::ConvertPPN(_testCaseForConvertPPN[i][0]);
				Assert::AreEqual(string(_testCaseForConvertPPN[i][1]), actualResult);
			}
		}

#pragma endregion

#pragma region Calculate / Tests

		static const int CALCULATE_TEST_CASE_COUNT = 8;
		const string _testCaseForCalculate[CALCULATE_TEST_CASE_COUNT][3] =
		{
			// formula										// input string										// expected output formula
			{"2+25*29-4",									"2 25 29 *+4 -",									"7,23000 * 10^2"}, //2+25*29-4 = 723
			{"(8+2*5)/(1+3*2-4)",							"8 2 5 *+1 3 2 *+4 -/",								"6,0"}, //(8+2*5)/(1+3*2-4) = 6
			{"(380+20*5)/(10+30*2-40)",						"380 20 5 *+10 30 2 *+40 -/",						"1,6 * 10^1"}, // (380+20*5)/(10+30*2-40) = 16
			{"(42+(108/5)*12)/3",							"42 108 5 /12 *+3 /",								"1,004 * 10^2"}, // (42+(108/5)*12)/3 = 100,4
			{"(317/7+5/7)*(3/11)-481/3+(8/7)/(3/5)-8/3",	"317 7 /5 7 /+3 11 /*481 3 /-8 7 /3 5 //+8 3 /-",	"-1,48537 * 10^2"}, // (317/7+5/7)*(3/11)-481/3+(8/7)/(3/5)-8/3 = -148,583
			{"5-2,5(38)+0,(3)*0,(4)",						"5 2,5(38) -0,(3) 0,(4) *+",						"2,610"}, // 5 - 2,5(38) + 0,(3) * 0,(4) = 2,610
			{"(513,(38)-20,3(8))*(0,0(03)-0,(1))",			"513,(38) 20,3(8) -0,0(03) 0,(1) -*",				"-5,3244 * 10^1"}, // (513,(38) - 20,3(8)) * (0,0(03) - 0,(1) ) = -53,244
			{"0,(013)*(25/3)-5,(011)/(3/7)",				"0,(013) 25 3 /*5,(011) 3 7 //-",					"-1,1573 * 10^1"} // 0,(013) * (25/3) - 5,(011) / (3/7) = -11,537
		};

		TEST_METHOD(Calculate_CorrectData_CorrectResult)
		{
			for (int i = 0; i < CALCULATE_TEST_CASE_COUNT; i++) {
				auto treeResult = FormulaRecognition::Calculate(_testCaseForCalculate[i][1]);
				auto topResult = treeResult.Top();
				auto resultString = topResult.GetResultOperation().ToString();
				Assert::AreEqual(string(_testCaseForCalculate[i][2]), resultString);
			}
		}

#pragma endregion

	};
}