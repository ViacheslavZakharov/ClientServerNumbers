#include <iostream>
#include "FormulaRecognitionTests.h"

using namespace std;
void RunAdditionalTests();

int main()
{
	setlocale(LC_ALL, "Russian");
	RunAdditionalTests();
	system("pause");
	return 0;
}

void RunAdditionalTests() {
	FormulaRecognitionTests::AssertConvertPPN();
	FormulaRecognitionTests::AssertCalculate();
	cout<<"Все тесты прошли успешно!\n";
}