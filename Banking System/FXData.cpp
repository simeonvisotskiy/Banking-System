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


void sendEmailWithCode(const std::string& email, const std::string& code) {
    char* apiKey = nullptr;
    size_t apiKeySize = 0;
    errno_t apiKeyErr = _dupenv_s(&apiKey, &apiKeySize, "SENDINBLUE_API_KEY");

    char* senderEmail = nullptr;
    size_t senderEmailSize = 0;
    errno_t senderEmailErr = _dupenv_s(&senderEmail, &senderEmailSize, "SENDINBLUE_SENDER_EMAIL");

    if (apiKeyErr || !apiKey) {
        std::cerr << "Failed to retrieve SENDINBLUE_API_KEY from environment variables.\n";
    }
    if (senderEmailErr || !senderEmail) {
        std::cerr << "Failed to retrieve SENDINBLUE_SENDER_EMAIL from environment variables.\n";
    }
    if (!apiKey || !senderEmail) {
        free(apiKey);
        free(senderEmail);
        return;
    }

    std::string data = "{\"sender\":{\"name\":\"Banking System\",\"email\":\"" + std::string(senderEmail) + "\"}, \"to\":[{\"email\":\"" + email + "\"}], \"subject\":\"Verification Code\", \"htmlContent\":\"<html><body>Your verification code is: " + code + "</body></html>\"}";
    CURL* curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.sendinblue.com/v3/smtp/email");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

        struct curl_slist* headers = NULL;
        headers = curl_slist_append(headers, "accept: application/json");
        headers = curl_slist_append(headers, "Content-Type: application/json");
        headers = curl_slist_append(headers, ("api-key: " + std::string(apiKey)).c_str());

        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);  // Set to 1 in production for security

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    free(apiKey);      // Free memory after use
    free(senderEmail); // Free memory after use
}