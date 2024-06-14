#include <gtest/gtest.h>
#include "../solution.hpp"
#include "../physical_device.h"
#include <thread>
#include "../custom_exceptions.hpp"

// Test fixture for setting up the test environment
class ServerTest : public ::testing::Test {
protected:
    Server server;
};

// Test adding a device
TEST_F(ServerTest, AddDevice) {
    Device device(1);
    server.addDevice(device);
    EXPECT_EQ(server.createAction("g name 0").getResult(), "");
}

// Test setting and getting device name
TEST_F(ServerTest, SetAndGetDeviceName) {
    Device device(1);
    server.addDevice(device);
    server.createAction("s name 0 device_name").getResult();
    EXPECT_EQ(server.createAction("g name 0").getResult(), "device_name");
}

// // Test setting and getting device parameters
TEST_F(ServerTest, SetAndGetDeviceParams) {
    Device device(1);
    server.addDevice(device);
    server.createAction("s params 0 1,3,2,0,255,67,67").getResult();
    EXPECT_EQ(server.createAction("g params 0").getResult(), "0,1,2,3,67,67,255");
}

// Test invalid device ID
TEST_F(ServerTest, CheckInvalidDeviceId) {
    EXPECT_EQ(server.createAction("g name 10").getResult(), InvalidDeviceId("10").what());
}

// Test invalid Action
TEST_F(ServerTest, CheckInvalidAction) {
    EXPECT_EQ(server.createAction("randomletters").getResult(),InvalidAction("randomletters").what());
}

// Test invalid Command
TEST_F(ServerTest, CheckInvalidCommand) {
    EXPECT_EQ(server.createAction("s tcp 0 True").getResult(),InvalidCommand("set_tcp").what());
}

// Test invalid Id (negative)
TEST_F(ServerTest, CheckInvalidIdNegative) {
    EXPECT_EQ(server.createAction("s name -10 True").getResult(),InvalidDeviceId("-10").what());
}

// Test invalid parameter structure
TEST_F(ServerTest, CheckInvalidParamStructure) {
    EXPECT_EQ(server.createAction("s params 0 9,3,4,5,#$5,7").getResult(),InvalidParameterStruct("9,3,4,5,#$5,7").what());
}

// Test invalid parameter value
TEST_F(ServerTest, CheckInvalidParamValue2) {
    EXPECT_EQ(server.createAction("s params 0 9,3,4, 5,5,70").getResult(),InvalidCommandStruct("s params 0 9,3,4, 5,5,70","5,5,70").what());

}


// Test invalid parameter structure
TEST_F(ServerTest, CheckInvalidParamValue) {
    EXPECT_EQ(server.createAction("s params 0 9,3,4,5,5,700").getResult(),InvalidParameterValue("700").what());
}

// Test concurrent adding of devices
TEST_F(ServerTest, ConcurrentAddDevices) {
    std::thread addThread1(&Server::addDevice, &server, Device(1));
    std::thread addThread2(&Server::addDevice, &server, Device(2));
    addThread1.join();
    addThread2.join();

    // Check that both devices were added correctly
    EXPECT_NO_THROW(server.createAction("g name 0").getResult());
    EXPECT_NO_THROW(server.createAction("g name 1").getResult());
}

// Test concurrent actions
TEST_F(ServerTest, ConcurrentActions) {
    server.addDevice(Device(1));
    server.addDevice(Device(2));

    auto action1 = [&]() { return server.createAction("s name 0 device_0_name").getResult(); };
    auto action2 = [&]() { return server.createAction("s name 1 device_1_name").getResult(); };

    std::thread actionThread1(action1);
    std::thread actionThread2(action2);

    actionThread1.join();
    actionThread2.join();

    EXPECT_EQ(server.createAction("g name 0").getResult(), "device_0_name");
    EXPECT_EQ(server.createAction("g name 1").getResult(), "device_1_name");
}



// Concurrent get operations test
TEST_F(ServerTest, ConcurrentGetOperations) {
    const int num_threads = 5;
    std::vector<std::thread> threads(num_threads);
    std::vector<std::string> results(num_threads);

    server.createAction("s name 0 Name_0").getResult();
    server.createAction("s name 1 Name_1").getResult();
    server.createAction("s name 2 Name_2").getResult();

    // Create threads to perform concurrent get operations
    for (int i = 0; i < num_threads; ++i) {
        threads[i] = std::thread([this, &results, i]() {
            try {
                results[i] = server.createAction("g name " + std::to_string(i % 3)).getResult();
            } catch (const std::exception& e) {
                results[i] = e.what();
            }
        });
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    // Assert that all threads obtained correct results
    for (int i = 0; i < num_threads; ++i) {
        EXPECT_EQ(results[i], "Name_" + std::to_string(i % 3)); // Assuming expected results based on your application
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
