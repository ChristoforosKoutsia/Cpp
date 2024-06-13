#ifndef SOLUTION_H
#define SOLUTION_H
#include <string>
#include "physical_device.h" 
#include <vector>
#include <unordered_map>
#include <functional>




class Action;
class Server;

class Device
{
    public:
        Device(int physical_id);



       std::string getName() const;


        void setName(std::string const name);


        void setParams(const std::vector<uint8_t>& params);


        std::vector<uint8_t> getParams() const;

        int getId() const;


    private:
        //std::shared_ptr<lib::Physical_device> m_physical_device;
        lib::Physical_device* m_physical_device;
        int                   m_some_factor;
        std::string           m_name; // private data member is not initialized anywhere but this is not a problem since there is the default initializer for a string
        std::vector<uint8_t>  m_params;
        int                   m_id; // Mention here that int should be uint_64t but cannot be changed due to possible implicit convesion in physical device
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

//friend class Action; //  Action is a friend of Server so it can have access to private members in order to modify them if needed
};


class Action
{
    public:
        Action(std::string const &command, Server& server);

        std::string getResult() const;

        void parse_command();
        void execute_command();

    private:
        std::string  m_command;
        Server  *m_server;

};

#endif



