/*
Helper functions are defined here 
*/

#include <sstream>
#include "custom_exceptions.hpp"
#include "utils.hpp"


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
        int num;
        // check if token could be converted to integer
        try
        {
            num = std::stoi(token);
        }
        catch(const std::exception& e)
        {
            throw InvalidParameterStruct(str);
        }
        
        if (num >=0 && num <=255)
            {
                 params.push_back(num);
            }
            else
            {
                 throw InvalidParameterValue(token);
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