//#include "gtest/gtest.h"
//#include "Account.h"
////#include "AppUtils.h"
//#include <string>
//#include <vector>
//
//class BankingTest : public ::testing::Test {
//protected:
//    std::vector<Account> accounts;
//
//    virtual void SetUp() {
//        accounts.push_back(Account(100.0, "User1", "Pass1!"));
//    }
//
//    virtual void TearDown() {
//        accounts.clear();
//    }
//};
//
//TEST_F(BankingTest, CreateAccountSuccess) {
//    std::string username = "NewUser";
//    std::string password = "Password1";
//    double deposit = 50;
//    Account newAccount;
//    bool result = newAccount.createAccountTest(accounts, username, password, deposit);
//    ASSERT_TRUE(result);
//    ASSERT_EQ(accounts.size(), 2); 
//}
//
//TEST_F(BankingTest, CreateAccountFailureDueToLowDeposit) {
//    std::string username = "NewUser1";
//    std::string password = "Password1";
//    double deposit = 5;
//    Account newAccount;
//    bool result = newAccount.createAccountTest(accounts, username, password, deposit);
//    ASSERT_FALSE(result);
//    ASSERT_EQ(accounts.size(), 1); 
//}
//
//TEST_F(BankingTest, SimpleCreateAccount) {
//    std::string name = "TestUser";
//    std::string password = "TestPass1";
//    double deposit = 20.0;
//
//    Account testAccount;
//    bool result = testAccount.createAccountTest(accounts, name, password, deposit);
//    ASSERT_TRUE(result);
//    ASSERT_EQ(accounts.size(), 2);
//}
//
//
//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    return RUN_ALL_TESTS();
//}