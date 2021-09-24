#pragma once
#include <fstream>
#include <stdio.h>
#include <mutex>
#include <ctime>
using namespace std;
enum LogPriority
{
    TracePriority,
    DebugPriority,
    InfoPriority,
    WarnPriority,
    ErrorPriority,
    CriticalPriority
};

class Logger
{
private:
    static LogPriority priority;
    static std::mutex log_mutex;

public:
    static void SetPriority(LogPriority new_priority)
    {
        priority = new_priority;
    }

    template <typename... Args>
    static void Trace(const char *message, Args... args)
    {
        log("[Trace]\t", TracePriority, message, args...);
    }

    template <typename... Args>
    static void Debug(const char *message, Args... args)
    {
        log("[Debug]\t", DebugPriority, message, args...);
    }

    template <typename... Args>
    static void Info(const char *message, Args... args)
    {
        log("[Info]\t", InfoPriority, message, args...);
    }

    template <typename... Args>
    static void Warn(const char *message, Args... args)
    {
        log("[Warn]\t", WarnPriority, message, args...);
    }

    template <typename... Args>
    static void Error(const char *message, Args... args)
    {
        log("[Error]\t", ErrorPriority, message, args...);
    }

    template <typename... Args>
    static void Critical(const char *message, Args... args)
    {
        log("[Critical]\t", CriticalPriority, message, args...);
    }

private:
    template <typename... Args>
    static void log(const char *message_priority_str, LogPriority message_priority, const char *message, Args... args)
    {
        if (priority <= message_priority)
        {
            std::time_t current_time = std::time(0);
            std::tm *timestamp = std::localtime(&current_time);
            char buffer[80];
            strftime(buffer, 80, "%c", timestamp);

            lock_guard<mutex> lock(log_mutex);
            ofstream ofs;
            ofs.open("logs.txt", std::ofstream::out | std::ofstream::app);
            ofs << buffer << "\t" << message_priority_str << message << "\n";
        }
    }
};

LogPriority Logger::priority = InfoPriority;
std::mutex Logger::log_mutex;
