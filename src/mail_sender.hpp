#include "configurator.hpp"
#include <ESP_Mail_Client.h>
#include <Vector.h>

class MailSender
{
private:
    SMTPSession session;
    Session_Config config;
    SMTP_Message message;

public:
    MailSender(String host, int port, String email, String password);
    void static smtpCallback(SMTP_Status status);
    void configureNtpServer(String server);
    void setMessageHeaders(String subject, Vector<String> recipients);
    void setMessageContent(String content);
    void sendMail();
    void connect();
    void disconnect();
};
