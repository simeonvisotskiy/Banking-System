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

void singOrLog() 
{
	int choice = 0;
	while (true)
	{
		std::cout << "1. Log In\n";
		std::cout << "2. Sign Up\n";
		std::cout << "3. Exit\n";
		std::cin >> choice;

		switch (choice) {
		case 1:

			mainMenu();
			break;
		case 2:

			mainMenu();
			break;
		case 3:
			return;
		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
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

void logIn() {

}

void signUp() {

}

void mainMenu()
{
	int choice = 0;
	while (true)
	{
		std::cout << "1. Account balance\n";
		std::cout << "2. Withdraw money\n";
		std::cout << "3. Close account\n";
		std::cout << "4. Make a deposit\n";
		std::cout << "5. Invest my savingst\n";
		std::cout << "6. Exit\n";
		std::cin >> choice;

		switch (choice) {
		case 1:

			break;
		case 2:

			break;
		case 3:
			return;
		case 4:

			break;
		case 5:

			break;
		case 6:

			break;
		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
	}
}