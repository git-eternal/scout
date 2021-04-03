#pragma once

// global include header file

// exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN

// use std::min and std::max instead of min() and max()
#define NOMINMAX

#include "deps/args.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <tuple>
#include <Windows.h>
#include <chrono>
#include <execution>
#include <shared_mutex>

// nlohmann json
#include <nlohmann/json.hpp>

using namespace nlohmann;
using namespace std::chrono_literals;
#define _ms_ std::chrono::milliseconds
