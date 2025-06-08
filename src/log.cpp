#include "WTools/log.hpp"
#include "WTools/file.hpp"
#include "WTools/type.hpp"
#include <chrono>
#include <cstring>
#include <ctime>
#include <format>
#include <print>
#include <string>

// void WtLogger::_write(const char *pMessage, WtMessageType sMessageType, const char *pLogFilePath, bool bVisible, bool bLogToFile, bool bShowTime) {
//     std::time_t t = time(0);
//     struct tm sNow;
//     localtime_s(&sNow, &t);

//     std::string strCurrentTime = std::format("{:0>2}:{:0>2}:{:0>2}", sNow.tm_hour, sNow.tm_min, sNow.tm_sec);

//     std::string message = std::format("{} {} ({})\n", std::format("[{}]:", sMessageType), pMessage, strCurrentTime);

//     if (bVisible) {
//         // std::print("{:<12} {} ({:0>2}:{:0>2}:{:0>2})\n", std::format("[{}]:", sMessageType), pMessage, sNow.tm_hour, sNow.tm_min, sNow.tm_sec);
//         // std::print("{} {} ({})\n", std::format("[{}]:", sMessageType), pMessage, strCurrentTime);
//         std::print("{}", message);
//     }

//     if (bLogToFile) {
//         WtFile sLogFile(pLogFilePath);

//         sLogFile.append(message.c_str());
//         // std::print("{} {} ({})\n", std::format("[{}]:", sMessageType), pMessage, strCurrentTime);
//     }
// }
void WtLogger::_write(const char *pMessage, WtMessageType sMessageType, const char *pLogFilePath, bool bVisible, bool bLogToFile, bool bShowTime) {
    std::time_t t = time(0);
    struct tm *sNow;
    sNow = localtime(&t);

    std::string strCurrentTime = std::format("{:0>2}:{:0>2}:{:0>2}", sNow->tm_hour, sNow->tm_min, sNow->tm_sec);

    std::string message = std::format("{} {} ({})\n", std::format("[{}]:", sMessageType), pMessage, strCurrentTime);

    if (bVisible) {
        // std::print("{:<12} {} ({:0>2}:{:0>2}:{:0>2})\n", std::format("[{}]:", sMessageType), pMessage, sNow.tm_hour, sNow.tm_min, sNow.tm_sec);
        // std::print("{} {} ({})\n", std::format("[{}]:", sMessageType), pMessage, strCurrentTime);
        std::print("{}", message);
    }

    if (bLogToFile) {
        WtFile sLogFile(pLogFilePath);

        sLogFile.append(message.c_str());
        // std::print("{} {} ({})\n", std::format("[{}]:", sMessageType), pMessage, strCurrentTime);
    }
}

inline bool WtLogger::needToLog(const char *pLogFilePath) {
    // return true ? pLogFilePath : false;
    return true ? !(pLogFilePath == nullptr) : false;
}

inline const char *WtLogger::determinePath(const char *pLogFilePath) {
    return pLogFilePath ? pLogFilePath : m_pLogFilePath;
}

WtResult WtLogger::log(const char *pMessage, const char *pLogFilePath) {
    pLogFilePath = determinePath(pLogFilePath);
    bool bLogToFile = needToLog(pLogFilePath);
    WtMessageType sMessageType = WtMessageType::LOG;
    WtResult sResult = WtResult::OK;

    _write(pMessage, sMessageType, pLogFilePath, false, true, m_bShowTime);
    return sResult;
}

WtResult WtLogger::message(const char *pMessage, const char *pLogFilePath, bool bVisible) {
    pLogFilePath = determinePath(pLogFilePath);
    bool bLogToFile = needToLog(pLogFilePath);
    WtMessageType sMessageType = WtMessageType::MESSAGE;
    WtResult sResult = WtResult::OK;

    _write(pMessage, sMessageType, pLogFilePath, bVisible, bLogToFile, m_bShowTime);
    return sResult;
}

WtResult WtLogger::error(const char *pMessage, const char *pLogFilePath, bool bVisible) {
    pLogFilePath = determinePath(pLogFilePath);
    bool bLogToFile = needToLog(pLogFilePath);
    WtMessageType sMessageType = WtMessageType::ERROR;
    WtResult sResult = WtResult::ERROR;

    _write(pMessage, sMessageType, pLogFilePath, bVisible, bLogToFile, m_bShowTime);
    return sResult;
}

WtResult WtLogger::info(const char *pMessage, const char *pLogFilePath, bool bVisible) {
    pLogFilePath = determinePath(pLogFilePath);
    bool bLogToFile = needToLog(pLogFilePath);
    WtMessageType sMessageType = WtMessageType::INFO;
    WtResult sResult = WtResult::OK;

    _write(pMessage, sMessageType, pLogFilePath, bVisible, bLogToFile, m_bShowTime);
    return sResult;
}

WtResult WtLogger::alert(const char *pMessage, const char *pLogFilePath, bool bVisible) {
    pLogFilePath = determinePath(pLogFilePath);
    bool bLogToFile = needToLog(pLogFilePath);
    WtMessageType sMessageType = WtMessageType::ALERT;
    WtResult sResult = WtResult::WARNING;

    _write(pMessage, sMessageType, pLogFilePath, bVisible, bLogToFile, m_bShowTime);
    return sResult;
}

WtResult WtLogger::warning(const char *pMessage, const char *pLogFilePath, bool bVisible) {
    pLogFilePath = determinePath(pLogFilePath);
    bool bLogToFile = needToLog(pLogFilePath);
    WtMessageType sMessageType = WtMessageType::WARNING;
    WtResult sResult = WtResult::WARNING;

    _write(pMessage, sMessageType, pLogFilePath, bVisible, bLogToFile, m_bShowTime);
    return sResult;
}

WtResult WtLogger::debug(const char *pMessage, const char *pLogFilePath, bool bVisible) {
    pLogFilePath = determinePath(pLogFilePath);
    bool bLogToFile = needToLog(pLogFilePath);
    WtMessageType sMessageType = WtMessageType::WARNING;
    WtResult sResult = WtResult::WARNING;

    _write(pMessage, sMessageType, pLogFilePath, bVisible, bLogToFile, m_bShowTime);
    return sResult;
}

WtResult WtLogger::consoleOutput(const char *pMessage) {
    WtMessageType sMessageType = WtMessageType::MESSAGE;
    WtResult sResult = WtResult::OK;

    _write(pMessage, sMessageType, nullptr, true, false, m_bShowTime);
    return sResult;
}
