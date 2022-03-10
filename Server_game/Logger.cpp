#include "Logger.h"

std::map<Logger::LogLevel, std::string> Logger::strLog{

        {Logger::LogLevel::WARN, "WARN"},
        {Logger::LogLevel::ERROR, "ERROR"},
        {Logger::LogLevel::TRACE, "TRACE"},
        {Logger::LogLevel::DEBUG, "DEBUG"},
        {Logger::LogLevel::INFO, "INFO"},
        {Logger::LogLevel::ALL, "ALL"},

};

Logger* Logger::instance{};

Logger& Logger::getInstance() {

    static std::once_flag flag;
    if (!instance)
        std::call_once(flag, []() { instance = new Logger(); });
    return *instance;

}

Logger::LogLevel Logger::getLogLevelFromStr(std::string level){

    std::string str;
    std::transform(level.begin(), level.end(), std::back_inserter(str), toupper);

    
    for (auto level : strLog) {

        if (str == level.second) {

            return level.first;

        }

    }

    throw str + "- This level of logging does not exist";

}

void Logger::log(std::string message, LogLevel level) {

    std::ofstream file(filename, std::fstream::out | std::fstream::app);
    std::string output;
    output.append(timestamp());
    output.append(" [");
    output.append(strLog.find(level)->second);
    output.append("] ");
    output.append(message);
    output.push_back('\n');
    file << output;
    file.close();

}

void Logger::logging()
{
    std::thread t1([&]() {
        while (true)
            {
                if (!qMessage.empty()) {
                    Message temp = qMessage.front();
                    qMessage.pop();
                    log(temp.getMsg(), temp.getLevel());

                }
            }
    });

    t1.detach();
       
}

std::string Logger::timestamp() {

    setlocale(LC_ALL, "RUS");
    try {

        const auto& timeZoneDatabase = std::chrono::get_tzdb();
        const auto& currentZone = timeZoneDatabase.current_zone();
        const std::chrono::zoned_time zt{ currentZone->name(), std::chrono::system_clock::now() };

        return std::format("{:%Y-%m-%d %H:%M:%OS}", zt);

    }
    catch (std::exception& a) {

        std::cout << a.what();

    }
    
}

void Logger::warn(std::string message) {

    Message temp(message, LogLevel::WARN);
    m.lock();
    qMessage.push(temp);
    m.unlock();

}

void Logger::error(std::string message) {

    Message temp(message, LogLevel::ERROR);
    m.lock();
    qMessage.push(temp);
    m.unlock();

}

void Logger::info(std::string message) {

    Message temp(message, LogLevel::INFO);
    m.lock();
    qMessage.push(temp);
    m.unlock();

}

void Logger::debug(std::string message) {

    Message temp(message, LogLevel::DEBUG);
    m.lock();
    qMessage.push(temp);
    m.unlock();

}

void Logger::trace(std::string message) {

    Message temp(message, LogLevel::TRACE);
    m.lock();
    qMessage.push(temp);
    m.unlock();

}

void Logger::all(std::string message) {

    Message temp(message, LogLevel::ALL);
    m.lock();
    qMessage.push(temp);
    m.unlock();

}

void Logger::setLevel(LogLevel level){

    level_ = level;

}

void Logger::Message::setMsg(std::string msg)
{

    message_ = msg;

}

void Logger::Message::setLevel(Logger::LogLevel lvl)
{

    level_ = lvl;

}

std::string Logger::Message::getMsg()
{

    return message_;

}

Logger::LogLevel Logger::Message::getLevel()
{

    return level_;

}
