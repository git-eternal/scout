#include "utils.hpp"

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

	// add the string to the file
	out << cmd::results; out.close();

	std::cout << "(wrote results to file)\n";
}

auto utils::replace(std::string& str, 
	const std::string& from, 
	const std::string& to) -> bool
{
	size_t start_pos = str.find(from);

	if (start_pos == std::string::npos)
		return false;

	str.replace(start_pos, from.length(), to);

	return true;
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