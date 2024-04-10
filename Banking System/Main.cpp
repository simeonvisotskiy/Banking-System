#include "Account.h"
#include "AppUtils.h"


int main() {
    //Account acc;
	int choice = 0;
	std::vector<Account>accounts = getNamesAndPass();

	while (true)
	{
		std::cout << "1. Log In\n";
		std::cout << "2. Sign Up\n";
		std::cout << "3. Exit\n";
		std::cin >> choice;

		switch (choice) {
		case 1: {
			Account logInAccount;
			if (logIn(accounts, logInAccount)) {
				mainMenu(logInAccount, accounts);
			}
			break;
		}
			
		case 2: {
			Account newAccount;
			newAccount.createAccount(accounts);
			//saveAccount(accounts);
			mainMenu(newAccount, accounts);
			break;
		}
		case 3:
			saveAccount(accounts);
			return 0;
		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
	}

	saveAccount(accounts);
	return 0;
}