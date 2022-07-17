#include <iostream>

#include "Logger.hpp"

void Logger::print(const LogLevel logLevel, std::string message)
{
	switch (logLevel)
	{
		case LogLevel::debug:
			message.insert(0, "[DEBUG]: ");
			message.push_back('\n');
			std::cout << message;
			break;
		case LogLevel::info:
			message.insert(0, "[INFO]: ");
			message.push_back('\n');
			std::cout << message;
			break;
		case LogLevel::warning:
			message.insert(0, "[WARNING]: ");
			message.push_back('\n');
			std::cerr << message;
			break;
		case LogLevel::error:
			message.insert(0, "[ERROR]: ");
			message.push_back('\n');
			std::cerr << message;
			break;
		case LogLevel::critical:
			message.insert(0, "[CRITICAL]: ");
			message.push_back('\n');
			std::cerr << message;
			break;
	}
}
