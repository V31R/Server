#pragma once
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <cctype>
#include <chrono>
#include <sstream>
#include <iostream>
#include<format>
#include <ctime>
#include <mutex>
#include <queue>
#include <thread>


class Logger {

public: 
	enum class LogLevel { WARN, ERROR, INFO, DEBUG, TRACE, ALL };
	static Logger& getInstance();
	void logging();
	std::string timestamp();
	void pushMessage(std::string msg, Logger::LogLevel lvl);

	void warn(std::string message);
	void error(std::string message);
	void info(std::string message);
	void debug(std::string message);
	void trace(std::string message);
	void all(std::string message);

	void setLevel(LogLevel level);
	static std::map <LogLevel, std::string> strLog;
	
	class Message {

	private:
		std::string message_;
		Logger::LogLevel level_;
	public:
		Message() {};
		Message(std::string msg, Logger::LogLevel lvl);

		void setMsg(std::string msg);
		void setLevel(Logger::LogLevel lvl);

		std::string getMsg();
		Logger::LogLevel getLevel();

	};

private:
	std::queue <Message> messageQueue;
	Logger() {};
	std::string filename = "Server_game.log";
    LogLevel level_;
	static Logger* instance;
	void log(Message msg);

protected:
	std::mutex mutex;
};

