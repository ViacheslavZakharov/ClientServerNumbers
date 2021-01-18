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
	*/
	cout << "Демонстрация работы\n";
	RationalNumerics rn1 = RationalNumerics("10099", "10000");
	RationalNumerics rn2 = RationalNumerics("1");
	ExponentialNotation result = ExponentialNotation(rn1, 3) * ExponentialNotation(rn2, 3);
	string strResult = result.ToString();
	//count << strResult;
	//1.
	//RationalNumerics rn1 = RationalNumerics("1", "43");
	//RationalNumerics rn2 = RationalNumerics("7", "158");
	//ServerRationalNumber s1 = ServerRationalNumber(rn1);
	//ServerRationalNumber s2 = ServerRationalNumber(rn2);
	//cout << rn1 << " * " << rn2 << " = ";
	//ClientNumber cn1 = ClientNumber(s1, s2, Operation::Multiplication);
	//string clientString = cn1.ToString();
	//cout << clientString << "\n"; //1,0 * 10^-3
	////2.
	//RationalNumerics rn3 = RationalNumerics("2587", "7");
	//RationalNumerics rn4 = RationalNumerics("346", "5");
	//ServerRationalNumber s3 = ServerRationalNumber(rn3);
	//ServerRationalNumber s4 = ServerRationalNumber(rn4);
	//cout << rn3 << " * " << rn4 << " = ";
	//ClientNumber cn2 = ClientNumber(s3, s4, Operation::Multiplication);
	//string clientString1 = cn2.ToString();
	//cout << clientString1 << "\n"; //2,5574313 * 10^4
	//3.


	cout << "Хотите увеличить точность?(y/n):";
	string answer = "";
	cin >> answer;
	if (answer == "y")
	{
		cout << "Ведите количество знаков, на сколько вы хотите увеличить точность результата:";
		int countDigit = 0;
		cin >> countDigit;
	//	cn.IncreaseAccuracyResult(countDigit);
	//	cout << "Результат увеличения точности: " << cn.ToString() << "\n";
	}
	system("pause");
	return 0;
}