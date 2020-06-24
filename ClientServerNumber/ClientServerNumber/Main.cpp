#include <iostream>
#include "ClientNumber.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	//// Демонстраци¤ работы.
	//cout << "ƒемонстраци¤ работы 1:\n";
	//RationalNumerics rn1 = RationalNumerics("1", "3");
	//RationalNumerics rn2 = RationalNumerics("1", "3");
	//ServerRationalNumber s1 = ServerRationalNumber(rn1);
	//ServerRationalNumber s2 = ServerRationalNumber(rn2);
	//cout << rn1 << " + " << rn2 <<" = ";
	//ClientNumber cn = ClientNumber(s1, s2, Plus);
	//string clientString = cn.ToString();
	//cout << clientString << "\n";
	//
	//cout << "’отите увеличить точность?(y/n):";
	//string answer = "";
	//cin >> answer;
	//if (answer == "y")
	//{
	//	cout << "¬ведите количество знаков, на сколько вы хотите увеличить точность результата:";
	//	int countDigit = 0;
	//	cin >> countDigit;
	//	cn.IncreaseAccuracyResult(countDigit);
	//	cout <<"–езультат увеличени¤ точности: " << cn.ToString() <<"\n";
	//}
	//-----------------
	cout << "ƒемонстраци¤ работы 2:\n";
	RationalNumerics rn1 = RationalNumerics("2587", "7");
	RationalNumerics rn2 = RationalNumerics("346", "5");
	ServerRationalNumber s1 = ServerRationalNumber(rn1);
	ServerRationalNumber s2 = ServerRationalNumber(rn2);
	cout << rn1 << " + " << rn2 << " = ";
	ClientNumber cn = ClientNumber(s1, s2, Plus);
	string clientString = cn.ToString();
	cout << clientString << "\n";

	cout << "’отите увеличить точность?(y/n):";
	string answer = "";
	cin >> answer;
	if (answer == "y")
	{
		cout << "¬ведите количество знаков, на сколько вы хотите увеличить точность результата:";
		int countDigit = 0;
		cin >> countDigit;
		cn.IncreaseAccuracyResult(countDigit);
		cout << "–езультат увеличени¤ точности: " << cn.ToString() << "\n";
	}
	system("pause");
	return 0;
}