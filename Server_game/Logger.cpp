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

    if (!instance) {

        std::call_once(flag, []() { instance = new Logger(); });

    }
        
    return *instance;

}

void Logger::log(Message msg) {

    std::ofstream file(filename, std::fstream::out | std::fstream::app);
    std::string output;
    output.append(timestamp());
    output.append(" [");
    output.append(strLog.find(msg.getLevel())->second);
    output.append("] ");
    output.append(msg.getMsg());
    output.push_back('\n');
    file << output;
    file.close();

}

void Logger::logging()
{
    std::thread t1([&]() {

        while (true){

            if (!messageQueue.empty()) {

                Message temp = messageQueue.front();
                mutex.lock();
                messageQueue.pop();
                mutex.unlock();
                log(temp);

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

void Logger::pushMessage(std::string msg, Logger::LogLevel lvl){

    mutex.lock();
    messageQueue.push(Message(msg, lvl));
    mutex.unlock();

}

void Logger::warn(std::string message) {

    pushMessage(message, LogLevel::WARN);

}

void Logger::error(std::string message) {

    pushMessage(message, LogLevel::ERROR);

}

void Logger::info(std::string message) {

    pushMessage(message, LogLevel::INFO);

}

void Logger::debug(std::string message) {

    pushMessage(message, LogLevel::DEBUG);

}

void Logger::trace(std::string message) {

    pushMessage(message, LogLevel::TRACE);

}

void Logger::all(std::string message) {

    pushMessage(message, LogLevel::ALL);

}

void Logger::setLevel(LogLevel level){

    level_ = level;

}

Logger::Message::Message(std::string msg, Logger::LogLevel lvl): 

    message_(msg), 
    level_(lvl) 

{}


void Logger::Message::setMsg(std::string msg){

    message_ = msg;

}

void Logger::Message::setLevel(Logger::LogLevel lvl){

    level_ = lvl;

}

std::string Logger::Message::getMsg(){

    return message_;

}

Logger::LogLevel Logger::Message::getLevel(){

    return level_;

}
