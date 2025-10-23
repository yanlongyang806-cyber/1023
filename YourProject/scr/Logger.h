#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <mutex>
#include <string>
#include <sstream>
#include <windows.h>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR
};

class Logger {
public:
    static Logger& Instance() {
        static Logger instance;
        return instance;
    }

    void Log(const std::string& msg, LogLevel level) {
        if (level < logLevel_) return;

        std::lock_guard<std::mutex> lock(mtx_);
        std::ofstream ofs(kLogPath, std::ios::app);
        if (!ofs.is_open()) return;

        SYSTEMTIME st;
        GetLocalTime(&st);
        ofs << "[" << st.wYear << "-" << st.wMonth << "-" << st.wDay << " "
            << st.wHour << ":" << st.wMinute << ":" << st.wSecond << "] ";

        switch (level) {
            case LogLevel::INFO: ofs << "[INFO] "; break;
            case LogLevel::WARNING: ofs << "[WARNING] "; break;
            case LogLevel::ERROR: ofs << "[ERROR] "; break;
        }

        ofs << msg << std::endl;
    }

private:
    Logger() = default;
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    std::mutex mtx_;
    const std::string kLogPath = "D:\\SPP-LegionV2\\Servers\\veh_patch.log";
    LogLevel logLevel_ = LogLevel::INFO;
};

#endif // LOGGER_H
