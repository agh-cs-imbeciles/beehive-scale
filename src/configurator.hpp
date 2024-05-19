#pragma once

#include "ArduinoJson.h"
#include <Vector.h>

#define ARR_SIZE (size_t)16

typedef struct WiFiPass
{
    String SSID;
    String password;
} WiFiPass;

class Configurator
{
private:
    String filename;
    String content;
    JsonDocument document;
    String storageRecipients[ARR_SIZE];
    WiFiPass storageWiFiPass[ARR_SIZE];
    
    template <typename T>
    T throwJsonExceptionIfWrongField(JsonVariant value, String fieldName);

public:
    Configurator(const String filename);
    void parse();
    double getMassThreshold();
    long getIntervalSeconds();
    Vector<WiFiPass> getNetworksArray();
    Vector<String> getRecipients();
    String getSmtpHost();
    int getSmtpPort();
    String getEmailLogin();
    String getEmailPassword();
    String getNtpServer();
};
