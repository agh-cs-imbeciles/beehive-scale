#include "ArduinoJson.h"
class MailException : public std::exception
{
private:
    char *message;

public:
    MailException(const char *msg) : message((char*)msg) {}
    char *what()
    {
        return message;
    }
};