#pragma once

#include "utils.hpp"
#include <cpr/cpr.h>

#define REQ_SUCCESS(status_code) \
  status_code >= 200 && status_code <= 299 

enum class response_type : std::uint16_t
{
  success = 200, error = 404, max_types
};

namespace web
{
  inline std::string username{};
  
  auto begin_scouting(const std::string& username) -> bool;
}