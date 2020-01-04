#include "stdafx.h"
#include "CppUnitTest.h"
#include "../ClientServerNumber/BigInteger.h"
#include "../ClientServerNumber/BigInteger.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ClientServerNumbersTests
{		
	TEST_CLASS(BigIntegerTest)
	{
	public:
		
		TEST_METHOD(Constructor_String_And_Int_Return_Same_Result)
		{
			// TODO: Разместите здесь код своего теста
			BigInteger b1("123");
			BigInteger b2("123");
			//auto str1 = b1.ToString();
			//auto str2 = b2.ToString();
			Assert::AreEqual(b1.ToString(), b2.ToString());
		}

	};
}