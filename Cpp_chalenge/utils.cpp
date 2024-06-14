/*
Helper function are defined here which are general usage helper function
*/

#include <sstream>
#include "custom_exceptions.hpp"
#include "utils.hpp"

bool isNumeric(const std::string& str) {
    for (char c : str) {
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