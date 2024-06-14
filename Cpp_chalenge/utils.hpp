#ifndef UTILS_HPP
#define UTILS_HPP

#include <vector>
#include <string>

bool isNumeric(const std::string& str);
std::vector<uint8_t> strToIntVec(const std::string& str);
std::string vectorToString(const std::vector<uint8_t>& vec);
#endif