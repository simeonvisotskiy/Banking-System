#ifndef FXDATA_H
#define FXDATA_H

#include<iostream>
#include<string>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <map>

class FXData {
public:
    std::map<std::string, double> getApiData(const std::string& apiUrl, const std::string& baseCurrency);
};

#endif 