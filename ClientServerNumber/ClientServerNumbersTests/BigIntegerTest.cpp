#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ClientServerNumbers/BigInteger.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClientServerNumbersTests
{		
	TEST_CLASS(BigIntegerTest)
	{
	public:
#pragma region Consts
		// Константы для проверки работы конструкторов и операторов сравнения.
		const string SHORT_POSITIVE_STRING = "1234";
		const string OTHER_SHORT_POSITIVE_STRING = "4";
		const string OTHER2_SHORT_POSITIVE_STRING = "5";

		const string LONG_POSITIVE_STRING =		  "1234567891011121314";
		const string OTHER_LONG_POSITIVE_STRING = "2222222222222222";
		const string OTHER2_LONG_POSITIVE_STRING= "1000000000000004";
		const string OTHER3_LONG_POSITIVE_STRING = "1234567891011121315";
		
		const int SHORT_POSITIVE_INT = 1234;
		const long long LONG_POSITIVE_LONG = 1234567891011121314L;

		const string SHORT_NEGATIVE_STRING = "-1234";
		const string LONG_NEGATIVE_STRING = "-1234567891011121314";

		const string LONG_DIFFERENT_COUNT_ZEROS_STRING = "1000000004";
		const string LONG_OTHER_DIFFERENT_COUNT_ZEROS_STRING = "100000000000000004";

		// Константы для сложения.
		const string FIRST_SUMMAND_STRING_1_CASE =   "2222222222222222";
		const string SECOND_SUMMAND_STRING_1_CASE =  "1000000000000004";
		const string ADDITION_RESULT_STRING_1_CASE = "3222222222222226";

		const string FIRST_SUMMAND_STRING_2_CASE =     "22222222222228";
		const string SECOND_SUMMAND_STRING_2_CASE =  "1000000000000004";
		const string ADDITION_RESULT_STRING_2_CASE = "1022222222222232";

		const string FIRST_SUMMAND_STRING_3_CASE =   "2222222222222222";
		const string SECOND_SUMMAND_STRING_3_CASE = "-1000000000000004";
		const string ADDITION_RESULT_STRING_3_CASE = "1222222222222218";

		const string FIRST_SUMMAND_STRING_4_CASE =   "2222222222222222";
		const string SECOND_SUMMAND_STRING_4_CASE =               "104";
		const string ADDITION_RESULT_STRING_4_CASE = "2222222222222326";

		const string FIRST_SUMMAND_STRING_5_CASE =   "2222222222222222";
		const string SECOND_SUMMAND_STRING_5_CASE =              "-104";
		const string ADDITION_RESULT_STRING_5_CASE = "2222222222222118";

		const string FIRST_SUMMAND_STRING_6_CASE =   "109";
		const string SECOND_SUMMAND_STRING_6_CASE =  "104";
		const string ADDITION_RESULT_STRING_6_CASE = "213";

		// Константы для вычитания.
		const string MINUED_STRING_1_CASE =              "2222222222222222";
		const string SUBTRACTABLE_STRING_1_CASE =        "1000000000000001";
		const string SUBTRACTION_RESULT_STRING_1_CASE =  "1222222222222221";

		const string MINUED_STRING_2_CASE =              "2222222222222228";
		const string SUBTRACTABLE_STRING_2_CASE =        "1000060000004";
		const string SUBTRACTION_RESULT_STRING_2_CASE =  "2221222162222224";

		const string MINUED_STRING_3_CASE =				  "2222222222222222";
		const string SUBTRACTABLE_STRING_3_CASE =		 "-1000000000000004";
		const string SUBTRACTION_RESULT_STRING_3_CASE =   "3222222222222226";

		const string MINUED_STRING_4_CASE =			    "2222222222222222";
		const string SUBTRACTABLE_STRING_4_CASE =				     "102";
		const string SUBTRACTION_RESULT_STRING_4_CASE = "2222222222222120";

		const string MINUED_STRING_5_CASE =				"2222222222222222";
		const string SUBTRACTABLE_STRING_5_CASE =				    "-104";
		const string SUBTRACTION_RESULT_STRING_5_CASE = "2222222222222326";

		const string MINUED_STRING_6_CASE =			  "109";
		const string SUBTRACTABLE_STRING_6_CASE =	  "104";
		const string SUBTRACTION_RESULT_STRING_6_CASE = "5";

		// Константы для умножения.
		const string FIRST_MULTIPLIER_STRING_1_CASE =      "2222222222282222";
		const string SECOND_MULTIPLIER_STRING_1_CASE =     "1000000000040001";
		const string MULTIPLICATION_RESULT_STRING_1_CASE = "2222222222371113111113511162222";

		const string FIRST_MULTIPLIER_STRING_2_CASE =       "2222222222222222";
		const string SECOND_MULTIPLIER_STRING_2_CASE =					   "8";
		const string MULTIPLICATION_RESULT_STRING_2_CASE = "17777777777777776";

		const string FIRST_MULTIPLIER_STRING_3_CASE =		"-2222222222222222";
		const string SECOND_MULTIPLIER_STRING_3_CASE =                      "8";
		const string MULTIPLICATION_RESULT_STRING_3_CASE = "-17777777777777776";

		const string FIRST_MULTIPLIER_STRING_4_CASE =       "-2222222222222222";
		const string SECOND_MULTIPLIER_STRING_4_CASE =				       "-8";
		const string MULTIPLICATION_RESULT_STRING_4_CASE = "17777777777777776";

		const string FIRST_MULTIPLIER_STRING_5_CASE =       "2";
		const string SECOND_MULTIPLIER_STRING_5_CASE =      "8";
		const string MULTIPLICATION_RESULT_STRING_5_CASE = "16";

		// Константы для деления.
		const string DIVIDEND_STRING_1_CASE =      "2222222222282222";
		const string DEVISOR_STRING_1_CASE =       "1000000000040001";
		const string DEVIDE_RESULT_STRING_1_CASE =                "2";

		const string DIVIDEND_STRING_2_CASE =      "2222222222222222";
		const string DEVISOR_STRING_2_CASE =                      "2";
		const string DEVIDE_RESULT_STRING_2_CASE = "1111111111111111";

		const string DIVIDEND_STRING_3_CASE =	   "-2222222222222222";
		const string DEVISOR_STRING_3_CASE =					   "2";
		const string DEVIDE_RESULT_STRING_3_CASE = "-1111111111111111";

		const string DIVIDEND_STRING_4_CASE =	  "-2222222222222222";
		const string DEVISOR_STRING_4_CASE =					 "-2";
		const string DEVIDE_RESULT_STRING_4_CASE = "1111111111111111";

		const string DIVIDEND_STRING_5_CASE =      "8";
		const string DEVISOR_STRING_5_CASE =       "4";
		const string DEVIDE_RESULT_STRING_5_CASE = "2";

		// Константы для взятия остатка от деления.
		const string DIVIDEND_FOR_REMINDER_STRING_1_CASE = "2222222222282222";
		const string DEVISOR_FOR_REMINDER_STRING_1_CASE =  "1000000000040001";
		const string REMIND_RESULT_STRING_1_CASE =          "222222222202220";

		const string DIVIDEND_FOR_REMINDER_STRING_2_CASE = "2222222222222222";
		const string DEVISOR_FOR_REMINDER_STRING_2_CASE =				  "2";
		const string REMIND_RESULT_STRING_2_CASE =				          "0";

		const string DIVIDEND_FOR_REMINDER_STRING_3_CASE = "-2222222222282222";
		const string DEVISOR_FOR_REMINDER_STRING_3_CASE =   "1000000000040001";
		const string REMIND_RESULT_STRING_3_CASE =			 "222222222202220";

		const string DIVIDEND_FOR_REMINDER_STRING_4_CASE = "-2222222222282222";
		const string DEVISOR_FOR_REMINDER_STRING_4_CASE =  "-1000000000040001";
		const string REMIND_RESULT_STRING_4_CASE =			 "222222222202220";

		const string DIVIDEND_FOR_REMINDER_STRING_5_CASE = "9";
		const string DEVISOR_FOR_REMINDER_STRING_5_CASE =  "5";
		const string REMIND_RESULT_STRING_5_CASE =		   "4";

		// Константы для наибольшего общего делителя.
		const string FIRST_GREATEST_COMMON_DIVISOR_STRING_1_CASE =  "2222222222222222";
		const string SECOND_GREATEST_COMMON_DIVISOR_STRING_1_CASE = "9999999999999999";
		const string GREATEST_COMMON_DIVISOR_RESULT_STRING_1_CASE =	"1111111111111111";

		const string FIRST_GREATEST_COMMON_DIVISOR_STRING_2_CASE = "2222222222222222";
		const string SECOND_GREATEST_COMMON_DIVISOR_STRING_2_CASE =				 "11";
		const string GREATEST_COMMON_DIVISOR_RESULT_STRING_2_CASE =				 "11";

		const string FIRST_GREATEST_COMMON_DIVISOR_STRING_3_CASE = "-2222222222222222";
		const string SECOND_GREATEST_COMMON_DIVISOR_STRING_3_CASE = "9999999999999999";
		const string GREATEST_COMMON_DIVISOR_RESULT_STRING_3_CASE = "1111111111111111";

		const string FIRST_GREATEST_COMMON_DIVISOR_STRING_4_CASE =  "-2222222222222222";
		const string SECOND_GREATEST_COMMON_DIVISOR_STRING_4_CASE = "-9999999999999999";
		const string GREATEST_COMMON_DIVISOR_RESULT_STRING_4_CASE =  "1111111111111111";

		const string FIRST_GREATEST_COMMON_DIVISOR_STRING_5_CASE =  "27";
		const string SECOND_GREATEST_COMMON_DIVISOR_STRING_5_CASE = "18";
		const string GREATEST_COMMON_DIVISOR_RESULT_STRING_5_CASE =  "9";

		// Константы для возведения в положительную целую степень.
		const string NUMBER_FOR_POW_STRING_1_CASE = "10";
		const string DEGREE_FOR_POW_STRING_1_CASE = "10";
		const string POW_RESULT_STRING_1_CASE = "10000000000";

		const string NUMBER_FOR_POW_STRING_2_CASE = "10";
		const string DEGREE_FOR_POW_STRING_2_CASE = "-10";
		const string POW_RESULT_STRING_2_CASE = "10000000000";

		const string NUMBER_FOR_POW_STRING_3_CASE = "-10";
		const string DEGREE_FOR_POW_STRING_3_CASE = "10";
		const string POW_RESULT_STRING_3_CASE = "10000000000";

		const string NUMBER_FOR_POW_STRING_4_CASE = "-10";
		const string DEGREE_FOR_POW_STRING_4_CASE = "3";
		const string POW_RESULT_STRING_4_CASE = "-1000";

		const string NUMBER_FOR_POW_STRING_5_CASE = "2";
		const string DEGREE_FOR_POW_STRING_5_CASE = "10";
		const string POW_RESULT_STRING_5_CASE = "1024";

#pragma endregion Consts

#pragma region Constructor.Tests

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

#pragma endregion Constructor.Tests

#pragma region ComparisonOperators.Tests

		TEST_METHOD(EqualsEqualsOperator_DifferentNumber_CorrectResult)
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

			BigInteger b11(SHORT_POSITIVE_STRING);
			BigInteger b12(SHORT_POSITIVE_INT);
			Assert::AreEqual(b11 == b12, true);

			Assert::AreEqual(BigInteger(LONG_DIFFERENT_COUNT_ZEROS_STRING) == BigInteger(LONG_OTHER_DIFFERENT_COUNT_ZEROS_STRING), false);
		}

		TEST_METHOD(UnaryPlusOperator_CorrectData_CorrectResult)
		{
			BigInteger b1(SHORT_POSITIVE_STRING);
			BigInteger b2 = +b1;
			Assert::AreEqual(b1 == b2, true);
			Assert::AreEqual(b1.Sign() == b2.Sign(), true);
			Assert::AreEqual(b1.Sign() == 1, true);
			Assert::AreEqual(b1.ToString() == b2.ToString(), true);

			BigInteger b3(LONG_POSITIVE_STRING);
			BigInteger b4 = +b3;
			Assert::AreEqual(b3 == b4, true);
			Assert::AreEqual(b3.Sign() == b4.Sign(), true);
			Assert::AreEqual(b3.Sign() == 1, true);
			Assert::AreEqual(b3.ToString() == b4.ToString(), true);
		}

		TEST_METHOD(UnaryMinusOperator_CorrectData_CorrectResult)
		{
			BigInteger b1(SHORT_POSITIVE_STRING);
			BigInteger b2 = -b1;
			Assert::AreEqual(b1 == b2, false);
			Assert::AreEqual(b1.Sign() == b2.Sign(), false);
			Assert::AreEqual(b1.Sign() == 1, true);
			Assert::AreEqual(b2.Sign() == -1, true);
			Assert::AreEqual(b1.ToString() == b2.ToString(), false);
			Assert::AreEqual(b1.ToString().length() == b2.ToString().length(), false);

			BigInteger b3(LONG_POSITIVE_STRING);
			BigInteger b4 = -b3;
			Assert::AreEqual(b3 == b4, false);
			Assert::AreEqual(b3.Sign() == b4.Sign(), false);
			Assert::AreEqual(b3.Sign() == 1, true);
			Assert::AreEqual(b4.Sign() == -1, true);
			Assert::AreEqual(b3.ToString() == b4.ToString(), false);
			Assert::AreEqual(b1.ToString().length() == b2.ToString().length(), false);
		}

		TEST_METHOD(LessOperator_DifferentNumber_CorrectResult)
		{
			BigInteger b1(SHORT_POSITIVE_STRING);
			BigInteger b2(OTHER_SHORT_POSITIVE_STRING);
			Assert::AreEqual(b2 < b1, true);

			BigInteger b3(SHORT_POSITIVE_STRING);
			BigInteger b4(SHORT_POSITIVE_STRING);
			Assert::AreEqual(b3 < b4, false);

			BigInteger b5(LONG_POSITIVE_STRING);
			BigInteger b6(OTHER_LONG_POSITIVE_STRING);
			Assert::AreEqual(b6 < b5, true);

			BigInteger b7(LONG_POSITIVE_STRING);
			BigInteger b8(LONG_NEGATIVE_STRING);
			Assert::AreEqual(b8 < b7, true);

			BigInteger b9(SHORT_NEGATIVE_STRING);
			BigInteger b10(LONG_NEGATIVE_STRING);
			Assert::AreEqual(b10 < b9, true);

			BigInteger b11(SHORT_POSITIVE_STRING);
			BigInteger b12(LONG_POSITIVE_STRING);
			Assert::AreEqual(b11 < b12, true);
		}

		TEST_METHOD(MoreOperator_DifferentNumber_CorrectResult)
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

			BigInteger b11(SHORT_POSITIVE_STRING);
			BigInteger b12(LONG_POSITIVE_STRING);
			Assert::AreEqual(b12 > b11, true);

		}

		TEST_METHOD(MoreOrEqualOperator_DifferentNumber_CorrectResult)
		{
			BigInteger b1(SHORT_POSITIVE_STRING);
			BigInteger b2(OTHER_SHORT_POSITIVE_STRING);
			Assert::AreEqual(b1 >= b2, true);

			Assert::AreEqual(b1 >= b1, true);

			BigInteger b3(LONG_POSITIVE_STRING);
			BigInteger b4(OTHER3_LONG_POSITIVE_STRING);
			Assert::AreEqual(b3 >= b4, false);

			BigInteger b5(LONG_POSITIVE_STRING);
			BigInteger b6(OTHER_LONG_POSITIVE_STRING);
			Assert::AreEqual(b5 >= b6, true);

			BigInteger b7(LONG_POSITIVE_STRING);
			BigInteger b8(LONG_NEGATIVE_STRING);
			Assert::AreEqual(b7 >= b8, true);

			BigInteger b9(SHORT_NEGATIVE_STRING);
			BigInteger b10(LONG_NEGATIVE_STRING);
			Assert::AreEqual(b9 >= b10, true);

			BigInteger b11(SHORT_POSITIVE_STRING);
			BigInteger b12(LONG_POSITIVE_STRING);
			Assert::AreEqual(b12 >= b11, true);

			Assert::AreEqual(b12 >= b12, true);
		}

		TEST_METHOD(LessOrEqualOperator_DifferentNumber_CorrectResult)
		{
			BigInteger b1(SHORT_POSITIVE_STRING);
			BigInteger b2(OTHER_SHORT_POSITIVE_STRING);
			Assert::AreEqual(b2 <= b1, true);

			Assert::AreEqual(b1 <= b1, true);

			BigInteger b3(LONG_POSITIVE_STRING);
			BigInteger b4(OTHER3_LONG_POSITIVE_STRING);
			Assert::AreEqual(b4 <= b3, false);

			BigInteger b5(LONG_POSITIVE_STRING);
			BigInteger b6(OTHER_LONG_POSITIVE_STRING);
			Assert::AreEqual(b6 <= b5, true);

			BigInteger b7(LONG_POSITIVE_STRING);
			BigInteger b8(LONG_NEGATIVE_STRING);
			Assert::AreEqual(b8 <= b7, true);

			BigInteger b9(SHORT_NEGATIVE_STRING);
			BigInteger b10(LONG_NEGATIVE_STRING);
			Assert::AreEqual(b10 <= b9, true);

			BigInteger b11(SHORT_POSITIVE_STRING);
			BigInteger b12(LONG_POSITIVE_STRING);
			Assert::AreEqual(b11 <= b12, true);

			Assert::AreEqual(b12 <= b12, true);
		}

		TEST_METHOD(NotEqualOperator_DifferentNumber_CorrectResult)
		{
			BigInteger b1(SHORT_POSITIVE_STRING);
			BigInteger b2(OTHER_SHORT_POSITIVE_STRING);
			Assert::AreEqual(b2 != b1, true);

			Assert::AreEqual(b1 != b1, false);

			BigInteger b3(LONG_POSITIVE_STRING);
			BigInteger b4(OTHER3_LONG_POSITIVE_STRING);
			Assert::AreEqual(b4 != b3, true);

			Assert::AreEqual(b4 != b4, false);
		}

#pragma endregion ComparisonOperators.Tests

#pragma region ArithmeticOperators.Tests

		TEST_METHOD(PlusOperator_DifferentNumber_CorrectResult)
		{
			BigInteger b1(FIRST_SUMMAND_STRING_1_CASE);
			BigInteger b2(SECOND_SUMMAND_STRING_1_CASE);
			Assert::AreEqual(b1 + b2 == BigInteger(ADDITION_RESULT_STRING_1_CASE), true);

			BigInteger b3(FIRST_SUMMAND_STRING_2_CASE);
			BigInteger b4(SECOND_SUMMAND_STRING_2_CASE);
			Assert::AreEqual(b3 + b4 == BigInteger(ADDITION_RESULT_STRING_2_CASE), true);

			BigInteger b5(FIRST_SUMMAND_STRING_3_CASE);
			BigInteger b6(SECOND_SUMMAND_STRING_3_CASE);
			Assert::AreEqual(b5 + b6 == BigInteger(ADDITION_RESULT_STRING_3_CASE), true);

			BigInteger b7(FIRST_SUMMAND_STRING_4_CASE);
			BigInteger b8(SECOND_SUMMAND_STRING_4_CASE);
			Assert::AreEqual(b7 + b8 == BigInteger(ADDITION_RESULT_STRING_4_CASE), true);

			BigInteger b9(FIRST_SUMMAND_STRING_5_CASE);
			BigInteger b10(SECOND_SUMMAND_STRING_5_CASE);
			Assert::AreEqual(b9 + b10 == BigInteger(ADDITION_RESULT_STRING_5_CASE), true);

			BigInteger b11(FIRST_SUMMAND_STRING_6_CASE);
			BigInteger b12(SECOND_SUMMAND_STRING_6_CASE);
			Assert::AreEqual(b11 + b12 == BigInteger(ADDITION_RESULT_STRING_6_CASE), true);
		}

		TEST_METHOD(PlusPlusOperator_BigNumber_CorrectResult)
		{
			BigInteger b1(LONG_POSITIVE_STRING);
			b1++;
			Assert::AreEqual( b1 == BigInteger(OTHER3_LONG_POSITIVE_STRING), true);
		}

		TEST_METHOD(MinusMinusOperator_DifferentNumber_CorrectResult)
		{
			BigInteger b1(OTHER3_LONG_POSITIVE_STRING);
			b1--;
			Assert::AreEqual(b1 == BigInteger(LONG_POSITIVE_STRING), true);
		}

		TEST_METHOD(MinusOperator_DifferentNumber_CorrectResult)
		{
			BigInteger b1(MINUED_STRING_1_CASE);
			BigInteger b2(SUBTRACTABLE_STRING_1_CASE);
			Assert::AreEqual(b1 - b2 == BigInteger(SUBTRACTION_RESULT_STRING_1_CASE), true);

			BigInteger b3(MINUED_STRING_2_CASE);
			BigInteger b4(SUBTRACTABLE_STRING_2_CASE);
			Assert::AreEqual(b3 - b4 == BigInteger(SUBTRACTION_RESULT_STRING_2_CASE), true);

			BigInteger b5(MINUED_STRING_3_CASE);
			BigInteger b6(SUBTRACTABLE_STRING_3_CASE);
			Assert::AreEqual(b5 - b6 == BigInteger(SUBTRACTION_RESULT_STRING_3_CASE), true);

			BigInteger b7(MINUED_STRING_4_CASE);
			BigInteger b8(SUBTRACTABLE_STRING_4_CASE);
			Assert::AreEqual(b7 - b8 == BigInteger(SUBTRACTION_RESULT_STRING_4_CASE), true);

			BigInteger b9(MINUED_STRING_5_CASE);
			BigInteger b10(SUBTRACTABLE_STRING_5_CASE);
			Assert::AreEqual(b9 - b10 == BigInteger(SUBTRACTION_RESULT_STRING_5_CASE), true);

			BigInteger b11(MINUED_STRING_6_CASE);
			BigInteger b12(SUBTRACTABLE_STRING_6_CASE);
			Assert::AreEqual(b11 - b12 == BigInteger(SUBTRACTION_RESULT_STRING_6_CASE), true);

		}

		TEST_METHOD(MultiplyOperator_DifferentNumber_CorrectResult)
		{
			BigInteger b1(FIRST_MULTIPLIER_STRING_1_CASE);
			BigInteger b2(SECOND_MULTIPLIER_STRING_1_CASE);
			Assert::AreEqual(b1 * b2 == BigInteger(MULTIPLICATION_RESULT_STRING_1_CASE), true);

			BigInteger b3(FIRST_MULTIPLIER_STRING_2_CASE);
			BigInteger b4(SECOND_MULTIPLIER_STRING_2_CASE);
			Assert::AreEqual(b3 * b4 == BigInteger(MULTIPLICATION_RESULT_STRING_2_CASE), true);

			BigInteger b5(FIRST_MULTIPLIER_STRING_3_CASE);
			BigInteger b6(SECOND_MULTIPLIER_STRING_3_CASE);
			Assert::AreEqual(b5 * b6 == BigInteger(MULTIPLICATION_RESULT_STRING_3_CASE), true);

			BigInteger b7(FIRST_MULTIPLIER_STRING_4_CASE);
			BigInteger b8(SECOND_MULTIPLIER_STRING_4_CASE);
			Assert::AreEqual(b7 * b8 == BigInteger(MULTIPLICATION_RESULT_STRING_4_CASE), true);

			BigInteger b9(FIRST_MULTIPLIER_STRING_5_CASE);
			BigInteger b10(SECOND_MULTIPLIER_STRING_5_CASE);
			Assert::AreEqual(b9 * b10 == BigInteger(MULTIPLICATION_RESULT_STRING_5_CASE), true);
		}

		TEST_METHOD(DivideOperator_DifferentNumber_CorrectResult)
		{
			BigInteger b1(DIVIDEND_STRING_1_CASE);
			BigInteger b2(DEVISOR_STRING_1_CASE);
			Assert::AreEqual(b1 / b2 == BigInteger(DEVIDE_RESULT_STRING_1_CASE), true);

			BigInteger b3(DIVIDEND_STRING_2_CASE);
			BigInteger b4(DEVISOR_STRING_2_CASE);
			Assert::AreEqual(b3 / b4 == BigInteger(DEVIDE_RESULT_STRING_2_CASE), true);

			BigInteger b5(DIVIDEND_STRING_3_CASE);
			BigInteger b6(DEVISOR_STRING_3_CASE);
			Assert::AreEqual(b5 / b6 == BigInteger(DEVIDE_RESULT_STRING_3_CASE), true);

			BigInteger b7(DIVIDEND_STRING_4_CASE);
			BigInteger b8(DEVISOR_STRING_4_CASE);
			Assert::AreEqual(b7 / b8 == BigInteger(DEVIDE_RESULT_STRING_4_CASE), true);

			BigInteger b9(DIVIDEND_STRING_5_CASE);
			BigInteger b10(DEVISOR_STRING_5_CASE);
			Assert::AreEqual(b9 / b10 == BigInteger(DEVIDE_RESULT_STRING_5_CASE), true);
		}

		TEST_METHOD(DivideOperator_DivideByZero_Exception)
		{
			BigInteger b1(DIVIDEND_STRING_1_CASE);
			try 
			{
				b1 / BigInteger();
				Assert::Fail();
			}
			catch (string actualExceptionString)
			{
				string expectedExceptionString = "Divide by zerro exception";
				Assert::AreEqual(actualExceptionString, expectedExceptionString);
			}
		}

		TEST_METHOD(RemindOperator_DifferentNumber_CorrectResult)
		{
			BigInteger b1(DIVIDEND_FOR_REMINDER_STRING_1_CASE);
			BigInteger b2(DEVISOR_FOR_REMINDER_STRING_1_CASE);
			Assert::AreEqual(b1 % b2 == BigInteger(REMIND_RESULT_STRING_1_CASE), true);

			BigInteger b3(DIVIDEND_FOR_REMINDER_STRING_2_CASE);
			BigInteger b4(DEVISOR_FOR_REMINDER_STRING_2_CASE);
			Assert::AreEqual(b3 % b4 == BigInteger(REMIND_RESULT_STRING_2_CASE), true);

			BigInteger b5(DIVIDEND_FOR_REMINDER_STRING_3_CASE);
			BigInteger b6(DEVISOR_FOR_REMINDER_STRING_3_CASE);
			Assert::AreEqual(b5 % b6 == BigInteger(REMIND_RESULT_STRING_3_CASE), true);

			BigInteger b7(DIVIDEND_FOR_REMINDER_STRING_4_CASE);
			BigInteger b8(DEVISOR_FOR_REMINDER_STRING_4_CASE);
			Assert::AreEqual(b7 % b8 == BigInteger(REMIND_RESULT_STRING_4_CASE), true);

			BigInteger b9(DIVIDEND_FOR_REMINDER_STRING_5_CASE);
			BigInteger b10(DEVISOR_FOR_REMINDER_STRING_5_CASE);
			Assert::AreEqual(b9 % b10 == BigInteger(REMIND_RESULT_STRING_5_CASE), true);
		}

#pragma endregion ArithmeticOperators.Tests

#pragma region PubblicMethod.Tests

		TEST_METHOD(Odd_DifferentNumber_CorrectResult)
		{
			BigInteger b1(LONG_POSITIVE_STRING);
			Assert::AreEqual(b1.Odd(), false);
			
			BigInteger b2(OTHER3_LONG_POSITIVE_STRING);
			Assert::AreEqual(b2.Odd(), true);
			
			BigInteger b3(OTHER_SHORT_POSITIVE_STRING);
			Assert::AreEqual(b3.Odd(), false);

			BigInteger b4(OTHER2_SHORT_POSITIVE_STRING);
			Assert::AreEqual(b4.Odd(), true);
			
			BigInteger b5(SHORT_NEGATIVE_STRING);
			Assert::AreEqual(b5.Odd(), false);
		}

		TEST_METHOD(Even_DifferentNumber_CorrectResult)
		{
			BigInteger b1(LONG_POSITIVE_STRING);
			Assert::AreEqual(b1.Even(), true);

			BigInteger b2(OTHER3_LONG_POSITIVE_STRING);
			Assert::AreEqual(b2.Even(), false);

			BigInteger b3(OTHER_SHORT_POSITIVE_STRING);
			Assert::AreEqual(b3.Even(), true);

			BigInteger b4(OTHER2_SHORT_POSITIVE_STRING);
			Assert::AreEqual(b4.Even(), false);

			BigInteger b5(SHORT_NEGATIVE_STRING);
			Assert::AreEqual(b5.Even(), true);
		}

		TEST_METHOD(Abs_DifferentNumber_CorrectResult)
		{
			BigInteger b1(LONG_POSITIVE_STRING);
			BigInteger b2 = BigInteger::Abs(b1);
			Assert::AreEqual(b1 == b2, true);

			BigInteger b3(LONG_NEGATIVE_STRING);
			BigInteger b4 = BigInteger::Abs(b3);
			Assert::AreEqual(b4 == b1, true);

			BigInteger b5(SHORT_POSITIVE_STRING);
			BigInteger b6 = BigInteger::Abs(b5);
			Assert::AreEqual(b5 == b6, true);

			BigInteger b7(SHORT_NEGATIVE_STRING);
			BigInteger b8 = BigInteger::Abs(b7);
			Assert::AreEqual(b8 == b5, true);

			BigInteger b9(LONG_NEGATIVE_STRING);
			BigInteger b10 = BigInteger::Abs(b3);
			Assert::AreEqual(b9 == b10, false);
		}

		TEST_METHOD(GreatestCommonDivisor_DifferentNumber_CorrectResult)
		{
			BigInteger b1(FIRST_GREATEST_COMMON_DIVISOR_STRING_1_CASE);
			BigInteger b2(SECOND_GREATEST_COMMON_DIVISOR_STRING_1_CASE);
			Assert::AreEqual(BigInteger::GreatestCommonDivisor(b1, b2) == BigInteger(GREATEST_COMMON_DIVISOR_RESULT_STRING_1_CASE), true);

			BigInteger b3(FIRST_GREATEST_COMMON_DIVISOR_STRING_2_CASE);
			BigInteger b4(SECOND_GREATEST_COMMON_DIVISOR_STRING_2_CASE);
			Assert::AreEqual(BigInteger::GreatestCommonDivisor(b3, b4) == BigInteger(GREATEST_COMMON_DIVISOR_RESULT_STRING_2_CASE), true);

			BigInteger b5(FIRST_GREATEST_COMMON_DIVISOR_STRING_3_CASE);
			BigInteger b6(SECOND_GREATEST_COMMON_DIVISOR_STRING_3_CASE);
			Assert::AreEqual(BigInteger::GreatestCommonDivisor(b5, b6) == BigInteger(GREATEST_COMMON_DIVISOR_RESULT_STRING_3_CASE), true);

			BigInteger b7(FIRST_GREATEST_COMMON_DIVISOR_STRING_4_CASE);
			BigInteger b8(SECOND_GREATEST_COMMON_DIVISOR_STRING_4_CASE);
			Assert::AreEqual(BigInteger::GreatestCommonDivisor(b7, b8) == BigInteger(GREATEST_COMMON_DIVISOR_RESULT_STRING_4_CASE), true);

			BigInteger b9(FIRST_GREATEST_COMMON_DIVISOR_STRING_5_CASE);
			BigInteger b10(SECOND_GREATEST_COMMON_DIVISOR_STRING_5_CASE);
			Assert::AreEqual(BigInteger::GreatestCommonDivisor(b9, b10) == BigInteger(GREATEST_COMMON_DIVISOR_RESULT_STRING_5_CASE), true);
		}

		TEST_METHOD(Pow_DifferentNumber_CorrectResult)
		{
			BigInteger b1(NUMBER_FOR_POW_STRING_1_CASE);
			BigInteger b2(DEGREE_FOR_POW_STRING_1_CASE);
			Assert::AreEqual(b1.Pow(b2) == BigInteger(POW_RESULT_STRING_1_CASE), true);

			BigInteger b3(NUMBER_FOR_POW_STRING_2_CASE);
			BigInteger b4(DEGREE_FOR_POW_STRING_2_CASE);
			Assert::AreEqual(b3.Pow(b4) == BigInteger(POW_RESULT_STRING_2_CASE), true);

			BigInteger b5(NUMBER_FOR_POW_STRING_3_CASE);
			BigInteger b6(DEGREE_FOR_POW_STRING_3_CASE);
			Assert::AreEqual(b5.Pow(b6) == BigInteger(POW_RESULT_STRING_3_CASE), true);

			BigInteger b7(NUMBER_FOR_POW_STRING_4_CASE);
			BigInteger b8(DEGREE_FOR_POW_STRING_4_CASE);
			Assert::AreEqual(b7.Pow(b8) == BigInteger(POW_RESULT_STRING_4_CASE), true);

			BigInteger b9(NUMBER_FOR_POW_STRING_5_CASE);
			BigInteger b10(DEGREE_FOR_POW_STRING_5_CASE);
			Assert::AreEqual(b9.Pow(b10) == BigInteger(POW_RESULT_STRING_5_CASE), true);
		}

#pragma endregion PubblicMethod.Tests
	};
}