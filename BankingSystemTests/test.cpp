#include "Account.h"
#include "pch.h"
#include <string>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(AccountTests, AccountInitialization) {
    
    Account testAccount(100.0, "TestUser", "TestPass1!");


    EXPECT_EQ(testAccount.getAmount(), 100.0) << "The account balance should be initialized to 100.0";

    EXPECT_EQ(testAccount.getName(), "TestUser") << "The account name should be 'TestUser'";

    EXPECT_EQ(testAccount.getPassword(), "TestPass1!") << "The account password should be 'TestPass1!'";
}