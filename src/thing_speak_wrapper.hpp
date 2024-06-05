#pragma once
#include <WiFi.h>
#include <ThingSpeak.h>

class ThingSpeakWrapper
{
private:
    WiFiClient client;
    long channelId;
    String APIKey;

public:
    ThingSpeakWrapper(long channelId, String APIKey);
    void sendMassData(long field, float mass);
};