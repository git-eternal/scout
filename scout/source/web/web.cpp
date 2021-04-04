#include "web.hpp"

using clock_tt = std::chrono::steady_clock;

auto web::output_request(const website_t& website, const cpr::Response& r) -> void
{
	// lock the mutex so output doesn't screw up
	std::unique_lock<decltype(m)> lock(m);

	// extract contents from tuple
	auto [name, url, error_type, message] = website;

	if (error_type == "status_code")
	{
		if (request_success(r.status_code))
		{
			std::cout << "  [" << cmd::blue << "hit" << cmd::white << "] " << url << '\n';
			cmd::results += ("[hit]: " + url + '\n');
		}
		else
		{
			if (!cmd::only_output_found)
			{
				std::cout << "  [" << cmd::red << "nil" << cmd::white << "] " << url << '\n';
				cmd::results += ("[nil]: " + url + '\n');
			}
		}
	}

	if (error_type == "message")
	{
		if (r.text.find(message) == std::string::npos)
		{
			std::cout << "  [" << cmd::blue << "hit" << cmd::white << "] " << url << '\n';
			cmd::results += ("[hit]: " + url + '\n');
		}
		else
		{
			if (!cmd::only_output_found)
			{
				std::cout << "  [" << cmd::red << "nil" << cmd::white << "] " << url << '\n';
				cmd::results += ("[nil]: " + url + '\n');
			}
		}
	}
}

auto web::begin_scouting(const std::string& username) -> void
{
	// store all the websites in tuple form
	std::vector<website_t> sites_vector{};

	// grab the json of all the websites
	cpr::Response r = cpr::Get
	(
		cpr::Header{ {"Content-Type", "application/json"} },
		cpr::Url{ "https://pastebin.com/raw/dciYgYJt" },
		cpr::Timeout{ 2000 }
	);

	nlohmann::json sites_json{ json::parse(r.text) };

	for (const auto& website : sites_json.items())
	{
		// get the website name from key
		std::string name{ website.key() };

		std::string url{ website.value()["url"] };

		// replace {} with the actual username
		if (url.find("{}") != std::string::npos)
			utils::replace(url, "{}", username);
		else
			url += username.c_str(); // append 

		std::string error_type{ website.value()["errorType"] };

		// default message is nothing by default
		// (since most sites return status codes)
		std::string message{};

		if (error_type == "message")
			website.value()["errorMsg"].get_to(message);
		
		// instantiate a new tuple and push it back
		sites_vector.push_back(
			{	name, url, error_type, message } 
		);
	}

	// start the timer
	clock_tt::time_point now = clock_tt::now();

	// sort the vector by site title
	std::sort(sites_vector.begin(), sites_vector.end(), 
		[&](website_t& s1, website_t& s2) -> bool
	{
		return(std::get<0>(s1) < std::get<0>(s2));
	});

	// this will break the sort a bit but its ok
	std::for_each(std::execution::par_unseq,
		sites_vector.begin(),
		sites_vector.end(), [&](auto& website) -> void
	{
		// parse title and url c++17 style
		auto [name, url, error_type, message] = website;

		cpr::Response r = cpr::Get
		(
			cpr::Header{ {"Content-Type", "application/json"} },
			cpr::Url{ url.c_str() },
			cpr::Timeout{ 2500 },

			// some sites may not respond if we do not provide a user agent due to them thinking we are a bot
			cpr::UserAgent
			{
				"Mozilla/5.0 (Macintosh; Intel" \
				"Mac OS X 10.12; rv:55.0)"      \
				"Gecko/20100101 Firefox/55.0"   \
			}
		);

		// output the result to console
	  output_request(website, r);
	});

	// end the timer
	clock_tt::time_point end = clock_tt::now();

	auto time = duration_cast<_ms_>(end - now).count();

	std::cout << "\n  time took: " << time << "ms ";

	if (cmd::output_results_to_file)
		cmd::write_results_to_file();
}
