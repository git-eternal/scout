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
  const std::vector<website_t> websites
  {
    { "pastebin", "https://pastebin.com/u/" + username },
    { "github", "https://github.com/" + username },
    { "pinterest", "https://pinterest.com/" + username },
    { "tumblr", "https://" + username + ".tumblr.com" },
    { "flickr", "https://flickr.com/people/" + username },
    { "vimeo", "https://vimeo.com/" + username },
    { "soundcloud", "https://soundcloud.com/" + username },
    { "medium", "https://medium.com/@/" + username },
    { "deviantart", "https://" + username + ".deviantart.com" },
    { "vk", "https://vk.com/" + username },
    { "aboutme", "https://about.me/" + username },
    { "flipboard", "https://flipboard.com/@/" + username },
    { "disqus", "https://disqus.com/by/" + username },
    { "slideshare", "https://slideshare.net/" + username },
    { "spotify", "https://open.spotify.com/user/" + username },
    { "scribd", "https://scribd.com/" + username },
    { "patreon", "https://www.patreon.com/" + username },
    { "bitbucket", "https://bitbucket.org/" + username },
    { "dailymotion", "https://www.dailymotion.com/" + username },
    { "etsy", "https://www.etsy.com/shop/" + username },
    { "cashapp", "https://cash.app/$" + username },
    { "behance", "https://www.behance.net/" + username },
    { "goodreads", "https://www.goodreads.com/" + username },
    { "keybase", "https://keybase.io/" + username },
    { "livejournal", "https://" + username + ".livejournal.com" },
    { "lastfm", "https://last.fm/user/" + username },
    { "dribbble", "https://dribbble.com/" + username },
    { "codecademy", "https://www.codecademy.com/profiles/" + username },
    { "gravatar", "https://en.gravatar.com/" + username },
    { "roblox", "https://www.roblox.com/user.aspx?username=" + username },
    { "gumroad", "https://www.gumroad.com/" + username },
    { "newgrounds", "https://" + username + ".newgrounds.com"},
    { "hubpages", "https://" + username + ".hubpages.com"},
    { "kongregate", "https://kongregate.com/accounts/" + username },
    { "wattpad", "https://www.wattpad.com/user/" + username },
    { "trakt", "https://www.trakt.tv/users/" + username },
    { "buzzfeed", "https://buzzfeed.com/" + username },
    { "tripadvisor", "https://www.tripadvisor.com/Profile/" + username },
    { "blipfm", "https://blip.fm/" + username },
    { "codementor", "https://www.codementor.io/" + username },
    { "reverbnation", "https://www.reverbnation.com/" + username },
    { "designspiration", "https://www.designspiration.com/" + username },
    { "bandcamp", "https://www.bandcamp.com/" + username },
    { "colourlovers", "https://www.colourlovers.com/lover/" + username },
    { "ifttt", "https://www.ifttt.com/p/" + username },
    { "slack", "https://" + username + ".slack.com"},
    { "wikipedia", "https://en.wikipedia.org/wiki/User:" + username },
    { "instructables", "https://www.instructables.com/member/" + username },
    { "ello", "https://ello.co/" + username },
    { "osu!", "https://osu.ppy.sh/u/" + username },
    { "minecraft", "https://namemc.com/profile/" + username },
    { "onlyfans", "https://onlyfans.com/" + username },
    { "youtube", "https://www.youtube.com/" + username },
  };

  // start the timer
  clock_tt::time_point now = clock_tt::now();

	// parallelize iteration
	std::for_each(
		std::execution::par_unseq, 
		websites.begin(), 
    websites.end(),
		[&](auto& website) -> void 
	{
		// parse title and url c++17 style
		auto [title, url] = website;

		cpr::Response r = cpr::Get(
			cpr::Url{ url.c_str() },
      cpr::Timeout{ 1000 }
		);

		// output the result to console
		cmd::output_request(website,
			r.status_code);
	});

  // end the timer
  clock_tt::time_point end = clock_tt::now();

  auto time = duration_cast<_ms_>(end - now).count();

  std::cout << "\n  time took: " << time << "ms\n";
}