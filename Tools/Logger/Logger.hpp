#pragma once

#include <iostream>
#include <format>
#include <source_location>

enum class LogLevel { debug, info, warning, error, critical, count };

class Logger
{
public:
	template<typename... T>
	static inline void debug(std::string_view fmt, const T&... t, const std::source_location& source = std::source_location::current())
	{
		print(LogLevel::debug, std::vformat(fmt, std::make_format_args(t...)), source);
	}

	template<typename... T>
	static inline void info(std::string_view fmt, const T&... t, const std::source_location& source = std::source_location::current())
	{
		print(LogLevel::info, std::vformat(fmt, std::make_format_args(t...)), source);
	}

	template<typename... T>
	static inline void warning(std::string_view fmt, const T&... t, const std::source_location& source = std::source_location::current())
	{
		print(LogLevel::warning, std::vformat(fmt, std::make_format_args(t...)), source);
	}

	template<typename... T>
	static inline void error(std::string_view fmt, const T&... t, const std::source_location& source = std::source_location::current())
	{
		print(LogLevel::error, std::vformat(fmt, std::make_format_args(t...)), source);
	}

	template<typename... T>
	static inline void critical(std::string_view fmt, const T&... t, const std::source_location& source = std::source_location::current())
	{
		print(LogLevel::critical, std::vformat(fmt, std::make_format_args(t...)), source);
	}
private:
	static void print(const LogLevel logLevel, std::string message, const std::source_location& source);
};