#include "utils.hpp"

auto cmd::output_request(const website_t& website,
  const int status_code) -> void
{
  // extract contents from tuple
  auto [title, url] = website;

  switch (status_code)
  {
    // status 200: success
    case 200:
    {
      std::cout  << "  [" << blue << "hit" << white << "] " << url << '\n';
    }
    break;

    // status 404: error
    case 404:
    case 410:
    {
      std::cout  << "  [" << red << "nil" << white << "] " << url << '\n';
    }
    break;

    default:
    {
      std::cout << "status_code: " << status_code << '\n';
    }  
  }
}

auto cmd::initialize() -> void
{
  // needed for colored cmd output
  HANDLE out{ GetStdHandle(STD_OUTPUT_HANDLE) };

  DWORD dw_mode{ 0 }; 
  GetConsoleMode(out, &dw_mode);
  SetConsoleMode(out,
    dw_mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING);

  CONSOLE_CURSOR_INFO cursorInfo;

  GetConsoleCursorInfo(out, &cursorInfo);
  cursorInfo.bVisible = false;
  SetConsoleCursorInfo(out, &cursorInfo);
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
    std::cout << argv[0] << " -?\n";

    return false;
  }

  if (parameter_exists(argv, argv + argc, "-h"))
  {
    std::cout << "scout usage:\n";
    std::cout << " -u: username\n";
    std::cout << " -genfile: output results to file\n";
    std::cout << "ex: scout.exe -u user123 -genfile results.txt";
    std::exit(0);
  }

  if (argc <= 1)
  {
    //if (argv[0])
    //  std::cout << "usage: " << argv[0] 
    //            << " <username>" << '\n';
    //else
    //  std::cout << "usage: " 
    //            << "scout.exe <username>" << '\n';

    std::cout << argv[0] << " -?\n";

    return false;
  }

  if (argv[1] == "-?")
  {
    std::cout << "scout usage:\n";
    std::cout << " -u: username\n";
    std::cout << " -o: output results to file\n";
  }

  return true;
}