#pragma once
#include <thread>
#include <stdio.h>
#include <mutex>
#include <fstream>
void filePutContents(const std::string &name, const std::string &content, bool append = false)
{
    std::ofstream outfile;
    if (append)
        outfile.open(name, std::ios_base::app);
    else
        outfile.open(name);
    outfile << content;
}
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
    static mutex log_mutex;

public:
    static void set_priority(LogPriority new_priority)
    {
        priority = new_priority;
    }

    template <typename... Args>
    static void Trace(const char *message, Args... args)
    {
        if (priority <= TracePriority)
        {
            lock_guard<mutex> lock(log_mutex);
            ofstream ofs;
            ofs.open("logs.txt", std::ofstream::out | std::ofstream::app);
            ofs << "[TRACE]\t" << message << "\n";
            // printf("[Trace]\t");
            // printf(message, args...);
            printf("\n");
        }
    }

    template <typename... Args>
    static void Debug(const char *message, Args... args)
    {
        if (priority <= DebugPriority)
        {
            lock_guard<mutex> lock(log_mutex);
            ofstream ofs;
            ofs.open("logs.txt", std::ofstream::out | std::ofstream::app);
            ofs << "[DEBUG]\t" << message << "\n";
            //printf("[Debug]\t");
            //printf(message, args...);
            printf("\n");
        }
    }

    template <typename... Args>
    static void Info(const char *message, Args... args)
    {
        if (priority <= InfoPriority)
        {
            //string s = "[INFO]\t" + message;
            lock_guard<mutex> lock(log_mutex);
            /*ofstream newFile("logs.txt");
            
            newFile << "[INFO]\t" << message;
            newFile.write("[Hello]");*/
            //filePutContents("logs.txt", s, true);
            ofstream ofs;
            ofs.open("logs.txt", std::ofstream::out | std::ofstream::app);
            ofs << "[INFO]\t" << message << "\n";
            printf("\n");
        }
    }

    template <typename... Args>
    static void Warn(const char *message, Args... args)
    {
        if (priority <= WarnPriority)
        {
            lock_guard<mutex> lock(log_mutex);
            ofstream ofs;
            ofs.open("logs.txt", std::ofstream::out | std::ofstream::app);
            ofs << "[WARN]\t" << message << "\n";
            //printf("[Warn]\t");
            //printf(message, args...);
            printf("\n");
        }
    }

    template <typename... Args>
    static void Error(const char *message, Args... args)
    {
        if (priority <= ErrorPriority)
        {
            lock_guard<mutex> lock(log_mutex);
            ofstream ofs;
            ofs.open("logs.txt", std::ofstream::out | std::ofstream::app);
            ofs << "[ERROR]\t" << message << "\n";
            //printf("[Error]\t");
            // printf(message, args...);
            printf("\n");
        }
    }

    template <typename... Args>
    static void Critical(const char *message, Args... args)
    {
        if (priority <= CriticalPriority)
        {
            lock_guard<mutex> lock(log_mutex);
            ofstream ofs;
            ofs.open("logs.txt", std::ofstream::out | std::ofstream::app);
            ofs << "[CRTICAL]\t" << message << "\n";
            //printf("[Critical]\t");
            //printf(message, args...);
            printf("\n");
        }
    }
};

LogPriority Logger::priority = InfoPriority;
mutex Logger::log_mutex;