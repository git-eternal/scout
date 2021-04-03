#pragma once

#include "../utils/utils.hpp"

#include <cpr/cpr.h>

// can lead to false positives, will update in future probably
#define request_success(status_code) \
  status_code >= 200 && status_code <= 299 

enum class response_type : std::uint16_t
{
  success = 200, error = 404, max_types
};

namespace web
{
  inline std::string username{};
  
  auto begin_scouting(const std::string& username) -> void;
}