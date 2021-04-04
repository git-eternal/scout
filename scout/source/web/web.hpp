#pragma once

#include "../utils/utils.hpp"

#include <cpr/cpr.h>

// can lead to false positives, will update in future probably
#define request_success(status_code) \
  status_code >= 200 && status_code <= 299 

//enum class error_type : std::uint16_t
//{
//  message, status_code, response_url, max_types
//};

                         // website title  website url error type   error msg
using website_t = std::tuple<std::string, std::string, std::string, std::string>;

namespace web
{
  inline std::string username{};
  
  auto output_request(const website_t& website, const cpr::Response& r) -> void;

  auto begin_scouting(const std::string& username) -> void;

  inline std::shared_timed_mutex m{};

  //auto output_request(const website_t& website, const cpr::Response& response, const error_type& type) -> void;

  //auto output_request(
	 // const website_t& website, 
	 // const cpr::Response& response,
	 // const error_type& type) -> void;
}