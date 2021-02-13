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
	RationalNumerics rn1 = RationalNumerics("583", "100");
	RationalNumerics rn2 = RationalNumerics("348540158", "100000");
	ServerRationalNumber s1 = ServerRationalNumber(rn1);
	ServerRationalNumber s2 = ServerRationalNumber(rn2);
	cout << rn1 << " / " << rn2 << " = ";
	ClientNumber cn1 = ClientNumber(s1, s2, Operation::Divide);
	string clientString = cn1.ToString();
	cout << clientString << "\n";
	system("pause");
	return 0;
}