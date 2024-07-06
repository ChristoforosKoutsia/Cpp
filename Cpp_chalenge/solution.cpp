#include <iostream>
#include <sstream>
#include <thread>
#include "custom_exceptions.hpp"
#include "utils.hpp"
#include "solution.hpp"
#include "physical_device.h" 

// ################################ Device class implementation ###############################################
Device:: Device(int physical_id)
{
    lib::getMutex()->lock();
    m_physical_device = new lib::Physical_device(lib::getHardware(physical_id));
    m_some_factor     = lib::getDefaultFactor();
    lib::getMutex()->unlock();
}

Device:: Device(int physical_id, int fixed_factor)
{
    m_some_factor = fixed_factor;
    lib::getMutex()->lock();
    m_physical_device = new lib::Physical_device(lib::getHardware(physical_id));
    lib::getMutex()->unlock();
}

 const std::string Device:: getName() const
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

const std::vector<uint8_t> Device:: getParams() const
{
    return m_params;
}

// ################################ Action class implementation ###############################################

Action::Action(std::string const &command, Server& server) : m_command(command), m_server(&server) {
    // Start execution in a separate thread immediately
    m_future = std::async(std::launch::async, [this] {
        try {
            CommandArgs cmd_args = parseCommand();
            return m_server->executeAction(cmd_args.res_command, cmd_args.id, cmd_args.params);
        } catch(const std::exception& e) {
            return std::string(e.what());
        }
    });
}

const CommandArgs Action::parseCommand() {
    std::istringstream iss(m_command);
    std::string action, attribute, device_id_str, params, remaining_str, res_command;
    iss >> action >> attribute >> device_id_str >> params >> remaining_str;

    if (!remaining_str.empty()) {
        throw InvalidCommandStruct(m_command, remaining_str);
    }

    if (action == "s") {
        res_command = "set";
    } else if (action == "g") {
        res_command = "get";
    } else {
        throw InvalidAction(action);
    }

    res_command += "_" + attribute;

    int id;
    try {
        id = std::stoi(device_id_str);
    } catch (const std::exception& e) {
        throw InvalidDeviceId(device_id_str);
    }

    CommandArgs cmd_args;
    cmd_args.id = id;
    cmd_args.params = params;
    cmd_args.res_command = res_command;
    return cmd_args;
}

const std::string Action::getResult() {
    // This will block until the async operation is complete
    return m_future.get();
}


// ################################ Server class implementation ###############################################

// define static_member m_devices since as per specification "Once added, the device is never removed."
std::vector<Device> Server::m_devices;

Server::Server()
{
    // Register actions in a form action_attribute so can be called from Action class and invoked here, from the Server
    actionMap["set_name"] = [this](int id, const std::string& param) -> std::string{ return setDevName(id, param); };
    actionMap["set_params"] = [this](int id, const std::string& param) -> std::string{ return setDevParams(id, strToIntVec(param)); };
    actionMap["get_name"] = [this](int id, const std::string&) -> std::string { return getDevName(id); };
    actionMap["get_params"] = [this](int id, const std::string&) -> std::string { return getDevParams(id); };
}

void Server::addDevice (const Device& dev)
{
    std::lock_guard<std::mutex> lock(mutex_);

    //Order of the devices corresponds to their IDs (i.e. the first added device gets ID 0, the second added gets 1, and so on)
    m_devices_id.push_back(m_devices.size());
    m_devices.push_back(dev);
}


Action Server::createAction(std::string command)
{
    // start execution and return immediately 
    return Action(command, *this); // pass also current instance of server since Action object may send a request for action execution
}

const std::string Server::executeAction(const std::string& action, int id, const std::string& param = "") 
{   
    std::unique_lock<std::mutex> lock(mutex_);
    // firstly check of id since id shloud exist  in order to perform action
    if (id >= m_devices.size() or id < 0)
    {
        throw InvalidDeviceId(std::to_string(id));
    }

    // check that action is refgistered in the map
    if (actionMap.find(action) != actionMap.end()) 
    {
        return actionMap[action](id, param);
    } 
    else 
    {
        throw InvalidCommand(action);
    }
}

// implementation of private methods
const std::string Server::setDevName(int id, const std::string& name)
{   
    m_devices[id].setName(name);
    return "";
}

const std::string Server::setDevParams(int id, const std::vector<uint8_t> &params)
{
    m_devices[id].setParams(params);
    return "";
}

const std::string Server::getDevName(int id) 
{   
    return (m_devices[id].getName());
}

const std::string Server::getDevParams(int id) 
{   
    // returns a list of device parameters, separated by a comma, in an ascending order
    std::vector<uint8_t> loc_vec;
    loc_vec = m_devices[id].getParams();
    std::sort(loc_vec.begin(), loc_vec.end());
    return vectorToString(loc_vec);
}
