#pragma once

#include <format>

class Logger
{
public:
	template<typename... T>
	static inline void info(std::string_view fmt, const T&... t)
	{
		auto message = std::vformat(fmt, std::make_format_args(t...));
		message += '\n';
		std::cout << message;
	}
};