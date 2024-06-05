#include "ArduinoJson.h"

class ThingSpeakException : public std::exception
{
private:
    char *message;

public:
    ThingSpeakException(const char *msg) : message((char*)msg) {}
    char *what()
    {
        return message;
    }
};
