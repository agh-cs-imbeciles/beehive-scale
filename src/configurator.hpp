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
    double massThreshold;
    double hysteresisOfMass;
    long intervalSeconds;
    Vector<WiFiPass> networksArray;
    Vector<String> recipients;
    String smtpHost;
    int smtpPort;
    String emailLogin;
    String emailPassword;
    String ntpServer;
    template <typename T>
    T throwJsonExceptionIfWrongField(JsonVariant value, String fieldName);
    void loadMassThreshold();
    void loadHysteresisOfMass();
    void loadIntervalSeconds();
    void loadNetworksArray();
    void loadRecipients();
    void loadSmtpHost();
    void loadSmtpPort();
    void loadEmailLogin();
    void loadEmailPassword();
    void loadNtpServer();

public:
    Configurator(const String filename);
    void parse();
    void loadConfig();
    double getMassThreshold();
    double getHysteresisOfMass();
    long getIntervalSeconds();
    Vector<WiFiPass> getNetworksArray();
    Vector<String> getRecipients();
    String getSmtpHost();
    int getSmtpPort();
    String getEmailLogin();
    String getEmailPassword();
    String getNtpServer();
};
