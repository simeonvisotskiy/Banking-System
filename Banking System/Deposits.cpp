#include"Deposits.h"
#include"Account.h"
#include"AppUtils.h"


std::chrono::system_clock::time_point parseDate(const std::string& dateStr) {
	std::tm tm = {};
	std::istringstream ss(dateStr);
	ss >> std::get_time(&tm, "%Y-%m-%d");
	return std::chrono::system_clock::from_time_t(std::mktime(&tm));
}

std::string formatDate(const std::chrono::system_clock::time_point& date) {
	std::time_t t = std::chrono::system_clock::to_time_t(date);
	std::tm tm{};
	localtime_s(&tm, &t);
	std::ostringstream oss;
	oss << std::put_time(&tm, "%Y-%m-%d");
	return oss.str();
}

std::vector<Deposit> loadDeposits() {

	std::vector<Deposit>deposits;
	std::ifstream file("deposts.txt");
	std::string line;
	while (std::getline(file, line)) {
		std::stringstream ss (line);
		std::string uName, depositDate, expiryDate;
		double amount;
		if (ss >> uName >> amount >> depositDate >> expiryDate) {
			
			Deposit deposit{ uName,amount,parseDate(depositDate),parseDate(expiryDate) };
			deposits.push_back(deposit);
			
		}
	}
	return deposits;
}

void saveDeposits(const std::vector<Deposit>& deposits) {
	std::ofstream file("deposits.txt", std::ios::app);
	for (const auto& deposit : deposits) {
		file << deposit.name << " "
			<< deposit.amount << " "
			<< formatDate(deposit.depositDate) << " "
			<< formatDate(deposit.expiryDate) << "\n";
	}
	file.close();
}

void addAndSaveDeposit(const std::string& username, double amount, const std::string& depositDateStr, const std::string& expiryDateStr) {
	std::vector<Deposit> deposits = loadDeposits();

	deposits.push_back(Deposit{
		username,
		amount,
		parseDate(depositDateStr),
		parseDate(expiryDateStr)
		});

	// Save the updated list of deposits.
	saveDeposits(deposits);
}

std::vector<Deposit>loadDeposits(const std::string& name) {
	std::vector<Deposit>deposits;
	std::ifstream file("deposits.txt");
	if (file.is_open()) {
		std::string line;
		while (std::getline(file, line)) {
			std::stringstream ss(line);
			std::string uName, depositDate, expiryDate;
			double amount;
			if (ss >> uName >> amount >> depositDate >> expiryDate) {
				if (name == uName) {
					deposits.push_back(Deposit{ uName,amount,parseDate(depositDate),parseDate(expiryDate) });
				}
			}
		}
	}
	return deposits;
}