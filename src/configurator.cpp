#pragma once

#include "configurator.hpp"
#include <FS.h>
#include <SPIFFS.h>
#include <Vector.h>
#include <type_traits>

#include "exception/json_exception.hpp"

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

double Configurator::getMassThreshold()
{
    String s = "massTreshold";
    return throwJsonExceptionIfWrongField<double>(document[s], s);
}

long Configurator::getIntervalSeconds()
{
    String s = "intervalSeconds";
    return throwJsonExceptionIfWrongField<long>(document[s], s);
}

Vector<WiFiPass> Configurator::getNetworksArray()
{
    Vector<WiFiPass> array;
    array.setStorage(this->storageWiFiPass, ARR_SIZE, 0);
    String s = "networks";
    JsonArray jsonArray = throwJsonExceptionIfWrongField<JsonArray>(document[s], s);

    for (int i = 0; i < jsonArray.size(); i++)
    {
        s = "ssid";
        String ssid = throwJsonExceptionIfWrongField<String>(jsonArray[i][s], s);
        s = "password";
        String password = throwJsonExceptionIfWrongField<String>(jsonArray[i][s], s);
        array.push_back(
            WiFiPass{
                ssid,
                password
            });
    }
    return array;
}

Vector<String> Configurator::getRecipients()
{
    Vector<String> array;
    array.setStorage(this->storageRecipients, ARR_SIZE, 0);
    String s = "recipients";
    JsonArray jsonArray = throwJsonExceptionIfWrongField<JsonArray>(document[s], s);
    for (int i = 0; i < jsonArray.size(); i++)
    {
        String recipient = throwJsonExceptionIfWrongField<String>(jsonArray[i], s);
        array.push_back(recipient);
    }
    return array;
}

String Configurator::getSmtpHost()
{
    String s = "smtpHost";
    return throwJsonExceptionIfWrongField<String>(document[s], s);
}

int Configurator::getSmtpPort()
{
    String s = "smtpPort";
    return throwJsonExceptionIfWrongField<int>(document[s], s);
}

String Configurator::getEmailLogin()
{
    String s = "emailLogin";
    return throwJsonExceptionIfWrongField<String>(document[s], s);
}

String Configurator::getEmailPassword()
{
    String s = "emailPassword";
    return throwJsonExceptionIfWrongField<String>(document[s], s);
}

String Configurator::getNtpServer()
{
    String s = "ntpServer";
    return throwJsonExceptionIfWrongField<String>(document[s], s);
}

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
