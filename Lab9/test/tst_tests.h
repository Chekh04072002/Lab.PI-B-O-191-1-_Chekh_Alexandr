#ifndef TST_TESTS_H
#define TST_TESTS_H

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <IKeypad.h>
#include <ILatch.h>
#include <lockcontroller.h>

using namespace testing;

struct MockKeypad : IKeypad
{
    MOCK_METHOD
    (
        bool,
        isActive,
        (),
        (override)
    );

    MOCK_METHOD
    (
        void,
        wait,
        (),
        (override)
    );

    MOCK_METHOD
    (
        PasswordResponse,
        requestPassword,
        (),
        (override)
    );

};


struct MockLatch : ILatch
{
    MOCK_METHOD
    (
        bool,
        isActive,
        (),
        (override)
    );

    MOCK_METHOD
    (
        DoorStatus,
        open,
        (),
        (override)
    );

    MOCK_METHOD
    (
        DoorStatus,
        close,
        (),
        (override)
    );

    MOCK_METHOD
    (
        DoorStatus,
        getDoorStatus,
        (),
        (override)
    );

};


TEST(Testing, test1)
{

    const short expected_calls_number = 1;
    MockKeypad keypad;
    MockLatch latch;
    LockController controller(&keypad, &latch);

      EXPECT_CALL(keypad, wait())
            .Times(expected_calls_number)
            .WillOnce(Return());


    controller.wait();

}


TEST(Testing, test2)
{
    const short expected_calls_number = 1;
    MockKeypad keypad;
    MockLatch latch;
    LockController controller(&keypad, &latch);

    EXPECT_CALL(latch, getDoorStatus())
            .Times(expected_calls_number)
            .WillOnce(Return(DoorStatus::CLOSE));

    bool is_open = controller.isDoorOpen();

    ASSERT_FALSE(is_open);
}


TEST(Testing, test3)
{
    const short expected_calls_number = 1;
    MockKeypad keypad;
    MockLatch latch;
    LockController controller(&keypad, &latch);

    EXPECT_CALL(latch, getDoorStatus())
            .Times(expected_calls_number)
            .WillOnce(Return(DoorStatus::OPEN));

    bool is_open = controller.isDoorOpen();

    ASSERT_TRUE(is_open);
}


TEST(Testing, test4)
{
    const short expected_calls_number = 1;
    MockKeypad keypad;
    MockLatch latch;
    LockController controller(&keypad, &latch);

    EXPECT_CALL(latch, open())
            .Times(expected_calls_number)
            .WillOnce(Return(DoorStatus::OPEN));

    DoorStatus door_status_test = controller.unlockDoor();

    ASSERT_EQ(DoorStatus::OPEN, door_status_test);
}


TEST(Testing, test5)
{
    const short expected_calls_number = 1;
    MockKeypad keypad;
    MockLatch latch;
    LockController controller(&keypad, &latch);

    EXPECT_CALL(latch, close())
            .Times(expected_calls_number)
            .WillOnce(Return(DoorStatus::CLOSE));

    DoorStatus door_status_test = controller.unlockDoor();

    ASSERT_EQ(DoorStatus::CLOSE, door_status_test);
}


TEST(Testing, test6)
{
    const short expected_calls_number = 1;
    MockKeypad keypad;
    MockLatch latch;
    LockController controller(&keypad, &latch);

    EXPECT_CALL(keypad, isActive())
            .Times(expected_calls_number)
            .WillOnce(Return(true));

    EXPECT_CALL(latch, isActive())
            .Times(expected_calls_number)
            .WillOnce(Return(true));

    HardWareStatus hard_ware_status = controller.hardWareCheck();

    ASSERT_EQ(HardWareStatus::OK, hard_ware_status);
}

TEST(Testing, test7)
{
    MockKeypad keypad;
    MockLatch latch;
    LockController controller(nullptr, &latch);

    EXPECT_CALL(keypad, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(true));

    EXPECT_CALL(latch, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(true));

    HardWareStatus hard_ware_status = controller.hardWareCheck();

    ASSERT_EQ(HardWareStatus::ERROR, hard_ware_status);

}


TEST(Testing, test8)
{
    MockKeypad keypad;
    MockLatch latch;
    LockController controller(&keypad, &latch);

    EXPECT_CALL(keypad, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(true));

    EXPECT_CALL(latch, isActive())
            .Times(AtLeast(0))
            .WillOnce(Return(false));

    HardWareStatus hard_ware_status = controller.hardWareCheck();

    ASSERT_EQ(HardWareStatus::ERROR, hard_ware_status);
}


TEST(Testing, test9)
{
    const short expected_calls_number = 1;
    MockKeypad keypad;
    MockLatch latch;
    LockController controller(&keypad, &latch);

    PasswordResponse user_input;
    user_input.status = PasswordResponse::Status::OK;
    user_input.password = "0000";

    EXPECT_CALL(keypad, requestPassword())
            .Times(expected_calls_number)
            .WillOnce(Return(user_input));

    bool correct_password = controller.isCorrectPassword();

    ASSERT_TRUE(correct_password);
}

TEST(Testing, test10)
{
    const short expected_calls_number = 1;
    MockKeypad keypad;
    MockLatch latch;
    LockController controller(&keypad, &latch);

    PasswordResponse user_input;
    user_input.status = PasswordResponse::Status::OK;
    user_input.password = "1111";

    EXPECT_CALL(keypad, requestPassword())
            .Times(expected_calls_number)
            .WillOnce(Return(user_input));

    bool correct_password = controller.isCorrectPassword();

    ASSERT_FALSE(correct_password);
}


TEST(Testing, test11)
{
    MockKeypad keypad;
    MockLatch latch;
    LockController controller(&keypad, &latch);

    PasswordResponse user_input_old;
    user_input_old.status = PasswordResponse::Status::OK;
    user_input_old.password = "0000";

    PasswordResponse user_input_new;
    user_input_new.status = PasswordResponse::Status::OK;
    user_input_new.password = "1111";

    EXPECT_CALL(keypad, requestPassword())
            .Times(3)
            .WillOnce(Return(user_input_old))
            .WillOnce(Return(user_input_new))
            .WillOnce(Return(user_input_new)); //

    controller.resetPassword();
    bool correct_password = controller.isCorrectPassword();

    ASSERT_TRUE(correct_password);
}

TEST(Testing, test12)
{
    MockKeypad keypad;
    MockLatch latch;
    LockController controller(&keypad, &latch);

    PasswordResponse user_input_old;
    user_input_old.status = PasswordResponse::Status::OK;
    user_input_old.password = "0000";

    PasswordResponse user_input_new;
    user_input_new.status = PasswordResponse::Status::OK;
    user_input_new.password = "9876";


    EXPECT_CALL(keypad, requestPassword())
            .Times(4)
            .WillOnce(Return(user_input_old))
            .WillOnce(Return(user_input_new))
            .WillOnce(Return(user_input_old))
            .WillOnce(Return(user_input_new));


    controller.resetPassword();
    user_input_old.password = user_input_new.password;
    user_input_new.password = "1111";
    controller.resetPassword();

    bool correct_password = controller.isCorrectPassword();

    ASSERT_TRUE(correct_password);
}


#endif // TST_TESTS_H
