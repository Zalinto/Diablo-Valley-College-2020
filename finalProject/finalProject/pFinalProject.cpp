#include "pch.h"
#include "pFinalProject.h"
#include <iterator>
#include <sstream>

ostream& roundingTwo(ostream& cout)
{
    cout.setf(ios::fixed);
    cout.precision(2); // 2 decimal digits
    return cout;
}

ostream& roundingOff(ostream& cout)
{
    cout.unsetf(ios::fixed);
    cout.precision(6); // the C++ default
    return cout;
}

Bank& Bank::operator = (const Bank& copyThis)
{
    Bank& host = *this;
    if (this != &copyThis)
    {
        const_cast<string&>(host.accountNumber) = copyThis.accountNumber;
        const_cast<string&>(host.name) = copyThis.name;
        const_cast<double&>(host.balance) = copyThis.balance;
    }
    return host;
}

void Bank::showAccount(ostream& cout) const
{
    cout << "Account Number: " << accountNumber << "\r\n\r\n";
    cout << "Name: " << name << "\r\n\r\n";
    cout << "Balance: " << roundingTwo << balance << roundingOff << "\r\n\r\n";
}

void Bank::withdraw(double withdrawalAmount)
{
    balance -= withdrawalAmount; 
}

void Bank::deposit(double depositAmount)
{
    balance += depositAmount;
}