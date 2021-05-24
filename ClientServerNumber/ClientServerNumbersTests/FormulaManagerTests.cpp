#include "stdafx.h"
#include "CppUnitTest.h"
#include <vector>
#include "../ClientServerNumbers/FormulaManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClientServerNumbersTests
{
	TEST_CLASS(FormulaManagerTests)
	{
	public:

#pragma region GetIncreasedAccuracyResult / Tests

		static const int INCREACE_ACCURACY_TEST_CASE_COUNT = 1;
		const string _testCaseForIncreaseAccuracy[INCREACE_ACCURACY_TEST_CASE_COUNT][3] =
		{
			// input string									// expected output formula
			{"1 / 3 + 5 / 7 - 8 / 3 * 5", "6",									"-1,228571 * 10^1"},
			//{"(513,(38)-20,3(8))*(0,0(03)-0,(1))", "13",			"-5,32832925211722 * 10^1"},
		};

		TEST_METHOD(GetIncreasedAccuracyResult_CorrectData_CorrectResult)
		{
			FormulaManager formulaManager = FormulaManager();
			for (int i = 0; i < INCREACE_ACCURACY_TEST_CASE_COUNT; i++) {
				formulaManager.Calculate(_testCaseForIncreaseAccuracy[i][0]);
				auto increaseResult = formulaManager.GetIncreasedAccuracyResult(atoi(_testCaseForIncreaseAccuracy[i][1].c_str()));
				int accuracy = formulaManager.GetRealAccuracyResult();
				Assert::AreEqual(accuracy, atoi(_testCaseForIncreaseAccuracy[i][1].c_str()));
				Assert::AreEqual(string(_testCaseForIncreaseAccuracy[i][2]), increaseResult);
			}
		}

#pragma endregion
	};
}