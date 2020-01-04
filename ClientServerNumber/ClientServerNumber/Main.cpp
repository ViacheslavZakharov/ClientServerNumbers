#include <iostream>
#include "BigInteger.h"

using namespace std;

int main()
{
	//198.32
	//0.002
	//1.98320 e-2
	//0.00002
	BigInteger bi("98320");
	BigInteger bi2("00002");
	//198.322
	//cout << bi.pow(-2) << endl;
	//BigInteger bi2("5");
	//cout <<"\n"<< ++bi2 << bi2 + bi;
	//cout << "\n" << bi2++;
	//cout << "\n" << bi2++;
	//cout << "\n" <<"bi="<<bi<<" bi2="<<bi2<<"\t"<< ++bi2/bi;
	cout << bi + bi2 << "\n";


	BigInteger b3("9");
	BigInteger b4("5");
	//cout << b3 % b4 << "\n";
	//BigInteger b5 = ;
	//BigInteger b6 = BigInteger::One();
	//count << b6;
	//cout << BigInteger::test();
	//BigInteger b5 = BigInteger::One();
	//cout << b5;
	cout << BigInteger::One() << "\n";
	cout << BigInteger::Zero() << "\n";
	cout << BigInteger::MinusOne() << "\n";
	//cout << BigInteger::Divide(BigInteger("8"),BigInteger("4")) << "\n";
	cout << BigInteger::Remainder(BigInteger("108"), BigInteger("10")) << "\n";
	//count <<;
	cout << "Hello World!\n";
	//cout << BigInteger("1") / BigInteger("0");
	//b3 = b3.pow(5);
	auto str = b3.ToString();
	cout << str;
	system("pause");
	return 0;
}