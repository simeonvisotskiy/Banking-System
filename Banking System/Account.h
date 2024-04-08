#ifndef ACCOUNT_H
#define ACCOUNT_H

#include<set>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>

class Account
{
	double amount;
	std::string name;
	std::string password;

public:
	Account();
	Account(double amount, std::string name, std::string password);
	std::string getName()const { return name; }
	std::string getPassword()const { return password; }

	double getAmount()const { return amount; }
	void createAccount();
	void printAmount();
	void print();

};



#endif 