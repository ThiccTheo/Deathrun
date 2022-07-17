#pragma once

#include <format>

enum class LogLevel { debug, info, warning, error, critical, count };

class Logger
{
public:
	template<typename... T>
	static inline void debug(std::string_view fmt, const T&... t)
	{
		print(LogLevel::debug, std::vformat(fmt, std::make_format_args(t...)));
	}

	template<typename... T>
	static inline void info(std::string_view fmt, const T&... t)
	{
		print(LogLevel::info, std::vformat(fmt, std::make_format_args(t...)));
	}

	template<typename... T>
	static inline void warning(std::string_view fmt, const T&... t)
	{
		print(LogLevel::warning, std::vformat(fmt, std::make_format_args(t...)));
	}

	template<typename... T>
	static inline void error(std::string_view fmt, const T&... t)
	{
		print(LogLevel::error, std::vformat(fmt, std::make_format_args(t...)));
	}

	template<typename... T>
	static inline void critical(std::string_view fmt, const T&... t)
	{
		print(LogLevel::critical, std::vformat(fmt, std::make_format_args(t...)));
	}
private:
	static void print(const LogLevel logLevel, std::string message);
};