#include "utils.hpp"

auto cmd::output_request(const website_t& website,
	const int status_code) -> void
{
	// lock the mutex so output doesn't screw up
	std::unique_lock<decltype(m)> lock(m);

	// extract contents from tuple
	auto [title, url] = website;

	switch (status_code)
	{
	// status 200: success
	case 200:
		
		std::cout << "  [" << blue << "hit" << white << "] " << url << '\n';
		cmd::results += ("[hit]: " + url + '\n');
		break;

	// status 404: error
	case 404:
	case 410:
	case 301:
	case 520:
	case 524:
		std::cout << "  [" << red << "nil" << white << "] " << url << '\n';
		cmd::results += ("[nil]: " + url + '\n');
		break;

	default:
		std::cout << "status_code: " << status_code << '\n';
	}
}

auto cmd::parameter_exists(char** begin, char** end,
	const std::string& option) -> bool
{
	return std::find(begin, end, option) != end;
}

auto cmd::check_parameters(int argc, char* argv[]) -> bool
{
	if (argc <= 1)
	{
		std::cout << "\nusage help: " << argv[0] << " -h, --help\n";
		return false;
	}

	auto end_arg{ argv + argc };

	if (parameter_exists(argv, end_arg, "-h") ||
		parameter_exists(argv, end_arg, "--help"))
	{
		std::cout << "\nscout arguments:\n";
		std::cout << "  -h, --help\t" <<
			"show this help message and exit\n";
		std::cout << "  -u, --user\t" <<
			"the username you want to search\n";
		std::cout << "  -o, --genf\t" <<
			"output the results to a file\n\n";
		std::cout << "example usage: scout.exe -u user123 --genf results.txt\n";

		std::exit(0);
	}

	if (parameter_exists(argv, end_arg, "-u") ||
		parameter_exists(argv, end_arg, "--user"))
	{
		if (argv[2] != nullptr)
			web::username = argv[2];
		else
		{
			std::cout << "invalid arg (failed to provide username)\n";
			std::exit(0);
		}
	}

	if (parameter_exists(argv, end_arg, "-o") ||
		parameter_exists(argv, end_arg, "--genf"))
	{
		std::cout << "wanted file\n";

		if (std::string(argv[4]).find(".txt") != std::string::npos)
		{
			output_results_to_file = true;

			std::cout << "setting: " << argv[4];
			cmd::results_file_name = argv[4];
			std::cout << " file name: " << cmd::results_file_name;
		}
	}

	return true;
}

auto cmd::print_logo() -> void
{
	std::cout << blue << logo << white << '\n';
}

auto cmd::set_console_cursor(bool shown = false) -> void
{
	// needed for colored cmd output
	HANDLE out{ GetStdHandle(STD_OUTPUT_HANDLE) };

	// store the cursor information
	CONSOLE_CURSOR_INFO cursor_info{};

	GetConsoleCursorInfo(out, &cursor_info);

	// set the cursor visibility (true/false)
	cursor_info.bVisible = shown;
	SetConsoleCursorInfo(out, &cursor_info);
}

auto cmd::write_results_to_file() -> void
{
	std::ofstream out(results_file_name);

	if (!out.is_open())
		std::cerr << "error occurred while making results file\n";

	out << cmd::results;

	out.close();
}

auto cmd::initialize() -> void
{
	// needed for colored cmd output
	HANDLE out{ GetStdHandle(STD_OUTPUT_HANDLE) };

	DWORD dw_mode{ 0 }; GetConsoleMode(out, &dw_mode);

	// needed for colored cmd output
	SetConsoleMode(out,
		dw_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING);

	// hide the console cursor
	set_console_cursor(false);
}