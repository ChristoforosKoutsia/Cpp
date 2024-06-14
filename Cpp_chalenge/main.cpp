#include "solution.hpp"
#include <thread>
#include <iostream>

// Function to simulate concurrent addDevice operations
void addDevicesConcurrently(Server &server, int numDevices) {
    for (int i = 0; i < numDevices; ++i) {
        server.addDevice(Device(i));
    }
}

// Function to simulate concurrent action creation and execution
void executeActionsConcurrently(Server &server, const std::vector<std::string>& commands) {
    for (const auto& command : commands) {
        server.createAction(command).getResult();
    }
}

int main()
{
   Server server;

    // // Create a vector of commands to be executed concurrently
    // std::vector<std::string> commands = {
    //     "s name 0 pc_magnet_1",
    //     "s name 1 some_name",
    //     "s params 0 4,3,2,1,0,44,55,44,55",
    //     "g name 0",
    //     "g name 1",
    //     "g params 0",
    //     "randomletters",
    //     "g name notanumber",
    //     "s params 0 4,3,2,1,0,44,55,44,55,9999",
    //     "s params 0 4,3,,2"
    // };

    // // Launch threads to add devices concurrently
    // std::thread addThread1(addDevicesConcurrently, std::ref(server), 10);
    // std::thread addThread2(addDevicesConcurrently, std::ref(server), 10);

    // // Launch threads to execute actions concurrently
    // std::thread actionThread1(executeActionsConcurrently, std::ref(server), std::ref(commands));
    // std::thread actionThread2(executeActionsConcurrently, std::ref(server), std::ref(commands));

    // // // Wait for all threads to complete
    // addThread1.join();
    // addThread2.join();
    // actionThread1.join();
    // actionThread2.join();

    // // Add more devices and execute actions to further test thread safety
    // server.addDevice(Device(98));
    // server.addDevice(Device(99));
    // server.addDevice(Device(3));

    // Server server2;
    // server2.addDevice(Device(8));


    std::cout << server.createAction("g name 0").getResult() << std::endl;
    std::cout << server.createAction("g name 1").getResult() << std::endl;
    std::cout << server.createAction("g name 2").getResult() << std::endl;
    std::cout << server.createAction("g name 3").getResult() << std::endl;
    std::cout << server.createAction("randomletters").getResult() << std::endl;
    std::cout << server.createAction("g name notanumber").getResult() << std::endl;
    std::cout << server.createAction("g params 0").getResult() << std::endl;
    std::cout << server.createAction("g name 1000").getResult() << std::endl;
    return 0;
}