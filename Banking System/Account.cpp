#include "Account.h"
#include "AppUtils.h"


Account::Account():amount(0), name(""), password("") {}
Account::Account(double amount, const std::string& name, const std::string& password)
    : amount(amount), name(name), password(password) {}
extern void sendEmailWithCode(const std::string& email, const std::string& code);

bool Account::createAccount(std::vector<Account>& accounts) {
    std::set<std::string> names;
    for (const auto& acc : accounts) {
        names.insert(acc.getName());
    }

    std::string tempName, email;
    std::cout << "\nEnter your Name (or 0 to return to the main menu): ";
    std::getline(std::cin, tempName);
    if (tempName == "0") return false;

    while (!checkName(tempName, names)) {
        std::cout << "Enter a new one (or 0 to return to the main menu): ";
        std::getline(std::cin, tempName);
        if (tempName == "0") return false;
    }
    this->name = tempName;

    std::cout << "\nEnter your Email (or 0 to return to the main menu): ";
    std::getline(std::cin, email);
    if (email == "0") return false;

    
    std::string pythonCommand = "python \"C:\\Users\\Simeon\\source\\repos\\Banking System\\PythonEmailService\\send_email.py\" " + email;
    std::system(pythonCommand.c_str());

    
    std::ifstream infile("verification_code.txt");
    std::string verificationCode;
    std::getline(infile, verificationCode);
    infile.close();

    std::string inputCode;
    std::cout << "Enter the verification code sent to your email: ";
    std::getline(std::cin, inputCode);
    if (inputCode == "0" || inputCode != verificationCode) {
        std::cout << "Invalid or incorrect verification code.\n";
        return false;
    }

    std::string tempPass;
    std::cout << "\nEnter your password (or 0 to return to the main menu): ";
    std::getline(std::cin, tempPass);
    if (tempPass == "0") return false;

    while (!checkPassword(tempPass)) {
        std::cout << "Enter a new one (or 0 to return to the main menu): ";
        std::getline(std::cin, tempPass);
        if (tempPass == "0") return false;
    }

    double deposit = 0.0;
    std::string depositStr;
    std::cout << "\nEnter a deposit (minimum 10): ";
    std::getline(std::cin, depositStr);
    if (depositStr == "0") return false;

    try {
        deposit = std::stod(depositStr);
        if (deposit < 10.0) throw std::invalid_argument("Deposit must be at least 10");
    }
    catch (const std::invalid_argument&) {
        std::cout << "Invalid deposit amount.\n";
        return false;
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


//bool Account::createAccountTest(std::vector<Account>& accounts, const std::string& name, const std::string& password, double deposit) {
//    if (deposit < 10.0) return false;
//    if (!checkName(name, std::set<std::string>(begin(accounts), end(accounts)))) return false;
//    if (!checkPassword(password)) return false;
//
//    Account newAccount(deposit, name, password);
//    accounts.push_back(newAccount);
//    return true;
//}

