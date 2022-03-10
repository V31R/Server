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
#include <format>
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
	void pushMessage(const std::string &msg, Logger::LogLevel lvl);

	void warn(const std::string &message);
	void error(const std::string &message);
	void info(const std::string &message);
	void debug(const std::string &message);
	void trace(const std::string &message);
	void all(const std::string &message);

	static std::map <LogLevel, std::string> strLog;
	
	class Message {

	private:
		std::string message_;
		Logger::LogLevel level_;
	public:
		Message() {};
		Message(const std::string &msg, Logger::LogLevel lvl);

		void setMsg(const std::string &msg);
		void setLevel(Logger::LogLevel lvl);

		std::string getMsg() const; 
		Logger::LogLevel getLevel() const;

	};

private:
	std::queue <Message> messageQueue;
	Logger() {};
	std::string filename = "Server_game.log";
	static Logger* instance;
	void log(const Message &msg);

protected:
	std::mutex mutex;
};

