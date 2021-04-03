#include "web.hpp"

/*
	add internet check and give warning if no internet lol
	output the results to a file. if they have the argument set
  parse the websites from a json (file or a pastebin raw)
  add data breach option (enter email)?
*/

using clock_tt = std::chrono::steady_clock;

auto web::begin_scouting(const std::string& username) -> bool
{
  cpr::Response r = cpr::Get
  (
    cpr::Url{ "https://pastebin.com/raw/1rwRvXKJ" },
    cpr::Timeout{ 2000 }
  );

  nlohmann::json sites_json{ nlohmann::json::parse(r.text) };

	// store all the websites in tuple form
	std::vector<website_t> sites_vector{};
	
	for (auto& website : sites_json["websites"].items())
	{
		std::string url = website.value()["url"];

		// if url requires username in middle, replace
		if (url.find("username") != std::string::npos)
			utils::replace(url, "username", username);
		else
			url += username.c_str(); // append username

		// instantiate a new tuple and push it back
		sites_vector.push_back(
			{ website.value()["title"], url }
		);
	}

	// start the timer
  clock_tt::time_point now = clock_tt::now();

	std::for_each(std::execution::par_unseq, 
		sites_vector.begin(),
		sites_vector.end(), [&](auto& website) -> void
	{
 		// parse title and url c++17 style
 		auto [title, url] = website;

		cpr::Response r = cpr::Get
		(
			cpr::Url{ url.c_str() },
			cpr::Timeout{ 2000 },

			// some sites may not respond if we do not provide a user agent due to them thinking we are a bot
			cpr::UserAgent
			{ 
			  "Mozilla/5.0 (Macintosh; Intel" \
			  "Mac OS X 10.12; rv:55.0)"      \
			  "Gecko/20100101 Firefox/55.0"   \
			}
		);

 		// output the result to console
 		cmd::output_request(website, r.status_code);
	});

	// end the timer
	clock_tt::time_point end = clock_tt::now();

	auto time = duration_cast<_ms_>(end - now).count();

	std::cout << "\n  time took: " << time << "ms ";

	if (cmd::output_results_to_file)
    cmd::write_results_to_file();
}