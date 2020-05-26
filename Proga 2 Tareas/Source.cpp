#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	fstream a("Texto.txt");
	while (!a.eof())
	{
		string x;
		a >> x;
		cout << x<< " ";
	}
}