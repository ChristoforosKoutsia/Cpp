#ifndef CUSTOM_EXCEPTIONS_HPP
#define  CUSTOM_EXCEPTIONS_HPP

#include <iostream>
#include <exception>  // For std::exception

class InvalidParameterStruct : public std::exception {
private:
    std::string message;

public:
    InvalidParameterStruct(const std::string& params)
        : message("Invalid Input : Given Parameters are not fulfill the pattern numerical value followed by comma but instead : '" + params + "' was given") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidParameterValue : public std::exception {
private:
    std::string message;

public:
    InvalidParameterValue(const std::string& num)
        : message("Invalid Input in given Parameter. Values should be in range 0-255. Instead value " + num + " was given") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidAction : public std::exception {
private:
    std::string message;

public:
    InvalidAction(const std::string& action)
        : message("Invalid Action. Actions should be either 's' for set or 'g' for get. Instead '" + action + "' was given") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};


class InvalidDeviceId : public std::exception {
private:
    std::string message;

public:
    InvalidDeviceId(const std::string& id)
        : message("Invalid Device id. There is no device with id '"+ id + "' registered") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidCommand : public std::exception {
private:
    std::string message;

public:
    InvalidCommand(const std::string& cmd)
        : message("Invalid Command. Command '" + cmd + "' is not registered") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class InvalidCommandStruct : public std::exception {
private:
    std::string message;

public:
    InvalidCommandStruct(const std::string& cmd,const std::string& trail_str)
        : message("Invalid Action. Action '" + cmd + "' is not well formed." + trail_str+ " is trailing (not correct spacing)") {}

    const char* what() const noexcept override {
        return message.c_str();
    }
};

#endif