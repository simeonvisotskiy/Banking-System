#ifndef ACCOUNT_H
#define ACCOUNT_H

#include<set>
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include"FXData.h"


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

	void setName(const std::string& name_) { name = name_; }
	void setPassword(const std::string& password_) { password = password_; }
	void setAmount(const double& amount_) { amount = amount_; }

	void createAccount(std::vector<Account>& accounts);
	void printAmount();
	void print();

};
	bool checkName(const std::string& name, std::set<std::string> names);
	bool checkPassword(const std::string& password);


#endif 
