#ifndef APPUTILS_H
#define APPUTILS_H

#include "Account.h"
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<set>
#include<sstream>


   std::vector<Account> loadAccounts();

   void saveAccount(const Account& account);

   std::set<std::string> getNames();




#endif 