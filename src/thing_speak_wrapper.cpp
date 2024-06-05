#include "thing_speak_wrapper.hpp"
#include "exception/thing_speak_exception.hpp"
#include <WiFi.h>
#include <ThingSpeak.h>

ThingSpeakWrapper::ThingSpeakWrapper(long channelId, String APIKey)
{
    ThingSpeak.begin(this->client);
    this->channelId = channelId;
    this->APIKey = APIKey;
}

void ThingSpeakWrapper::sendMassData(long field, float mass)
{
    Serial.println(this->channelId);
    Serial.println(this->APIKey);

    int code = ThingSpeak.writeField(this->channelId, 1, mass, this->APIKey.c_str());
    if (code != 200)
    {
        String res = "Problem updating channel. HTTP error code " + String(code);
        throw ThingSpeakException(res.c_str());
    }
}
