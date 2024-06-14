#include "solution.hpp"
#include <thread>
#include <iostream>

/*
Main function just for demonstration purposes
*/

int main()
{
   Server server;

    server.addDevice(Device(98));
    server.addDevice(Device(99));
    server.addDevice(Device(3));

    Server server2;
    server2.addDevice(Device(8));
    std::cout << server.createAction("s name 0 dev_0").getResult() << std::endl;
    std::cout << server.createAction("s name 1 pc_magnet_1").getResult() << std::endl;
    std::cout << server.createAction("s name 2 pc_magnet_2").getResult() << std::endl;
    std::cout << server.createAction("g name 2").getResult() << std::endl;
    std::cout << server.createAction("g name 3").getResult() << std::endl;
    std::cout << server.createAction("g name 0").getResult() << std::endl;
    std::cout << server.createAction("g name 1").getResult() << std::endl;
    std::cout << server.createAction("s params 0 9,3,4,5,#$5,7").getResult() << std::endl;
    std::cout << server.createAction("randomletters").getResult() << std::endl;
    std::cout << server.createAction("g name notanumber").getResult() << std::endl;
    std::cout << server2.createAction("g params 0").getResult() << std::endl;
    std::cout << server.createAction("g name 1000").getResult() << std::endl;
    return 0;
}