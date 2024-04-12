#ifndef DEPOSITS_H
#define DEPOSITS_H

#include<fstream>
#include<vector>
#include<string>
#include<sstream>
#include<chrono>
#include<iomanip>
#include<iostream>

struct Deposit{
	std::string name;
	double amount;
	std::chrono::system_clock::time_point depositDate;
	std::chrono::system_clock::time_point expiryDate;

};
std::vector<Deposit> loadDeposits();

std::string formatDate(const std::chrono::system_clock::time_point& date);

std::chrono::system_clock::time_point parseDate(const std::string& dateStr);

void saveDeposits(const std::vector<Deposit>& deposits);

void addAndSaveDeposit(const std::string& username, double amount, const std::string& depositDateStr, const std::string& expiryDateStr);

std::vector<Deposit>loadDeposits(const std::string& name);

#endif 
