#include "Account.h"
#include "AppUtils.h"
#include"FXData.h"
#include <gtest/gtest.h>

TEST(AccountTests, AccountInitialization) {

	Account testAccount(100.0, "TestUser", "TestPass1!");


	EXPECT_EQ(testAccount.getAmount(), 100.0) << "The account balance should be initialized to 100.0";

	EXPECT_EQ(testAccount.getName(), "TestUser") << "The account name should be 'TestUser'";

	EXPECT_EQ(testAccount.getPassword(), "TestPass1!") << "The account password should be 'TestPass1!'";
}


int main() {
	

	Account acc;
	std::string choice;
	std::vector<Account>accounts = getNamesAndPass();

	while (true)
	{
		std::cout << "1. Log In\n";
		std::cout << "2. Sign Up\n";
		std::cout << "3. Exit\n";
		std::cin >> choice;
		std::cin.ignore();
	
		if (choice == "1") {
			Account logInAccount;
			if (logIn(accounts, logInAccount)) {
				mainMenu(logInAccount, accounts);
			}
		}
		else if (choice == "2") {
			Account newAccount;
			if (!newAccount.createAccount(accounts)) {
				continue;
			}
			saveAccount(accounts);
			mainMenu(newAccount, accounts);
		}
		else if (choice == "3") {
			saveAccount(accounts);
			return 0;
		}
		else {
			std::cout << "Invalid choice. Please try again.\n";
		}
	}
	saveAccount(accounts);
	return 0;
}