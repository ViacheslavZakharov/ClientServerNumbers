#pragma once
#include "FormulaRecognition.h"
#include <cassert>

const int CONVERT_PPN_TEST_CASE_COUNT = 5;
const string _testCaseForConvertPPN[CONVERT_PPN_TEST_CASE_COUNT][2] =
{
	// input string									// expected output formula
	{"2+25*29-4",									"2 25 29 *+4 -"},
	{"(8+2*5)/(1+3*2-4)",							"8 2 5 *+1 3 2 *+4 -/"},
	{"(380+20*5)/(10+30*2-40)",						"380 20 5 *+10 30 2 *+40 -/"},
	{"(42+(108/5)*12)/3",							"42 108 5 /12 *+3 /"},
	{"(317/7+5/7)*(3/11)-481/3+(8/7)/(3/5)-8/3",	"317 7 /5 7 /+3 11 /*481 3 /-8 7 /3 5 //+8 3 /-"}
};

const int CALCULATE_TEST_CASE_COUNT = 5;
const string _testCaseForCalculate[CALCULATE_TEST_CASE_COUNT][2] =
{
	// input string										// expected output formula
	{"2 25 29 *+4 -",									"7,23000 * 10^2"}, //2+25*29-4 = 723
	{"8 2 5 *+1 3 2 *+4 -/",							"6,0"}, //(8+2*5)/(1+3*2-4) = 6
	{"380 20 5 *+10 30 2 *+40 -/",						"1,6 * 10^1"}, // (380+20*5)/(10+30*2-40) = 16
	{"42 108 5 /12 *+3 /",								"1,004 * 10^2"}, // (42+(108/5)*12)/3 = 100,4
	{"317 7 /5 7 /+3 11 /*481 3 /-8 7 /3 5 //+8 3 /-",	"-1,48537 * 10^2"} // (317/7+5/7)*(3/11)-481/3+(8/7)/(3/5)-8/3 = -148,583
};

class FormulaRecognitionTests
{
public:

	static void AssertConvertPPN() 
	{
		for (int i = 0; i < CONVERT_PPN_TEST_CASE_COUNT; i++) {
			string actualResult = FormulaRecognition::ConvertPPN(_testCaseForConvertPPN[i][0]);
			assert(_testCaseForConvertPPN[i][1] == actualResult);
		}
	}

	static void AssertCalculate() 
	{
		for (int i = 0; i < CALCULATE_TEST_CASE_COUNT; i++) {
			auto treeResult = FormulaRecognition::Calculate(_testCaseForCalculate[i][0]);
			auto topResult = treeResult.Top();
			auto resultString = topResult.GetResultOperation().ToString();
			cout << "--------------------------";
			treeResult.Print();
			cout<< "\n";
			assert(_testCaseForCalculate[i][1] == resultString);
		}
	}
};
