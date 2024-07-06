#ifndef SOLUTION_HPP
#define SOLUTION_HPP
#include <string>
#include "physical_device.h" 
#include <vector>
#include <unordered_map>
#include <functional>
#include <optional>
#include <future>

// forward declaration of classes Action and Server in order to avoid circular dependency error
class Action;
class Server;

struct CommandArgs
{
    std::string params;
    int id;
    std::string res_command;
};

class Device
{
    public:
        Device(int physical_id);

        Device(int physical_id, int fixed_factor);

        void setName(std::string const name);

        void setParams(const std::vector<uint8_t>& params);

        const std::vector<uint8_t> getParams() const;

        const std::string getName() const;

    private:
        lib::Physical_device* m_physical_device;
        int                   m_some_factor;
        std::string           m_name;
        std::vector<uint8_t>  m_params;
};


class Server
{
public:
    Server();
    void addDevice (const Device& dev);
    Action createAction(std::string command);
    const std::string executeAction(const std::string& action, int id, const std::string& param );

private:
    static std::vector<Device> m_devices;
    std::vector<uint64_t> m_devices_id;
    std::mutex mutex_;

    // mapping actions with correspoding functions
    std::unordered_map<std::string, std::function<const std::string(int, const std::string&)>> actionMap;

    // private functions that handle the commands
    const std::string setDevName(int id, const std::string& name);

    const std::string setDevParams(int id, const std::vector<uint8_t> &params);

    const std::string getDevName(int id) ; 

    const std::string getDevParams(int id); 
};


class Action
{
    public:
        Action(std::string const &command, Server& server);
        const std::string getResult();
        const CommandArgs parseCommand();
        std::future<std::string> m_future;

    private:
        std::string  m_command;
        Server  *m_server;
};

#endif



