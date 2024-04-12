#include "Account.h"
#include "AppUtils.h"
#include"FXData.h"


int main() {


	//std::map<std::string, double> exchangeRates;

	//std::string apiKey = "0ff731280066f9b0115cacdc";
	//std::string baseCurrency = "BGN"; // or any base currency you're interested in
	////std::string response = fetchExchangeRate(apiKey, baseCurrency);

	////std::cout << "Response: \n" << response << std::endl;
	//return 0;
    Account acc;
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