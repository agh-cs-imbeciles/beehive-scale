#pragma once
#include "Configurator.hpp"
#include "FS.h"
#include "SPIFFS.h"
#include <Vector.h>

Configurator::Configurator(const String filename)
{
    this->filename = filename;
}

void Configurator::parse()
{
    File file = SPIFFS.open(this->filename, "r", false);

    if (!file || file.isDirectory())
    {
        return;
    }
    if (deserializeJson(document, file) != DeserializationError::Ok)
    {
        return;
    }
    file.close();
}

double Configurator::getMassThreshold()
{
    return document["massTreshold"].as<double>();
}

long Configurator::getIntervalSeconds()
{
    return document["intervalSeconds"].as<long>();
}

Vector<WiFiPass> Configurator::getNetworksArray()
{
    Vector<WiFiPass> array;
    array.setStorage(this->storageWiFiPass,ARR_SIZE,0);
    JsonArray jsonArray = document["networks"];
    for (int i = 0; i < jsonArray.size(); i++)
    {   
        array.push_back(
            WiFiPass{
                jsonArray[i]["SSID"].as<String>(),
                jsonArray[i]["password"].as<String>()
            }
        );
    }
    Serial.println(array.size());
    return array;
}

Vector<String> Configurator::getRecipients()
{   
    
    Vector<String> array;
    array.setStorage(this->storageRecipients,ARR_SIZE,0);
    JsonArray jsonArray = document["recipients"];
    for (int i = 0; i < jsonArray.size(); i++)
    {
        Serial.println(jsonArray[i].as<String>());
        array.push_back(jsonArray[i].as<String>());
        Serial.println(array[0]);
    }
    return array;
}

String Configurator::getSmtpHost(){
    return document["smtpHost"];
}

int Configurator::getSmtpPort(){
    return document["smtpPort"];
}

String Configurator::getEmailLogin(){
    return document["emailLogin"];
}

String Configurator::getEmailPassword(){
    return document["emailPassword"];
}

String Configurator::getNtpServer(){
    return document["ntpServer"];
}