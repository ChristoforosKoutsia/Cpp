#include <string>
#include "physical_device.h" 
#include <vector>
#include <algorithm>
#include <condition_variable>
#include <iostream>
#include <memory>
#include "solution.hpp"
#include <sstream>
#include <variant>
#include "custom_exceptions.cpp"

bool isNumeric(const std::string& str) {
    for (char c : str) {
        if (c == 32 && str.size() > 1)
        {
            continue; // spaces at the beggining are allowed
        }
        if (!std::isdigit(c)) {
            return false;
        }
    }
    return true;
}


std::vector<uint8_t> strToIntVec(const std::string& str)
{
    // This is helper function which converts a string to vector of unsigned integers (0-255) with the 
    //following specifications : 
    // - String shall have only numerical values separated by comma (e.g "1,2,3,6...") 
    // - Every value between commas shall be  in range (0-255)
    std::vector<uint8_t> params;
    std::string token;
    std::istringstream iss(str);
    while (std::getline(iss, token, ',')) 
    {
    // Try to convert token to an integer
        if (token.empty() or !isNumeric(token) )
        {
            throw InvalidParameterStruct(str);  
        }
        else 
        {
            int num = std::stoi(token);
            if (num >=0 && num <=255)
            {
                 params.push_back(num);
            }
            else
            {
                 throw InvalidParameterValue(token);
            }
           
        }                             

    }
    return params; 
}


std::string vectorToString(const std::vector<uint8_t>& vec) {
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
        if (i != 0) {
            oss << ",";
        }
        oss << static_cast<int>(vec[i]);
    }
    return oss.str();
}


Device:: Device(int physical_id)
{
    m_id = physical_id;
    //std::lock_guard<std::mutex> lock(*lib::getMutex());
    lib::getMutex()->lock();
    //m_physical_device = std::make_shared<lib::Physical_device>(lib::getHardware(physical_id));
    m_physical_device = new lib::Physical_device(lib::getHardware(physical_id));
    m_some_factor     = lib::getDefaultFactor();
    lib::getMutex()->unlock();
}

// Device(int physical_id, int fixed_factor)
// {
//     m_some_factor = fixed_factor;
//     m_id = physical_id;
//     std::lock_guard<std::mutex> lock(*lib::getMutex());
//     m_physical_device = std::make_shared<lib::Physical_device>(lib::getHardware(physical_id));
// }

 std::string Device:: getName() const
{
    return m_name;
}

void Device::setName(std::string const name)
{
    m_name = name;
}

void Device::setParams(const std::vector<uint8_t>& params)
{
    m_params = params;
}

std::vector<uint8_t> Device:: getParams() const
{
    return m_params;
}


int Device:: getId() const
{
    return m_id;
}




Action::Action(std::string const &command, Server& server)
{
    m_command = command;
    m_server = &server; // use pass by reference so server object is manipulated here
}

std::string Action::getResult() const
{
try
{
    /* code */


    std::istringstream iss(m_command);
    std::string action, attribute, device_id_str ,params,res_command;
    iss >> action >> attribute >> device_id_str>>params;

    // Check of action
    if (action == "s")
    {
        res_command = "set";

    }
    else if (action == "g")
    {
        res_command = "get";
    }
    else
    {
        throw InvalidAction(action);
    }

    // Check of attribute could be literally anything. The check will be done aftwerwards in executeAction method
    res_command += "_" + attribute;
 
    // convert id to integer and check that is >0
    int id;
    id = std::stoi(device_id_str);
    if (id < 0)
    {
        throw InvalidDeviceId(device_id_str);
    }

     
        return m_server->executeAction(res_command,id,params);
}
catch(const std::exception& e)
{
    return( e.what());
}
}


// define static_member m_devices
std::vector<Device> Server::m_devices;

Server::Server()
{
    // Register actions
    actionMap["set_name"] = [this](int id, const std::string& param) -> std::string{ return setDevName(id, param); };
    actionMap["set_params"] = [this](int id, const std::string& param) -> std::string{ return setDevParams(id, strToIntVec(param)); };
    actionMap["get_name"] = [this](int id, const std::string&) -> std::string { return getDevName(id); };
    actionMap["get_params"] = [this](int id, const std::string&) -> std::string { return getDevParams(id); };
}

void Server::addDevice (const Device& dev)
{
    std::lock_guard<std::mutex> lock(mutex_);
    m_devices.push_back(dev);
    m_devices_id.push_back(m_devices.size()-1);
}


Action Server::createAction(std::string command)
{
    // create object action
    return Action(command, *this); // pass also current instance of server since Action object should know the current devices etc
             
}

const std::string Server::executeAction(const std::string& action, int id, const std::string& param = "") {
    if (actionMap.find(action) != actionMap.end()) {
        return actionMap[action](id, param);
    } else {
        throw InvalidCommand(action);
    }
}

// implementationn of private methods
const std::string Server::setDevName(int id, const std::string& name)
{   
    // locking the mutex so there are no race condition
    std::lock_guard<std::mutex> lock(mutex_);

    if (id >= 0 && id < m_devices.size())
    {
        m_devices[id].setName(name);
        return "";
    }
    else
    {
        throw std::invalid_argument("Invalid token:");
    }

}

const std::string Server::setDevParams(int id, const std::vector<uint8_t> &params)
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (id >= 0 && id < m_devices.size())
    {
        m_devices[id].setParams(params);
        return "";
    }
    else
    {
        throw InvalidDeviceId(std::to_string(id));
    }
}

const std::string Server::getDevName(int id) 
{   
    // locking the mutex so there are no race condition
    std::lock_guard<std::mutex> lock(mutex_);

    if (id >= 0 && id < m_devices.size())
    {
        return (m_devices[id].getName());
    }
    else
    {
        throw InvalidDeviceId(std::to_string(id)); 
    }

}

const std::string Server::getDevParams(int id) 
{   
    // locking the mutex so there are no race condition
    std::lock_guard<std::mutex> lock(mutex_);

    if (id >= 0 && id < m_devices.size())
    {
        return vectorToString(m_devices[id].getParams());
    }
    else
    {
        throw InvalidDeviceId(std::to_string(id));
    }

}

  
// Sample main() functon - might be useful for quick testing 
int main()
{
    Server server;
    std::string y;
    //server.addDevice(Device(97));
    server.addDevice(Device(98));
    server.addDevice(Device(99));
    server.addDevice(Device(3));
    server.addDevice(Device(98));
    server.addDevice(Device(99));
    server.addDevice(Device(3));
    server.addDevice(Device(98));
    server.addDevice(Device(99));
    server.addDevice(Device(3));
    Server server2;
    server2.addDevice(Device(8));
   std::cout<<server.createAction("s name 0 pc_magnet_1").getResult()<<std::endl;      
   std::cout<<server.createAction("s name 1 some_name").getResult()<<std::endl;
   std::cout<<server.createAction("s params 0 4,3,2,1,0,44,55,44,55").getResult()<<std::endl;
    

    std::cout<<server.createAction("g name 0").getResult()<<std::endl;                              // = "pc_magnet_1"
    std::cout<<server.createAction("g name 1").getResult()<<std::endl;                              // = "some_name"
    std::cout<<server.createAction("g name 2").getResult()<<std::endl;                     // = "2"

    std::cout<<server.createAction("g name 3").getResult()<<std::endl;                              // = <Error>
    std::cout<<server.createAction("randomletters").getResult()<<std::endl;                          // = <Error>
    std::cout<<server.createAction("g name notanumber").getResult()<<std::endl;                     // = <Error>

    std::cout<<server.createAction("s params 0 4,3,2,1,0,44,55,44,55").getResult()<<std::endl;      // = ""
    std::cout<<server.createAction("s params 0 4,3,2,1,0,44,55,44,55,9999").getResult()<<std::endl; // = <Error>
    std::cout<<server.createAction("s params 0 4,3,,2").getResult()<<std::endl;                     // = <Error>
    std::cout<<server.createAction("g params 0").getResult()<<std::endl;                            // = "0,1,2,3,4,44,44,55,55"

return 0;
}