#include <iostream>
#include "FormulaRecognitionTests.h"
#include "FormulaManager.h"

using namespace std;
void RunAdditionalTests();

int main()
{
	setlocale(LC_ALL, "Russian");
	//RunAdditionalTests();
	cout<<"Начинаю вычислять\n";
	auto f = FormulaManager();
	string result = f.Calculate("(317/7+5/7)*(3/11)-481/3+(8/7)/(3/5)-8/3");
	cout<<"Результат вычисления:" << result<<"\n";
	cout<< "Увеличим каждый узел дерева операций на 1.\n";
	string increasedResult = f.GetIncreasedAccuracyResult(2);
	cout <<"После повышения точности: " << increasedResult << "\n";
	cout<<"Точность числа: " << f.GetRealAccuracyResult() << "\n";
	//f.PrintTreeResult();
	cout<<"\n";
	system("pause");
	return 0;
}

void RunAdditionalTests() {
	FormulaRecognitionTests::AssertConvertPPN();
	FormulaRecognitionTests::AssertCalculate();
	cout<<"Все тесты прошли успешно!\n";
}