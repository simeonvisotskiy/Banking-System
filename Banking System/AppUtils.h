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

void saveAccount(const std::vector<Account>& accounts);

std::set<std::string> getNames();

void removeAcc(const std::string& name,const std::vector<Account>& accounts);

bool logIn(std::vector<Account>& accounts, Account& acc);

std::vector< Account> getNamesAndPass();

void mainMenu(Account& acc, std::vector<Account>& accounts);

void withdrawMoney(Account& acc);

void depositMoney(Account& acc);

void updateAccount(std::vector<Account>& accounts, const Account& updateAccount);

#endif 
