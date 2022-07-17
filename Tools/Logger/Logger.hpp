#pragma once

#include <iostream>
#include <format>
#include <source_location>
#include <string>

struct FmtString
{
	std::string_view message;
	std::source_location location;

	FmtString();
	FmtString(const char* message, const std::source_location& location = std::source_location::current());
	FmtString(const std::string& message, const std::source_location& location = std::source_location::current());
};

enum class LogLevel { debug, info, warning, error, critical, count };

class Logger
{
public:
	template<typename... T>
	static inline void debug(const FmtString formatString, const T&... t)
	{
		print(LogLevel::debug, std::vformat(formatString.message, std::make_format_args(t...)), formatString.location);
	}

	template<typename... T>
	static inline void info(const FmtString formatString, const T&... t)
	{
		print(LogLevel::info, std::vformat(formatString.message, std::make_format_args(t...)), formatString.location);
	}

	template<typename... T>
	static inline void warning(const FmtString formatString, const T&... t)
	{
		print(LogLevel::warning, std::vformat(formatString.message, std::make_format_args(t...)), formatString.location);
	}

	template<typename... T>
	static inline void error(const FmtString formatString, const T&... t)
	{
		print(LogLevel::error, std::vformat(formatString.message, std::make_format_args(t...)), formatString.location);
	}

	template<typename... T>
	static inline void critical(const FmtString formatString, const T&... t)
	{
		print(LogLevel::critical, std::vformat(formatString.message, std::make_format_args(t...)), formatString.location);
	}
private:
	static void print(const LogLevel logLevel, std::string message, const std::source_location& location);
};