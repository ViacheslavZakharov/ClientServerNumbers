#include <iostream>
#include "FormulaRecognitionTests.h"
#include "FormulaManager.h"

using namespace std;
void RunAdditionalTests();

int main()
{
	setlocale(LC_ALL, "Russian");
	RunAdditionalTests();
	//auto f = FormulaManager();
	//string formula = "(317/7+5/7)*(3/11)-481/3+(8/7)/(3/5)-8/3";
	//cout << "Начинаю вычислять выражение: " << formula << "\n";
	//string result = f.Calculate(formula);
	//cout<<"Результат вычисления:" << result<<"\n";
	//cout<<"Получившаяся точность числа: " << f.GetRealAccuracyResult() << "\n";
	//cout << "Введите новую точность числа: ";
	//int newAccuracy = 3;
	//cin >> newAccuracy;
	//cout<< "Увеличим каждый узел дерева операций на " << newAccuracy << ".\n";
	//string increasedResult = f.GetIncreasedAccuracyResult(newAccuracy);
	//cout <<"После повышения точности: " << increasedResult << "\n";
	//cout<<"Точность числа: " << f.GetRealAccuracyResult() << "\n";
	// 
	// 
	// 
	//auto f = FormulaManager();
	//string formula = "(42+(108/5)*12)/3";
	//cout << "Начинаю вычислять выражение: " << formula << "\n";
	//string result = f.Calculate(formula);
	//cout<<"Результат вычисления:" << result<<"\n";
	//cout<<"Получившаяся точность числа: " << f.GetRealAccuracyResult() << "\n";
	//cout << "Введите новую точность числа: ";
	//int newAccuracy = 3;
	//cin >> newAccuracy;
	//cout<< "Увеличим каждый узел дерева операций на " << newAccuracy << ".\n";
	//string increasedResult = f.GetIncreasedAccuracyResult(newAccuracy);
	//cout <<"После повышения точности: " << increasedResult << "\n";
	//cout<<"Точность числа: " << f.GetRealAccuracyResult() << "\n";
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