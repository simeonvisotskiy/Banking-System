#ifndef APPUTILS_H
#define APPUTILS_H

#include "Account.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<set>
#include<sstream>
#include<utility>


std::vector<Account> loadAccounts();

void saveAccount(const Account& account);

std::set<std::string> getNames();

void removeAcc(const std::string& name);

bool logIn(Account& acc);

std::vector< Account> getNamesAndPass();

void mainMenu(Account& acc);

void withdrawMoney(Account& acc);



#endif 
