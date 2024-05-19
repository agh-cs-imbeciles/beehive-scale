#include "ArduinoJson.h"
class JsonException : public std::exception
{
private:
    char *message;

public:
    JsonException(const char *msg) : message((char*)msg) {}
    char *what()
    {
        return message;
    }
};