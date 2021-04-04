#pragma once

#include "../global.hpp"
#include "../web/web.hpp"

const std::string logo = R"(                       _     _   ___  
   ___  ___ ___  _   _| |_  / | / _ \ 
  / __|/ __/ _ \| | | | __| | || | | |
  \__ \ (_| (_) | |_| | |_  | || |_| |
  |___/\___\___/ \__,_|\__| |_(_)___/ 
)";

namespace cmd
{
	// console colors (portable)
	inline const char* white = "\033[0m";
	inline const char* black = "\x1B[30m";
	inline const char* green = "\x1B[32m";
	inline const char* orange = "\x1B[33m";
	inline const char* blue = "\x1B[36;1m";
	inline const char* purple = "\033[35m";
	inline const char* clear = "\033c";
	inline const char* red = "\x1B[31m";

	auto initialize() -> void;
	auto set_console_cursor(bool shown) -> void;
	auto write_results_to_file() -> void;

	auto __forceinline print_logo() -> void
	{
		std::cout << blue << logo << white << '\n';
	}

	inline std::string results{};
	inline std::string results_file_name{};
	inline bool output_results_to_file{};
	inline bool only_output_found{};
}

namespace utils
{
	auto replace(std::string& str,
		const std::string& from,
		const std::string& to) -> bool;
}