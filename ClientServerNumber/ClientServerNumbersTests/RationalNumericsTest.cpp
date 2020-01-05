#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ClientServerNumber/RationalNumerics.h"
#include "../ClientServerNumber/RationalNumerics.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClientServerNumbersTests
{
	TEST_CLASS(RationalNumericsTest)
	{
	public:
		const string SHORT_POSITIVE_STRING = "1234";
		const string OTHER_SHORT_POSITIVE_STRING = "4";

		const string LONG_POSITIVE_STRING = "1234567891011121314";
		const string OTHER_LONG_POSITIVE_STRING = "2222222222222222";
		const string OTHER2_LONG_POSITIVE_STRING = "1000000000000004";

		const int SHORT_POSITIVE_INT = 1234;
		const long long LONG_POSITIVE_LONG = 1234567891011121314L;

		const string SHORT_NEGATIVE_STRING = "-1234";
		const string LONG_NEGATIVE_STRING = "-1234567891011121314";

		TEST_METHOD(Constructor_NotParameters_ReturnSameResult)
		{
			RationalNumerics r1 = RationalNumerics();
			//Assert::AreEqual(r1.Numerator == 0, true);
			Assert::AreEqual(r1.Sign(), 0);
			Assert::AreEqual(r1 == RationalNumerics::Zero(), true);
		}
	};
}