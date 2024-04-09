#include "Account.h"
#include "AppUtils.h"

int main() {
    Account acc;
	int choice = 0;

	while (true)
	{
		std::cout << "1. Log In\n";
		std::cout << "2. Sign Up\n";
		std::cout << "3. Exit\n";
		std::cin >> choice;

		switch (choice) {
		case 1:
			if (logIn(acc)) {
				mainMenu(acc);
			}
			
			break;
		case 2:
			acc.createAccount();
			mainMenu(acc);
			break;
		case 3:
			return 0;
		default:
			std::cout << "Invalid choice. Please try again.\n";
		}
	}


	return 0;
}