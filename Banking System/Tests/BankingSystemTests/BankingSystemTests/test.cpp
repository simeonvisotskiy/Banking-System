#include "pch.h"
#include "Account.h"
#include <vector>
#include <string>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}


TEST(AccountTests, AccountCreationVerification) {
    Account testAccount(100.0, "TestUser", "TestPass1!");

    EXPECT_EQ(testAccount.getAmount(), 100.0) << "Account balance should be initialized to 100.0";
    EXPECT_EQ(testAccount.getName(), "TestUser") << "Account name should match 'TestUser'";
    EXPECT_EQ(testAccount.getPassword(), "TestPass1!") << "Account password should match 'TestPass1!'";
}

//std::vector<Account> loadMockAccounts() {
//    std::vector<Account> accounts;
//    accounts.emplace_back(100.0, "User1", "Password1!");
//    accounts.emplace_back(200.0, "User2", "Password2!");
//    return accounts;
//}
//
//// Function to check if the username is taken
//bool isNameTaken(const std::string& name, const std::vector<Account>& accounts) {
//    for (const auto& account : accounts) {
//        if (account.getName() == name) {
//            return true;
//        }
//    }
//    return false;
//}
//
//// Test fixture
//class AccountCreationTest : public ::testing::Test {
//protected:
//    std::vector<Account> accounts;
//
//    void SetUp() override {
//        accounts = loadMockAccounts(); // Load mock data
//    }
//};
//
//TEST_F(AccountCreationTest, CreateAccount_Success) {
//    std::string name = "NewUser";
//    std::string password = "Password3!";
//    double initialDeposit = 50.0;
//
//    bool nameTaken = isNameTaken(name, accounts);
//    bool passwordValid =checkPassword(password);  // Assuming Account class has a static method to validate passwords
//    bool depositValid = initialDeposit >= 10.0;
//
//    ASSERT_FALSE(nameTaken) << "Username should not be taken.";
//    ASSERT_TRUE(passwordValid) << "Password should meet criteria (1 letter, 1 capital letter, 1 digit).";
//    ASSERT_TRUE(depositValid) << "Initial deposit should be at least 10.";
//
//    // Assuming Account constructor adds the account to the list if all checks pass
//    if (!nameTaken && passwordValid && depositValid) {
//        accounts.emplace_back(initialDeposit, name, password);
//    }
//
//    // Verify that the new account was added
//    EXPECT_EQ(3, accounts.size()) << "There should now be 3 accounts in the system.";
//}