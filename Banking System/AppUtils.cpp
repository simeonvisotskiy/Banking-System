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