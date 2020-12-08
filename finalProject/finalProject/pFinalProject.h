#ifndef iFinalProject_h
#define iFinalProject_h

#include <iostream>
#include <vector>
using namespace std;

class Bank
{
	private:
		const string name;
		double balance;

	public:
		const string accountNumber;

		Bank(const vector<string>& tokens) : accountNumber(tokens.size() >= 2 ?  tokens[1] : 0), name(tokens.size() >= 3 ?  tokens[2] : 0), balance(tokens.size() >= 4 ? atof(tokens[3].c_str()) : 0) {};
		Bank& operator = (const Bank&);
		void showAccount(ostream&) const;	// display 
		void withdraw(double);				// withdraw
		void deposit(double);				// deposit
};
ostream& roundingTwo(ostream&);
ostream& roundingOff(ostream&);
#endif