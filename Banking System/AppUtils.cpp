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

void saveAccount(const Account& account) {
	std::ofstream file("accounts.txt", std::ios::app);
	if (file.is_open()) {
		file << account.getName() << " " << account.getPassword() << " " << account.getAmount() << "\n";
		file.close();
	}
	else {
		std::cout << "err\n";
	}
}

void removeAcc(const std::string& nameToRemove) {
	std::vector<std::string> accounts;
	std::ifstream file("accounts.txt");
	std::string line, name;

	while (getline(file, line)) {
		std::stringstream lineStream(line);
		lineStream >> name;

		if (nameToRemove != name) {
			accounts.push_back(line);
		}
	}
	file.close();
	std::ofstream outFile("accounts.txt", std::ofstream::trunc);
	for (const auto& acc : accounts) {
		outFile << acc << "\n";
	}
	outFile.close();
}

bool logIn(Account& acc) {
	std::vector<Account>vec = getNamesAndPass();
	std::string name, password;
	bool login = false;

	while (!login) {
		std::cout << "\nEnter your Name: ";
		std::cin >> name;

		std::cout << "\nEnter your password: ";
		std::cin >> password;

		for (const auto& account:vec){
			if (account.getName() == name && account.getPassword() == password) {
				std::cout << "Login successful!"<< std::endl;
				acc.setName(account.getName());
				acc.setPassword(account.getPassword());
				acc.setAmount(account.getAmount());
				removeAcc(account.getName());
				//login = true;
				return true ;
			}

		}
		if (!login) {
			std::cout << "Incorrect name or password\n";
			std::cout << "Try again Y/N: ";
			char choice;
			std::cin >> choice;
			if (choice == 'n' || choice == 'N') {
				return false;
			}
		}
	}
	return false;
}

void mainMenu(Account& acc)
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
			saveAccount(acc);
			break;
		case 3:
			std::cout << "Type account name: ";
			std::cin >> temp;
			removeAcc(temp);
			return;
		case 4:
			std::cout << "Type amount";
			std::cin >> amouth;
			acc.setAmount(amouth);
			saveAccount(acc);

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
	if (acc.getAmount() - amount < 0) {
		std::cout << "Unable to complete transaction\n";
	}
	else {
		acc.setAmount(acc.getAmount() - amount);
	}

}