#include "AppUtils.h"
#include "FXData.h"
#include "Deposits.h"

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
	/*char ch;
	std::cout << "Are you sure you want to remove your account?";
	std::cin >> ch;*/
	

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
		std::cout << "5. Check currency exchange rates\n";
		std::cout << "6. Send money\n";
		std::cout << "7. Deposit\n";
		std::cout << "8. Exit\n";
		std::cin >> choice;
		std::string temp;
		double balance = acc.getAmount();
		//double amouth;

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
			displayExchangeRate(accounts);
			break;
		case 6:
			sendMoney(accounts, acc);
			saveAccount(accounts);
			break;
		case 7:
			depositMenu(acc, accounts);
			saveAccount(accounts);
			break;
		case 8:
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

void displayExchangeRate(const std::vector<Account>& accounts) {
	FXData fxData; 
	std::map<std::string, double> rates;
	std::string currency;

	std::cout << "Enter the currency code (e.g., EUR, USD): ";
	std::cin >> currency;

	std::string apiUrl = "https://api.exchangerate-api.com/v4/latest/BGN?access_key=YOUR_API_KEY";
	rates = fxData.getApiData(apiUrl,"BGN");

	if (rates.find(currency) != rates.end()) {
		std::cout << "1 BGN = " << rates[currency] << " " << currency << std::endl;
	}
	else {
		std::cout << "Currency not found or API error.\n";
	}
}

void sendMoney(std::vector<Account>& accounts, Account& curr) {
	std::string name,password;
	bool transaction = false;
	double amount;

	while (!transaction) {
		std::cout << "\nType the account name to send money to: ";
		std::cin >> name;

		for (auto& account : accounts) {
			if (account.getName() == name ) {
				std::cout << "Enter the account password: ";
				std::cin >> password;

				if (curr.getPassword() == password) {
					std::cout << "Available balance:" << curr.getAmount() << std::endl;
					std::cout << "Enter amount to transfer: ";
					std::cin >> amount;
					if (curr.getAmount() >= amount) {
						curr.setAmount(curr.getAmount() - amount);
						account.setAmount(account.getAmount() + amount);
						updateAccount(accounts, curr);
						updateAccount(accounts, account);
						std::cout << "Transfer succesful! " << std::endl;
						transaction = true;
						return;
					}
					else {
						std::cout << "Insufficient funds." << std::endl;
					}
				}
				else {
					std::cout << "Incorrect password." << std::endl;
				}
				
				break;
			}

		}
		if (!transaction) {
			std::cout << "Try again Y/N: ";
			char choice;
			std::cin >> choice;
			if (choice == 'n' || choice == 'N') {
				return;
			}
		}
	}
}

void depositMenu(Account& acc, std::vector<Account>& accounts) {
	int choice = 0;
	double amount = 0;
	std::vector<Deposit> deposits = loadDeposits();

	while (true) {
		std::cout << "\n1. Make a deposit\n";
		std::cout << "2. See deposit\n";
		std::cout << "3. Exit\n";
		std::cin >> choice;
		

		switch (choice)
		{
		case 1: {
			std::string expiryDateStr;
			std::cout << "Enter deposit amount: ";
			std::cin >> amount;
			std::cout << "Enter expiry date (YYYY-MM-DD): ";
			std::cin >> expiryDateStr;

			if (amount > acc.getAmount()) {
				break;
			}
			else {
				acc.setAmount(acc.getAmount() - amount);
			}
			auto now = std::chrono::system_clock::now();
			auto depositDateStr = formatDate(now);
			deposits.push_back(Deposit{ acc.getName(), amount, parseDate(depositDateStr), parseDate(expiryDateStr) });
			std::cout << "Deposit added successfully.\n";
			saveDeposits(deposits);
			updateAccount(accounts, acc);
			saveAccount(accounts);
		}
			break;
		case 2:
		{
			displayDeposits(acc);
		}
			break;
		case 3:
			//saveDeposits(deposits);
			return;
		default:
			std::cout << "Invalid choice. Try again.\n";
			break;
		}
	}
}

int daysBetween(const std::chrono::system_clock::time_point& start, const std::chrono::system_clock::time_point& end) {
	return std::chrono::duration_cast<std::chrono::hours>(end - start).count() / 24;
}
double calculateAccruedAmount(double initialAmount, int days) {

	for (int i = 0;i < days;i++) {
		initialAmount *= 1.001;
	}

	return initialAmount;
}

void displayDeposits(const Account& acc) {
	auto today = std::chrono::system_clock::now();
	std::vector<Deposit> userDeposits = loadDeposits(acc.getName());

	if (userDeposits.empty()) {
		std::cout << "No deposits found for this account.\n";
		return;
	}

	for (const auto& deposit : userDeposits) {
		int days = daysBetween(deposit.depositDate, today);
		double accruedAmount = calculateAccruedAmount(deposit.amount, days); // 0.10% interest per day

		std::cout << "Original Amount: " << deposit.amount << " ";
		std::cout << "Amount as of " << formatDate(today) << ": " << accruedAmount << " ";
		std::cout << "Deposit Date: " << formatDate(deposit.depositDate) << " ";
		std::cout << "Expiry Date: " << formatDate(deposit.expiryDate) << std::endl;
	}
}