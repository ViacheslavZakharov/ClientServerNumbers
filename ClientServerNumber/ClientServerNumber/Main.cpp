#include <iostream>
#include "ClientNumber.h"

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

	RationalNumerics rn1 = RationalNumerics("400589", "100000");
	RationalNumerics rn2 = RationalNumerics("5008956", "1000000");
	ServerRationalNumber s1 = ServerRationalNumber(rn1);
	ServerRationalNumber s2 = ServerRationalNumber(rn2);
	cout << rn1 << " * " << rn2 << " = ";
	ClientNumber cn1 = ClientNumber(s1, s2, Operation::Divide);
	string clientString = cn1.ToString();
	cout << clientString << "\n";
	cout << "Точность числа:" << cn1.GetAccuracy() << "\n";
	
	cout << "Точный ответ: " << cn1.GetAccurateExponentialNumber().ToString() << "\n";

	while (true) {
		cout << "Увеличить точность (y/n)?\n";
		string answer;
		cin >> answer;
		if (answer == "n") {
			break;
		}

		cn1.IncreaseAccuracyResult(5);
		cout << cn1.ToString() << "\n";
		cout << "Точность числа:" << cn1.GetAccuracy() << "\n";
	}
	system("pause");
	return 0;
}