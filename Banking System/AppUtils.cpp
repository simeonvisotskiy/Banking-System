#include "AppUtils.h"

std::vector<Account> loadAccounts() {
	std::vector<Account>accounts;
	std::ifstream file("accounts.txt");
	std::string name, password;
	double amount;
	while (file >> name >> password >> amount) {
		accounts.emplace_back(amount, name, password);
	}
	return accounts;
}

std::set<std::string> getNames() {
	std::set<std::string> accNames;
	std::ifstream file("accounts.txt");
	std::string name, line;

	while (getline(file, line)) {
		std::istringstream lineStream(line);
		
		if (lineStream >> name) {
			accNames.insert(name);
		}

	}

	return accNames;
}

void saveAccount(const std::vector<Account>& accounts) {
	std::ofstream file("accounts.txt", std::ios::trunc);
	if (file.is_open()) {
		for (const auto& account : accounts) {
			file << account.getName() << " " << account.getPassword() << " " << account.getAmount() << "\n";
		}
		file.close();
	}
	else {
		std::cout << "err\n";
	}
}

void removeAcc(const std::string& nameToRemove, std::vector<Account>& accounts) {
	for (auto it = accounts.begin();it != accounts.end();it++) {
		if (it->getName() == nameToRemove) {
			accounts.erase(it);
		}
	}
}

bool logIn(std::vector<Account>& accounts, Account& acc) {

	std::string name, password;
	bool login = false;

	while (!login) {
		std::cout << "\nEnter your Name: ";
		std::cin >> name;

		std::cout << "\nEnter your password: ";
		std::cin >> password;

		for (const auto& account: accounts){
			if (account.getName() == name && account.getPassword() == password) {
				std::cout << "Login successful!"<< std::endl;
				acc = account;
				return true ;
			}

		}
		
		std::cout << "Incorrect name or password\n";
		std::cout << "Try again Y/N: ";
		char choice;
		std::cin >> choice;
		if (choice == 'n' || choice == 'N') {
			return false;
		}
		
	}
	return false;
}

void mainMenu(Account& acc, std::vector<Account>& accounts)
{
	int choice = 0;
	while (true)
	{
		std::cout << "\n1. Account balance\n";
		std::cout << "2. Withdraw money\n";
		std::cout << "3. Close account\n";
		std::cout << "4. Make a deposit\n";
		std::cout << "5. Invest my savingst\n";
		std::cout << "6. Exit\n";
		std::cin >> choice;
		std::string temp;
		double balance = acc.getAmount();
		double amouth;

		switch (choice) {
		case 1:
			std::cout << "Account balance: " << balance << std::endl;
			break;
		case 2:
			withdrawMoney(acc);
			updateAccount(accounts, acc);
			saveAccount(accounts);
			break;
		case 3:
			removeAcc(acc.getName(), accounts);
			saveAccount(accounts);
			return;
		case 4:
			depositMoney(acc);
			updateAccount(accounts, acc);
			saveAccount(accounts);

			break;
		case 5:

			break;
		case 6:
			return;
		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
	}
}


std::vector< Account> getNamesAndPass() {
	std::vector<Account>vec;

	std::set<std::string> accNames;
	std::ifstream file("accounts.txt");
	std::string line;

	while (getline(file, line)) {
		std::istringstream lineStream(line);
		std::string name, password;
		double amount;
		if (lineStream >> name >> password >> amount) {
			vec.emplace_back(amount, name, password);
		}

	}
	return vec;
	
}

void withdrawMoney(Account& acc) {
	std::cout << "Available balance:" << acc.getAmount()<<std::endl;
	double amount;
	std::cin >> amount;
	if (amount <= 0) {
		std::cout << "Withdrawl shoud be positive.\n";
		return;
	}
	if (acc.getAmount() - amount < 0) {
		std::cout << "Unable to complete transaction\n";
	}
	else {
		acc.setAmount(acc.getAmount() - amount);
		std::cout << "Withdrawl successful.";
	}

}

void depositMoney(Account& acc) {
	double deposit;
	std::cout << "Enter deposit: ";
	std::cin >> deposit;
	if (deposit > 0) {
		acc.setAmount(acc.getAmount() + deposit);
		std::cout << "Deposit successful." << std::endl;
	}
	else {
		std::cout << "Invalid deposit amount." << std::endl;
	}
}

void updateAccount(std::vector<Account>& accounts, const Account& updateAccount) {
	for (auto& account : accounts) {
		if (account.getName() == updateAccount.getName()) {
			account = updateAccount;
			break;
		}
	}
}