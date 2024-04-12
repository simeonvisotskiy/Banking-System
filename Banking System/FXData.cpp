#include"FXData.h"

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data) {
    size_t newLength = size * nmemb;
    try {
        data->append((char*)contents, newLength);
        return newLength;
    }
    catch (std::bad_alloc& e) {
       
        return 0;
    }
}

std::map<std::string, double> FXData::getApiData(const std::string& apiUrl, const std::string& baseCurrency) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;
    std::map<std::string, double> currencyRates;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        else {
            auto json = nlohmann::json::parse(readBuffer);
            for (auto& [key, value] : json["rates"].items()) {
                currencyRates[key] = value.get<double>();
            }
        }
    }
    return currencyRates;
}