#pragma once

#ifndef ENMA_TEST_LOG_HPP
#define ENMA_TEST_LOG_HPP

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>

inline std::string getCurrentDateTime(std::string s)
{
    time_t now = time(0);
    struct tm timeinfo;
    char buf[80];
    localtime_s(&timeinfo, &now);

    if(s == "now")
    {
        strftime(buf, sizeof(buf), "%d-%m-%Y %X", &timeinfo);
    }
    else if(s == "date")
    {
        strftime(buf, sizeof(buf), "%d-%m-%Y", &timeinfo);
    }

    return std::string(buf);
};

template <typename  ...Args>
void LogToFile(std::string msgType, Args ... args)
{
    #ifdef FILE_LOG

    std::stringstream ss;
    (ss << ... << args);

    std::string curr = getCurrentDateTime("now");
    std::ofstream file(std::string("debug-") + getCurrentDateTime("date") + std::string(".log"), std::ios_base::out | std::ios_base::app);
    file << curr << " " << msgType << ss.str() << '\n';
    file.close();

    #endif
}

template <typename  ...Args>
void LogToConsole(std::string msgType, Args ... args)
{
    #ifdef CONSOLE_LOG

    std::stringstream ss;
    (ss << ... << args);

    std::cout << msgType << ss.str() << '\n';

    #endif
}

#define XSTR(x) #x
#define STR(x) XSTR(x)
#define S(x) std::string(x)


#if defined(CONSOLE_LOG) && defined(FILE_LOG)

#define LOG_D(...)                                                                                  \
do                                                                                                  \
{                                                                                                   \
    LogToConsole("DEBUG: ", __VA_ARGS__);                                                           \
    LogToFile("DEBUG: ", __VA_ARGS__);                                                              \
} while (0)                                                                                         \

#define LOG_W(...)                                                                                  \
do                                                                                                  \
{                                                                                                   \
    LogToConsole(S("WARN [") + STR(__FILE__) + S(": ") + STR(__LINE__) + S("]: "), __VA_ARGS__);    \
    LogToFile(S("WARN [") + STR(__FILE__) + S(": ") + STR(__LINE__) + S("]: "), __VA_ARGS__);       \
} while (0)                                                                                         \

#define LOG_E(...)                                                                                  \
do                                                                                                  \
{                                                                                                   \
    LogToConsole(S("ERROR [") + STR(__FILE__) + S(": ") + STR(__LINE__) + S("]: "), __VA_ARGS__);   \
    LogToFile(S("ERROR [") + STR(__FILE__) + S(": ") + STR(__LINE__) + S("]: "), __VA_ARGS__);      \
} while (0)                                                                                         \

#elif defined(CONSOLE_LOG)

#define LOG_D(...)                                                                                  \
do                                                                                                  \
{                                                                                                   \
    LogToConsole("DEBUG: ", __VA_ARGS__);                                                           \
} while (0)                                                                                         \

#define LOG_W(...)                                                                                  \
do                                                                                                  \
{                                                                                                   \
    LogToConsole(S("WARN [") + STR(__FILE__) + S(": ") + STR(__LINE__) + S("]: "), __VA_ARGS__);    \
} while (0)                                                                                         \

#define LOG_E(...)                                                                                  \
do                                                                                                  \
{                                                                                                   \
    LogToConsole(S("ERROR [") + STR(__FILE__) + S(": ") + STR(__LINE__) + S("]: "), __VA_ARGS__);   \
} while (0)                                                                                         \

#elif defined(FILE_LOG)

#define LOG_D(...)                                                                                  \
do                                                                                                  \
{                                                                                                   \
    LogToFile("DEBUG: ", __VA_ARGS__);                                                              \
} while (0)                                                                                         \

#define LOG_W(...)                                                                                  \
do                                                                                                  \
{                                                                                                   \
    LogToFile(S("WARN [") + STR(__FILE__) + S(": ") + STR(__LINE__) + S("]: "), __VA_ARGS__);       \
} while (0)                                                                                         \

#define LOG_E(...)                                                                                  \
do                                                                                                  \
{                                                                                                   \
    LogToFile(S("ERROR [") + STR(__FILE__) + S(": ") + STR(__LINE__) + S("]: "), __VA_ARGS__);      \
} while (0)                                                                                         \

#else

#define LOG_D(...)

#define LOG_W(...)

#define LOG_E(...)

#endif

#endif // ENMA_TEST_LOG_HPP