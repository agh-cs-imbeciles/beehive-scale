#pragma once

#include "configurator.hpp"
#include <FS.h>
#include <SPIFFS.h>
#include <Vector.h>
#include <type_traits>

#include "exception/json_exception.hpp"

template <typename T>
T Configurator::throwJsonExceptionIfWrongField(JsonVariant value, String fieldName)
{
    T v = value.as<T>();
    String message = "Wrong value of " + fieldName;
    if (!v)
    {
        throw JsonException(message.c_str());
    }
    return v;
}

void Configurator::loadMassThreshold()
{
    String s = "massTreshold";
    this->massThreshold = throwJsonExceptionIfWrongField<double>(document[s], s);
}

void Configurator::loadHysteresisOfMass()
{
    String s = "hysteresisOfMass";
    this->hysteresisOfMass = throwJsonExceptionIfWrongField<double>(document[s], s);
}

void Configurator::loadIntervalSeconds()
{
    String s = "intervalSeconds";
    this->intervalSeconds = throwJsonExceptionIfWrongField<long>(document[s], s);
}

void Configurator::loadNetworksArray()
{
    Vector<WiFiPass> array;
    array.setStorage(this->storageWiFiPass, ARR_SIZE, 0);
    String s = "networks";
    JsonArray jsonArray = throwJsonExceptionIfWrongField<JsonArray>(document[s], s);

    for (int i = 0; i < jsonArray.size(); i++)
    {
        s = "ssid";
        String ssid = throwJsonExceptionIfWrongField<const char *>(jsonArray[i][s], s);
        s = "password";
        String password = throwJsonExceptionIfWrongField<const char *>(jsonArray[i][s], s);
        array.push_back(
            WiFiPass{
                ssid,
                password});
    }
    this->networksArray = array;
}

void Configurator::loadRecipients()
{
    Vector<String> array;
    array.setStorage(this->storageRecipients, ARR_SIZE, 0);
    String s = "recipients";
    JsonArray jsonArray = throwJsonExceptionIfWrongField<JsonArray>(document[s], s);
    for (int i = 0; i < jsonArray.size(); i++)
    {
        String recipient = throwJsonExceptionIfWrongField<const char *>(jsonArray[i], s);
        array.push_back(recipient);
    }
    this->recipients = array;
}

void Configurator::loadSmtpHost()
{
    String s = "smtpHost";
    this->smtpHost = throwJsonExceptionIfWrongField<const char *>(document[s], s);
}

void Configurator::loadSmtpPort()
{
    String s = "smtpPort";
    this->smtpPort = throwJsonExceptionIfWrongField<int>(document[s], s);
}

void Configurator::loadEmailLogin()
{
    String s = "emailLogin";
    this->emailLogin = throwJsonExceptionIfWrongField<const char *>(document[s], s);
}

void Configurator::loadEmailPassword()
{
    String s = "emailPassword";
    this->emailPassword = throwJsonExceptionIfWrongField<const char *>(document[s], s);
}

void Configurator::loadNtpServer()
{
    String s = "ntpServer";
    this->ntpServer = throwJsonExceptionIfWrongField<const char *>(document[s], s);
}

void Configurator::loadThingSpeakChannelId()
{
    String s = "thingSpeakChannelId";
    this->thingSpeakChannelId = throwJsonExceptionIfWrongField<long>(document[s], s);
}

void Configurator::loadThingSpeakApiKey()
{
    String s = "thingSpeakApiKey";
    this->thingSpeakApiKey = throwJsonExceptionIfWrongField<const char *>(document[s], s);
}

Configurator::Configurator(const String filename)
{
    this->filename = filename;
}

void Configurator::parse()
{
    File file = SPIFFS.open(this->filename, "r", false);

    if (!file || file.isDirectory())
    {
        throw JsonException("Failed to open a file or file is directory");
    }
    DeserializationError err;
    if ((err = deserializeJson(document, file)) != DeserializationError::Ok)
    {
        throw JsonException("Failed to serialize json file");
    }
    file.close();
}

void Configurator::loadConfig()
{
    this->loadMassThreshold();
    this->loadHysteresisOfMass();
    this->loadIntervalSeconds();
    this->loadNetworksArray();
    this->loadRecipients();
    this->loadSmtpHost();
    this->loadSmtpPort();
    this->loadEmailLogin();
    this->loadEmailPassword();
    this->loadNtpServer();
    this->loadThingSpeakChannelId();
    this->loadThingSpeakApiKey();
}

double Configurator::getMassThreshold()
{
    return this->massThreshold;
}

double Configurator::getHysteresisOfMass()
{
    return this->hysteresisOfMass;
}

long Configurator::getIntervalSeconds()
{
    return this->intervalSeconds;
}

Vector<WiFiPass> Configurator::getNetworksArray()
{
    return this->networksArray;
}

Vector<String> Configurator::getRecipients()
{
    return this->recipients;
}

String Configurator::getSmtpHost()
{
    return this->smtpHost;
}

int Configurator::getSmtpPort()
{
    return this->smtpPort;
}

String Configurator::getEmailLogin()
{
    return this->emailLogin;
}

String Configurator::getEmailPassword()
{
    return this->emailPassword;
}

String Configurator::getNtpServer()
{
    return this->ntpServer;
}

long Configurator::getThingSpeakChannelId()
{
    return this->thingSpeakChannelId;
}

String Configurator::getThingSpeakApiKey()
{
    return this->thingSpeakApiKey;
}
