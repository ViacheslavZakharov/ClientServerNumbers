#include <iostream>
//#include "ClientNumber.h"
//#include "FormulaRecognition.h"
#include "StackList.h"
#include "BigInteger.h"
#include "ServerRationalNumber.h"
#include "FormulaRecognition.h"
#include <cassert> 

using namespace std;


int main()
{
	setlocale(LC_ALL, "Russian");
	/*Примеры:
	* 1) 1/43 * 7/158
	* 2) 2587/7 * 346/5
	* 3) 1/3 * 1/3
	* 4) 400589/100000 * 5008956/1000000
	* 5) 400999/100000 * 5009999/1000000
	* "583", "100", "348540158", "100000", "1,67 * 10^-3"
	*/
	cout << "Демонстрация работы\n";
	//RationalNumerics rn1 = RationalNumerics("1", "3");
	//RationalNumerics rn2 = RationalNumerics("1", "3");
	// 11/13 ; 1/12; 1/112; 55/13; 76/13 = 5 11/13 ;158/589 (нет периода), 337/112 = 3, 1/112
	//ExponentialNotation exp1 = ExponentialNotation(RationalNumerics("337", "112"), 100);
	//ExponentialNotation exp1 = ExponentialNotation(RationalNumerics("10", "3"), 10);
	//1 /112
	//cout << exp1.ToString() << "\n";
	//cout<<exp1.ToString(true);
	//RationalNumerics rn1 = RationalNumerics("400589", "100000");
	//RationalNumerics rn2 = RationalNumerics("5008956", "1000000");
	//ServerRationalNumber s1 = ServerRationalNumber(rn1);
	//ServerRationalNumber s2 = ServerRationalNumber(rn2);
	//cout << rn1 << " * " << rn2 << " = ";
	//ClientNumber cn1 = ClientNumber(s1, s2, Operation::Divide);
	//string clientString = cn1.ToString();
	//cout << clientString << "\n";
	//cout << "Точность числа:" << cn1.GetAccuracy() << "\n";
	//
	//cout << "Точный ответ: " << cn1.GetAccurateExponentialNumber().ToString() << "\n";

	//while (true) {
	//	cout << "Увеличить точность (y/n)?\n";
	//	string answer;
	//	cin >> answer;
	//	if (answer == "n") {
	//		break;
	//	}

	//	cn1.IncreaseAccuracyResult(5);
	//	cout << cn1.ToString() << "\n";
	//	cout << "Точность числа:" << cn1.GetAccuracy() << "\n";
	//}
	/*			string formula = "(8+2*5)/(1+3*2-4)";
			string expectedPPNFormula = "8 2 5 *+1 3 2 *+4 -/";
			FormulaRecognition f = FormulaRecognition();
			string actualResult = f.ConvertPPN(formula);*/
			//cout << actualResult;
	//ServerRationalNumber sr = ServerRationalNumber(RationalNumerics("1", "3"));
	//ServerRationalNumber sr1 = ServerRationalNumber(RationalNumerics("1", "125"));
	//StackList<ServerRationalNumber> SL;
	////SL.Print("SL");

	//SL.Push(sr);
	//SL.Push(sr1);
	//SL.Print();
	//auto top = SL.Pop();
	//auto top1 = SL.Pop();
	//SL.Print();
	/*for (int i = 0; i < 20; i++) {
		stack.push(i);
	}
	stack.printStack();
	for (int i = 0; i < 10; i++) {
		stack.pop();
	}
	cout << "\n";
	stack.printStack();*/

	string formula = "(8+2*5)/(1+3*2-4)";
	string expectedPPNFormula = "8 2 5 *+1 3 2 *+4 -/";
	FormulaRecognition f = FormulaRecognition();
	string actualResult = f.ConvertPPN(formula);
	//bool formulasAreEqual = expectedPPNFormula == actualResult;
	assert(expectedPPNFormula == actualResult, "int must be 4 bytes");
	auto result = f.Calculate(actualResult);
	result.Print();
	//auto t = result.Top();
	//cout<<t.ToString();
	system("pause");
	return 0;
}