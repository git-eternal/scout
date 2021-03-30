#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <Windows.h>
#include <chrono>
#include <execution>

#include "web.hpp"

// website title  website url
using website_t = std::tuple<std::string, std::string>;

const std::string logo = R"(                       _     _   ___  
   ___  ___ ___  _   _| |_  / | / _ \ 
  / __|/ __/ _ \| | | | __| | || | | |
  \__ \ (_| (_) | |_| | |_  | || |_| |
  |___/\___\___/ \__,_|\__| |_(_)___/ 
)";

using namespace std::chrono_literals;

#define _ms_ std::chrono::milliseconds

namespace cmd
{
	auto output_request(const website_t& website, 
		const int status_code) -> void;

	auto initialize() -> void;

  auto check_parameters(int argc, char* argv[]) -> bool;

	inline const char* white = "\033[0m";
	inline const char* black = "\x1B[30m";
	inline const char* green = "\x1B[32m";
	inline const char* orange = "\x1B[33m";
	inline const char* blue = "\x1B[36;1m";
	inline const char* purple = "\033[35m";
	inline const char* clear = "\033c";
	inline const char* red = "\x1B[31m";
}