#include <iostream>
#include "ClientNumber.h"

using namespace std;

int main()
{
	ServerRationalNumber s1 = ServerRationalNumber("1", "3");
	ServerRationalNumber s2 = ServerRationalNumber("1", "3");
	ClientNumber cn = ClientNumber(s1, s2, Plus);
	string clientString = cn.ToString();
	cout << clientString << "\n";
	system("pause");
	return 0;
}