#include <SPIFFS.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HX711.h>
#include "ArduinoJson.h"

#include "src/thing_speak_wrapper.hpp"
#include "src/configurator.hpp"
#include "src/mail_sender.hpp"
#include "src/exception/json_exception.hpp"
#include "src/exception/mail_exception.hpp"
#include "src/exception/thing_speak_exception.hpp"
#include "src/thing_speak_wrapper.hpp"

#define DOUT 13
#define CLK 12

HX711 scale;
WiFiMulti wifiMulti;
Configurator *configurator;
MailSender *sender;
ThingSpeakWrapper *thingSpeakWrapper;

unsigned long previousMilis = 0;
unsigned long interval;
float calibration_factor = 40000;
double treshold;
double hysteresis;
bool tresholdReset = true;

void setup()
{
    try
    {
        Serial.begin(115200);
        delay(2000);
        if (!SPIFFS.begin(true))
        {
            Serial.println("SPIFFS Mount Failed");
            return;
        }
        configurator = new Configurator("/esp32.json");
        configurator->parse();
        configurator->loadConfig();
        treshold = configurator->getMassThreshold();
        hysteresis = configurator->getHysteresisOfMass();
        for (const WiFiPass w : configurator->getNetworksArray())
        {
            wifiMulti.addAP(w.SSID.c_str(), w.password.c_str());
        }
        if (wifiMulti.run() == WL_CONNECTED)
        {
            Serial.print("WiFi connected: ");
            Serial.print(WiFi.SSID());
            Serial.print(" ");
            Serial.print(WiFi.RSSI());
            Serial.print(" ");
            Serial.println(WiFi.localIP());
        }
        sender = new MailSender(
            configurator->getSmtpHost(),
            configurator->getSmtpPort(),
            configurator->getEmailLogin(),
            configurator->getEmailPassword());
        sender->setMessageHeaders("ESPWaga", configurator->getRecipients());
        sender->configureNtpServer(configurator->getNtpServer());
        interval = configurator->getIntervalSeconds() * 1000;
        sender->connect();
        sender->disconnect();
        scale.begin(DOUT, CLK);
        scale.set_scale(calibration_factor);
        scale.tare();
        thingSpeakWrapper = new ThingSpeakWrapper(
            configurator->getThingSpeakChannelId(),
            configurator->getThingSpeakApiKey()
        );
    }
    catch (JsonException e)
    {
        Serial.println(e.what());
        Serial.println("Failed to load configuration");
    }
    catch (MailException e)
    {
        Serial.println(e.what());
    }
    catch (...)
    {
        Serial.println("Unknown exception in setup");
    }
}

void loop()
{
    try
    {
        unsigned long currentMillis = millis();

        float mass = -scale.get_units();
        Serial.println(mass);
        if (mass > treshold && tresholdReset)
        {
            while (wifiMulti.run() != WL_CONNECTED)
            {
                Serial.println("WiFi not connected!");
                delay(200);
            }

            Serial.print("WiFi connected: ");
            Serial.print(WiFi.SSID());
            Serial.print(" ");
            Serial.print(WiFi.RSSI());
            Serial.print(" ");
            Serial.println(WiFi.localIP());
            previousMilis = currentMillis;
            sender->connect();

            mass = std::ceil(mass * 100.0) / 100.0;
            std::string massStr = std::to_string(mass);
            massStr = massStr.substr(0, massStr.find(".") + 3);
            std::string mailBody = std::string();
            mailBody.append("Masa: ").append(massStr);

            sender->setMessageContent(String(mailBody.c_str()));
            sender->sendMail();
            sender->disconnect();

            if (mass > treshold)
            {
                tresholdReset = false;
            }
        }
        if ((currentMillis - previousMilis) >= interval)
        {
            while (wifiMulti.run() != WL_CONNECTED)
            {
                Serial.println("WiFi not connected!");
                delay(200);
            }

            Serial.print("WiFi connected: ");
            Serial.print(WiFi.SSID());
            Serial.print(" ");
            Serial.print(WiFi.RSSI());
            Serial.print(" ");
            Serial.println(WiFi.localIP());

            thingSpeakWrapper->sendMassData(1, mass);
        }
        if (mass < treshold - hysteresis)
        {
            tresholdReset = true;
        }
    }
    catch (MailException e)
    {
        Serial.println(e.what());
        Serial.println("Failed to send mail");
    }
    catch (ThingSpeakException e){
        Serial.println(e.what());
        Serial.println("Failed to send update on ThingSpeak");
    }
    catch (...)
    {
        Serial.println("Unknown exception in loop");
    }
}
