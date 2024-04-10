#include "Account.h"
#include "AppUtils.h"

Account::Account():amount(0), name(""), password("") {}

Account::Account(double amount, std::string name, std::string password)
	: amount(amount), name(name), password(password) {}

void Account::createAccount(std::vector<Account>& accounts) {
	std::set<std::string> names;
	for (const auto& acc : accounts) {
		names.insert(acc.getName());
	}

	std::string tempName;
	std::cout << "\nEnter your Name: ";
	std::cin >> tempName;
	
	while (names.find(tempName) != names.end()) {
		std::cout << "Invalid username, already taken.\n";
		std::cout << "Enter a new one: ";
		std::cin >> tempName;
	}
	this->name = tempName;

	std::cout << "\nEnter your password: ";
	std::cin >> this->password;
	std::cout << "\nEnter a deposit: ";
	std::cin >> this->amount;

	
	accounts.push_back(*this);

}

void Account::print() {
	std::cout << name<<"\n";
	std::cout << password<<"\n";
	std::cout << amount<<"\n";

}

void Account::printAmount() {
	std::cout << "\nAvailable:"<<getAmount();
}



	