#include "Account.h"
#include "AppUtils.h"

Account::Account():amount(0), name(""), password("") {}

Account::Account(double amount, std::string name, std::string password)
	: amount(amount), name(name), password(password) {}

void Account::createAccount() {
	std::set<std::string>st = getNames();
	std::string tempName;
	std::cout << "\nEnter your Name: ";
	std::cin >> tempName;
	
	if (st.find(tempName) != st.end()) {
		while (st.find(tempName) != st.end()) {
			std::cout << "Invalid username\n";
			std::cout << "Enter a new one: ";
			//std::cin.ignore();
			std::cin >> tempName;
			
		}
	}
	this->name = tempName;

	std::cout << "\nEnter your password: ";
	std::cin >> password;
	std::cout << "\nEnter a deposit: ";
	std::cin >> amount;
	saveAccount(*this);

}

void Account::print() {
	std::cout << name<<"\n";
	std::cout << password<<"\n";
	std::cout << amount<<"\n";

}

void Account::printAmount() {
	std::cout << "\nAvailable:"<<getAmount();
}



	