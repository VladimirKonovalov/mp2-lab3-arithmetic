#include <iostream>
#include <string>
#include "arithmetic.h"

using namespace std;

int main()
{	
	start:
	string str;
	char tmp;


	cout << "You want use vars? (y/n)" << endl;
	cin >> tmp;

	if (tmp=='y')
	{
		int n;
		cout << "Enter number of vars: ";
		cin >> n;
		char *names = new char[n];
		double *values = new double[n];

		for (int i = 0; i < n; i++)
		{
			cout << "Enter name " << i+1 << " variable: ";
			cin >> names[i];
			cout << "Enter value " << names[i] <<": ";
			cin >> values[i];
		}
		cout << "Enter expression:" << endl;
		cin >> str;
		TArithmetic calc(str);
		calc.setvars(n,names,values);
		cout << "Value: " << calc.Calculate() << endl;
		other:
		char _tmp;
		cout << "Want to repeat with other values? (y/n)" << endl;
		cin >> _tmp;
		if (_tmp=='y')
		{
			for (int i = 0; i < n; i++)
			{
				cout << "Enter value " << names[i] <<": ";
				cin >> values[i];
			}
			calc.setvars(n,names,values);
			cout << "Value: " << calc.Calculate() << endl;
			goto other;
		}
		else
		{
			cout << "Want to repeat? (y/n)" << endl;
			char __tmp;
			cin >> __tmp;
			if (__tmp=='y') 
			{	
				system("CLS");
				goto start;
			}
			else exit;
		}	
	}
	else
	{
		cout << "Enter expression:" << endl;
		cin >> str;
		TArithmetic calc(str);
		cout << "Value: " << calc.Calculate() << endl;
		cout << "Want to repeat? (y/n)" << endl;
		char __tmp;
		cin >> __tmp;
		if (__tmp=='y') 
		{	
			system("CLS");
			goto start;
		}
		else exit;
	}
	return 1;
}