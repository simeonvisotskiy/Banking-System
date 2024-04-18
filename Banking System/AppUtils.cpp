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

bool removeAcc(const std::string& nameToRemove, std::vector<Account>& accounts) {


	std::string ch;
	std::cout << "Are you sure you want to remove your account? " << " (Y/N) ";
	std::cin >> ch;
	while (true) {
		if (ch == "N" || ch == "n") {
			return false;
		}
		else if (ch == "Y" || ch == "y") {
			for (auto it = accounts.begin(); it != accounts.end(); it++) {
				if (it->getName() == nameToRemove) {
					accounts.erase(it);
					return true;
				}
			}
		}
		else {
			std::cout << "\nInvalid input try again: ";
			std::cin >> ch;
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
		std::string choice;
		std::cin >> choice;
		while (choice != "y" && choice != "Y" && choice != "n" && choice != "N") {
			std::cout << "Invalid input. Try again Y/N: ";
			std::cin >> choice;
		}

		if (choice == "n" || choice == "N") {
			return false;
		}
		
	}
	return false;
}

void mainMenu(Account& acc, std::vector<Account>& accounts)
{
	std::string choice;
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
		std::cin.ignore();

		if (choice == "1") {
			std::cout << std::fixed << std::setprecision(2) << "Account balance: " << acc.getAmount() << std::endl;
		}
		else if (choice == "2")
		{
			withdrawMoney(acc);
			updateAccount(accounts, acc);
			saveAccount(accounts);
		}
		else if (choice == "3")
		{
			if (removeAcc(acc.getName(), accounts))
			{
				std::cout << "Account removed. \n";
				return;
			}
			else
			{
				std::cout << "Account removal cancelled. \n";
			}
			saveAccount(accounts);
		}
		else if (choice == "4")
		{
			depositMoney(acc);
			updateAccount(accounts, acc);
			saveAccount(accounts);
		}
		else if (choice == "5")
		{
			displayExchangeRate(accounts);
		}
		else if (choice == "6")
		{
			sendMoney(accounts, acc);
			saveAccount(accounts);
		}
		else if (choice == "7")
		{
			depositMenu(acc, accounts);
			saveAccount(accounts);
		}
		else if (choice == "8")
		{
			return;
		}
		else
		{
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
	std::cout << "Available balance: " << acc.getAmount() << std::endl;
	double amount = 0.0;
	std::string amountStr;

	std::getline(std::cin, amountStr);

	if (amountStr.empty() || !std::all_of(amountStr.begin(), amountStr.end(), [](char c) { return std::isdigit(c) || c == '.'; }) || std::count(amountStr.begin(), amountStr.end(), '.') > 1) {
		std::cout << "Withdrawal amount should be a positive number.\n";
		return;
	}

	amount = std::stod(amountStr);

	if (amount <= 0) {
		std::cout << "Withdrawal amount should be positive.\n";
		return;
	}

	if (acc.getAmount() - amount < 0) {
		std::cout << "Unable to complete transaction.\n";
	}
	else {
		acc.setAmount(acc.getAmount() - amount);
		std::cout << "Withdrawal successful.\n";
	}
}

void depositMoney(Account& acc) {
	double deposit = 0.0;
	std::string depositStr;
	std::cout << "Enter deposit amount: ";
	std::getline(std::cin, depositStr);

	if (depositStr.empty() || !std::all_of(depositStr.begin(), depositStr.end(), [](char c) { return std::isdigit(c) || c == '.'; })) {
		std::cout << "Deposit amount should be a positive number.\n";
		return;
	}
	deposit = std::stod(depositStr);

	if (deposit <= 0) {
		std::cout << "Deposit amount should be positive.\n";
		return;
	}

	std::streamsize prec = std::cout.precision();
	std::cout << std::fixed << std::setprecision(2);
	acc.setAmount(acc.getAmount() + deposit);
	std::cout << "Deposit successful.\n";
	std::cout.precision(prec);
}

void updateAccount(std::vector<Account>& accounts, const Account& updateAccount) {
	for (auto& account : accounts) {
		if (account.getName() == updateAccount.getName()) {
			//account.setPassword(updateAccount.getPassword());
			account.setAmount(updateAccount.getAmount());
			//account = updateAccount;
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
	std::string name;
	bool transaction = false;

	while (!transaction) {
		std::cout << "\nType the account name to send money to: ";
		std::cin >> name;
		
		if (name == curr.getName()) {
			std::cout << "Cannot transfer money to the same account." << std::endl;
			continue; 
		}
		bool found = false;
		for (auto& account : accounts) {
			if (account.getName() == name) {
				std::string password;
				std::cout << "Enter the account password: ";
				std::cin >> password;

				if (curr.getPassword() == password) {
					std::cout << "Available balance:" << std::fixed << std::setprecision(2) << curr.getAmount() << std::endl;
					std::string amountStr;
					std::cout << "Enter amount to transfer: ";
					std::cin >> amountStr;

					double amount;
					try {
						amount = std::stod(amountStr);
					}
					catch (const std::invalid_argument& e) {
						std::cout << "Invalid amount. Please try again." << std::endl;
						continue;
					}

					if (amount <= 0 || amount > curr.getAmount()) {
						std::cout << "Invalid amount. Please try again." << std::endl;
					}
					else {
						curr.setAmount(curr.getAmount() - amount);
						account.setAmount(account.getAmount() + amount);
						updateAccount(accounts, curr);
						updateAccount(accounts, account);
						std::cout << "Transfer successful! " << std::endl;
						transaction = true;
					}
					return;
				}
				else {
					std::cout << "Incorrect password." << std::endl;
				}
				found = true;
				break;
			}
		}
		if (!found) {
			std::cout << "Account name not found.\n";
		}

		if (!transaction) {
			std::string choice;
			std::cout << "Continue? (Y/N): ";
			std::cin >> choice;

			while (choice != "y" && choice != "Y" && choice != "n" && choice != "N") {
				std::cout << "Invalid input. Try again Y/N: ";
				std::cin >> choice;
			}

			if (choice == "n" || choice == "N") {
				return;
			}
		}
	}
}

void depositMenu(Account& acc, std::vector<Account>& accounts) {
	std::string choice;
	double amount = 0.0;
	std::vector<Deposit> deposits = loadDeposits();

	while (true) {
		std::cout << "\n1. Make a deposit\n";
		std::cout << "2. See deposit\n";
		std::cout << "3. Exit\n";
		std::getline(std::cin, choice);

		if (choice == "1") {
			std::string expiryDateStr,amountStr;
			std::cout << "Enter deposit amount: ";
			std::getline(std::cin, amountStr);

			if (amountStr.empty() || !std::all_of(amountStr.begin(), amountStr.end(), [](char c) { return std::isdigit(c) || c == '.'; }) || std::count(amountStr.begin(), amountStr.end(), '.') > 1) {
				std::cout << "Invalid deposit amount. Please enter a valid number.\n";
				continue;
			}

			amount = std::stod(amountStr);

			if (amount > acc.getAmount()) {
				std::cout << "Insufficient balance.\n";
				continue;
			}

			std::cout << "Enter expiry date (YYYY-MM-DD): ";
			std::getline(std::cin, expiryDateStr);

			std::regex dateFormat("([0-9]{4})-([0-9]{2})-([0-9]{2})");
			if (!std::regex_match(expiryDateStr, dateFormat)) {
				std::cout << "Invalid date format.\n";
				continue;
			}
			
			auto expiryDate = parseDate(expiryDateStr);
			auto now = std::chrono::system_clock::now();
			auto sixMonthsFromNow = now + std::chrono::months(6);

			if (expiryDate < sixMonthsFromNow) {
				std::cout << "The expiry date should be at least 6 months from now.\n";
				continue;
			}

			acc.setAmount(acc.getAmount() - amount);

			auto depositDateStr = formatDate(now);
			deposits.push_back(Deposit{ acc.getName(), amount, parseDate(depositDateStr), parseDate(expiryDateStr) });

			std::cout << "Deposit added successfully.\n";
			saveDeposits(deposits);
			updateAccount(accounts, acc);
			saveAccount(accounts);
		}
		else if (choice == "2") {
			displayDeposits(acc);
		}
		else if (choice == "3") {
			return;
		}
		else {
			std::cout << "Invalid choice. Try again.\n";
		}
	}
}

int daysBetween(const std::chrono::system_clock::time_point& start, const std::chrono::system_clock::time_point& end) {
	return std::chrono::duration_cast<std::chrono::hours>(end - start).count() / 24;
}
double calculateAccruedAmount(double initialAmount, int days) {

	double dailyInterest = 0.0025;

	for (int i = 0;i < days;i++) {
		initialAmount *= 1.0025;
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
		double accruedAmount = calculateAccruedAmount(deposit.amount, days); // 0.25% interest per day

		std::cout << "Original Amount: " << deposit.amount << " ";
		std::cout << "Amount as of " << formatDate(today) << ": " << accruedAmount << " ";
		std::cout << "Deposit Date: " << formatDate(deposit.depositDate) << " ";
		std::cout << "Expiry Date: " << formatDate(deposit.expiryDate) << std::endl;
	}
}