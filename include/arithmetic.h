#include <iostream>
#include <string>
#include "stack.h"
#include <cmath>

using namespace std;

#define MAX_NUMB_VAR 26
#define MAX_NUMB_TOK 256

class TArithmetic
{
protected:
	string str;										//expression
	int numbvars;
	char namevars[MAX_NUMB_VAR];
	double valuevars[MAX_NUMB_VAR];
public:
	TArithmetic(string _str = " ");
	~TArithmetic();
	void setvars(int numb, char *names, double *values);
	double Calculate();				
private:
	int priority(char a);
	int checkprior(TStack<char> &stack);
	bool isoperation(char a);
	double doop(TStack<double> &dst, TStack<char> &cst);
	bool isnumber(char a);
	double setvar(char a);
};

TArithmetic::TArithmetic(string _str)
{
	str = _str;
}

TArithmetic::~TArithmetic()
{}

void TArithmetic::setvars(int numb, char *names, double *values)
{
	numbvars = numb;
	for (int i = 0; i < numbvars; i++)
		namevars[i] = names[i];
	for (int i = 0; i < numbvars; i++)
		valuevars[i] = values[i];
}

int TArithmetic::priority(char a)
{
	switch(a)
	{
	case '^': return 4;
	case '*': case '/': return 3;
	case '-': return 2;
	case '+': return 1;
	case '(': return 0;
	}
}

int TArithmetic::checkprior(TStack<char> &stack)
{
	char tmp;
	tmp=stack.GetElem();
	stack.SetElem(tmp);
	return priority(tmp);
}

bool TArithmetic::isoperation(char a)
{
	if ((a == '+') ||
		(a == '-') ||
		(a == '*') ||
		(a == '/') ||
		(a == '^'))
		return true; 
	else return false;
}

double TArithmetic::doop(TStack<double> &dst, TStack<char> &cst)
{
	char op;
	op = cst.GetElem();
	double dig2 = dst.GetElem();
	double dig1 = dst.GetElem();
	switch (op)	{
			case '^': return(pow(dig1, dig2)); 
			case '*': return(dig1 * dig2); 
			case '/': return(dig1 / dig2); 
			case '+': return(dig1 + dig2); 
			case '-': return(dig1 - dig2); 
			}
}

bool TArithmetic::isnumber(char a)
{
	if ((a>='0')&&(a<='9'))
		return 1;
	else
		return 0;
}

double TArithmetic::setvar(char a)
{
	int i = 0;
	for (;i<MAX_NUMB_VAR; i++)
	{
		if (namevars[i]==a)
			return valuevars[i];
	}
	throw("illigal var");
}

double TArithmetic::Calculate()
{
	TStack<char> ostack(MAX_NUMB_TOK);				//stack of operations
	TStack<double> dstack(MAX_NUMB_TOK);			//stack of digits
	TStack<char> bstack(MAX_NUMB_TOK);				//stack 4 check brackets
	int flag = 0;									//flag 4 check unary minus
	int dflag = 1;

	/*--------------------------------------------------------------*/

	int i=0;
	while (i < str.length()) 
	{
		if (isnumber(str[i])) 
		{
			string tmp = "";
			while ( (i < str.length()) && (isnumber(str[i]) || (str[i]=='.')) ) 
			{
				tmp += str[i];
				i++;
			}
			i--;
			if (flag) 
			{
				dstack.SetElem(-stod(tmp));
				flag = 0;
			}
			else dstack.SetElem(stod(tmp));
			dflag = 0;
		}
		else
			if (isalpha(str[i])) 
			{
				dstack.SetElem(setvar(str[i]));
				dflag = 0;
			}
			else
				if (str[i]=='(')
				{
					ostack.SetElem(str[i]);
					bstack.SetElem(1);
					dflag = 1;
				}
				else
					if (isoperation(str[i]))
					{
						if ((str[i]=='-')&&(((!ostack.IsEmpty())&&(checkprior(ostack)==0)&&dflag) ||(ostack.IsEmpty()&&dflag)	))
							flag = 1;
						else
							if (((!ostack.IsEmpty())&&(checkprior(ostack)==0)) ||
								(ostack.IsEmpty())							   ||
								(priority(str[i])>=checkprior(ostack))			)
								ostack.SetElem(str[i]);
							else 
								if (priority(str[i])<checkprior(ostack))
								{
									while ((!ostack.IsEmpty())&&(priority(str[i])<checkprior(ostack)))
										dstack.SetElem(doop(dstack,ostack));
									if (str[i]=='-')						
									{
										flag = 1;
										if (((!ostack.IsEmpty())&&(checkprior(ostack)!=0)) ||
											(!dstack.IsEmpty()))	
											ostack.SetElem('+');
									}
									else
										ostack.SetElem(str[i]);
								}
					}
					else 
						if (str[i]==')')
						{
							if (bstack.IsEmpty())
								throw ("illigal brackets");
							else
								char tmp = bstack.GetElem();

							while (checkprior(ostack) != 0)
								dstack.SetElem(doop(dstack,ostack));
							char tmp = ostack.GetElem();
						}
		i++;
	}

	if (!bstack.IsEmpty()) throw ("illigal brackets");

	while (!ostack.IsEmpty())
		dstack.SetElem(doop(dstack,ostack));

	/*--------------------------------------------------------------*/

	if (dstack.IsEmpty()) return 0;
	else return dstack.GetElem();
}
