#include <SPIFFS.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HX711.h>

#include "src/configurator.hpp"
#include "src/mail_sender.hpp"

#define FORMAT_SPIFFS_IF_FAILED true
#define DOUT 13
#define CLK 12

HX711 scale;
WiFiMulti wifiMulti;
Configurator *configurator;
MailSender *sender;
unsigned long previousMilis = 0;
unsigned long interval;
float calibration_factor = 40000;

void setup()
{
    Serial.begin(115200);
    if (!SPIFFS.begin(true))
    {
        Serial.println("SPIFFS Mount Failed");
        return;
    }
    configurator = new Configurator("/config.json");
    configurator->parse();
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
    Serial.println(configurator->getRecipients()[0]);
    Serial.println(configurator->getRecipients()[1]);
    sender = new MailSender(
        configurator->getSmtpHost(),
        configurator->getSmtpPort(),
        configurator->getEmailLogin(),
        configurator->getEmailPassword());
    sender->setMessageHeaders("ESPWaga", configurator->getRecipients());
    sender->configureNtpServer(configurator->getNtpServer());
    interval = configurator->getIntervalSeconds() * 1000;
    sender->connect();
    scale.begin(DOUT, CLK);
    scale.set_scale(calibration_factor);
    scale.tare();
}

void loop()
{
    // Serial.println(configurator->getIntervalSeconds());
    Serial.println(scale.get_units(), 1);
    unsigned long currentMillis = millis();
    if ((currentMillis - previousMilis) >= interval)
    {
        while (wifiMulti.run() != WL_CONNECTED)
        {
            Serial.println("WiFi not connected!");
            delay(200);
        }
        float mass = scale.get_units();
        mass = -std::ceil(mass * 100.0) / 100.0;
        Serial.print("WiFi connected: ");
        Serial.print(WiFi.SSID());
        Serial.print(" ");
        Serial.print(WiFi.RSSI());
        Serial.print(" ");
        Serial.println(WiFi.localIP());
        previousMilis = currentMillis;
        sender->connect();

        std::string massStr = std::to_string(mass);
        massStr = massStr.substr(0, massStr.find(".") + 3);
        std::string mailBody = std::string();
        mailBody.append("Masa: ").append(massStr);

        sender->setMessageContent(String(mailBody.c_str()));
        sender->sendMail();
    }
}
