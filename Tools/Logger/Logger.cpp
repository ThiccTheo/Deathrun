#include <filesystem>

#include "Logger.hpp"

void Logger::print(const LogLevel logLevel, std::string message, const std::source_location source)
{
	switch (logLevel)
	{
		case LogLevel::debug:
			message.insert(0, "[Debug] ");
			message.push_back(' ');
			message += std::format("[{}:{}:{}]\n", (strrchr(source.file_name(), '\\') ? strrchr(source.file_name(), '\\') + 1 : source.file_name()), source.line(), source.column());
			std::cout << message;
			break;
		case LogLevel::info:
			message.insert(0, "[Info] ");
			message.push_back(' ');
			message += std::format("[{}:{}:{}]\n", (strrchr(source.file_name(), '\\') ? strrchr(source.file_name(), '\\') + 1 : source.file_name()), source.line(), source.column());
			std::cout << message;
			break;
		case LogLevel::warning:
			message.insert(0, "[Warning] ");
			message.push_back(' ');
			message += std::format("[{}:{}:{}]\n", (strrchr(source.file_name(), '\\') ? strrchr(source.file_name(), '\\') + 1 : source.file_name()), source.line(), source.column());
			std::cerr << message;
			break;
		case LogLevel::error:
			message.insert(0, "[Error] ");
			message.push_back(' ');
			message += std::format("[{}:{}:{}]\n", (strrchr(source.file_name(), '\\') ? strrchr(source.file_name(), '\\') + 1 : source.file_name()), source.line(), source.column());
			std::cerr << message;
			break;
		case LogLevel::critical:
			message.insert(0, "[Critical] ");
			message.push_back(' ');
			message += std::format("[{}:{}:{}]\n", (strrchr(source.file_name(), '\\') ? strrchr(source.file_name(), '\\') + 1 : source.file_name()), source.line(), source.column());
			std::cerr << message;
			break;
	}
}
