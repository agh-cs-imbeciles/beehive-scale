#include "mail_sender.hpp"
#include "exception/mail_exception.hpp"
#include <ESP_Mail_Client.h>
#include <Vector.h>

MailSender::MailSender(String host, int port, String email, String password)
{
    session.callback(MailSender::smtpCallback);
    config.server.host_name = host;
    config.server.port = port;
    config.login.email = email;
    config.login.password = password;
    config.login.user_domain = "";
}
void MailSender::smtpCallback(SMTP_Status status)
{
    Serial.println(status.info());
    if (status.success())
    {
        Serial.println("----------------");
        ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
        ESP_MAIL_PRINTF("Message sent failed: %d\n", status.failedCount());
        Serial.println("----------------\n");
    }
}
void MailSender::configureNtpServer(String server)
{
    config.time.ntp_server = server;
    config.time.gmt_offset = 0;
    config.time.day_light_offset = 0;
}
void MailSender::setMessageHeaders(String subject, Vector<String> recipients)
{
    message.subject = subject;
    message.sender.email = config.login.email;
    for (int i = 0; i < recipients.size(); i++)
    {
        message.addRecipient(recipients[i], recipients[i]);
    }
    message.text.charSet = "UTF-8";
    message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
    message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;
    message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_delay | esp_mail_smtp_notify_failure;
}
void MailSender::setMessageContent(String content)
{
    message.text.content = content;
}
void MailSender::sendMail()
{
    bool sendingResult;
    if ((sendingResult = !MailClient.sendMail(&session, &message, false))){
        ESP_MAIL_PRINTF("Error, Status Code: %d, Error Code: %d, Reason: %s", session.statusCode(), session.errorCode(), session.errorReason().c_str());
    }
;
    session.sendingResult.clear();
    if (sendingResult)
    {
        std::string s = std::string("Failed to send mail because of: ").append(std::string(session.errorReason().c_str()));
        throw new MailException(s.c_str());
    }
}

void MailSender::connect()
{
    if (!session.connect(&config))
    {
        ESP_MAIL_PRINTF("Connection error, Status Code: %d, Error Code: %d, Reason: %s", session.statusCode(), session.errorCode(), session.errorReason().c_str());
        std::string s = std::string("Failed to send mail because of: ").append(std::string(session.errorReason().c_str()));
        throw new MailException(s.c_str());;
    }
    if (!session.isLoggedIn())
    {
        Serial.println("\nNot yet logged in.");
    }
    else
    {
        if (session.isAuthenticated())
            Serial.println("\nSuccessfully logged in.");
        else
            Serial.println("\nConnected with no Auth.");
    }
}

void MailSender::disconnect()
{
    session.closeSession();
}
