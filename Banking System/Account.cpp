#include "Account.h"
#include "AppUtils.h"

Account::Account():amount(0), name(""), password("") {}

Account::Account(double amount, std::string name, std::string password)
	: amount(amount), name(name), password(password) {}

bool Account::createAccount(std::vector<Account>& accounts) {
    std::set<std::string> names;
    for (const auto& acc : accounts) {
        names.insert(acc.getName());
    }

    std::string tempName;
    std::cout << "\nEnter your Name (or 0 to return to the main menu): ";
    std::getline(std::cin, tempName);

    if (tempName == "0") {
        return false;
    }

    while (!checkName(tempName, names)) {
        std::cout << "Enter a new one (or 0 to return to the main menu): ";
        std::getline(std::cin, tempName);

        if (tempName == "0") {
            return false;
        }
    }
    this->name = tempName;

    std::string tempPass;
    std::cout << "\nEnter your password (or 0 to return to the main menu): ";
    std::getline(std::cin, tempPass);
    if (tempPass == "0") {
        return false;
    }

    while (!checkPassword(tempPass)) {
        std::cout << "Enter a new one (or 0 to return to the main menu): ";
        std::getline(std::cin, tempPass);

        if (tempPass == "0") {
            return false;
        }
    }

    double deposit = 0.0;
    std::string depositStr;
    while (true) {
        std::cout << "\nEnter a deposit (minimum 10): ";
        std::getline(std::cin, depositStr);

        if (depositStr == "0") {
            return false;
        }

        try {
            deposit = std::stod(depositStr);
            if (deposit >= 10.0) {
                break;
            }
        }
        catch (const std::invalid_argument&) {}

        std::cout << "Invalid deposit amount.\n";
    }

    this->amount = deposit;

    Account newAccount(amount, tempName, tempPass);

    accounts.push_back(newAccount);

    return true;
}


void Account::print() {
	std::cout << name<<"\n";
	std::cout << password<<"\n";
	std::cout << amount<<"\n";

}

void Account::printAmount() {
	std::cout << "\nAvailable:"<<getAmount();
}

bool checkName(const std::string& name, std::set<std::string> names) {
	while (names.find(name) != names.end()) {
		std::cout << "Invalid username, already taken.\n";
		return false;
	}
	for (int i = 0; i < name.size();i++) {
		if (!isalpha(name[i])) {
			std::cout << "Name should only contain letters.\n";
			return false;
		}
	}
	return !name.empty();
}
bool checkPassword(const std::string& password) {
	if (password.size() < 8) {
		std::cout << "Password must be at least 8 charecters\n";
		//return false;
	}

	bool capital = false;
	bool digit = false;
	bool letter = false;
	for (int i = 0; i < password.size();i++) {
		if (capital==false && password[i] >= 65 && password[i] <= 90) {
			capital = true;
		}
		if (digit == false && password[i] >= 48 && password[i] <= 57) {
			digit = true;
		}
		if (!letter && password[i] >= 97 && password[i] <= 122) {
			letter = true;
		}
	}
	if (!capital) {
		std::cout << "There must be at least 1 capital letter \n";
		//return false;
	}
	if (!digit) {
		std::cout << "There must be at least 1 digit \n";
		//return false;
	}
	if (!letter) {
		std::cout << "There must be at least 1 letter \n";
		//return false;
	}
	if (password.size() >= 8 && letter && digit && capital) {
		return true;
	}

	return false;
}


	