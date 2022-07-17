#include <filesystem>
#include <string>

#include "Logger.hpp"

void Logger::print(const LogLevel logLevel, std::string message, const std::source_location& source)
{
	const std::string& src{ source.file_name() };
	const std::string& fileName{ (strrchr(source.file_name(), '\\') ? strrchr(source.file_name(), '\\') + 1 : source.file_name()) };
	const std::string& functionName{ source.function_name() };
	const auto line{ source.line() };
	const auto column{ source.column() };

	switch (logLevel)
	{
		case LogLevel::debug:
			message.insert(0, "[Debug] ");
			message += std::format(" [{}:{}:{}]\n", fileName, source.line(), source.column());
			std::cout << message;
			break;
		case LogLevel::info:
			message.insert(0, "[Info] ");
			message += std::format(" [{}:{}:{}]\n", fileName, source.line(), source.column());
			std::cout << message;
			break;
		case LogLevel::warning:
			message.insert(0, "[Warning] ");
			message += std::format(" [{}:{}:{}]\n", fileName, source.line(), source.column());
			std::cerr << message;
			break;
		case LogLevel::error:
			message.insert(0, "[Error] ");
			message += std::format(" [{}:{}:{}]\n", fileName, source.line(), source.column());
			std::cerr << message;
			break;
		case LogLevel::critical:
			message.insert(0, "[Critical] ");
			message += std::format(" [{}:{}:{}]\n", fileName, source.line(), source.column());
			std::cerr << message;
			break;
	}
}
