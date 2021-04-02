﻿#include "utils.hpp"

int main(int argc, char* argv[])
{
  argparse::ArgumentParser scout("scout");

  scout.add_argument("-u", "--user")
    .help("the username you want to search")
    .required()
    .action([](const std::string& value)
  {
    web::username = value;
  });

  scout.add_argument("-o", "--output")
    .help("output the results to a file")
    .action([](const std::string& value) 
  {
    cmd::output_results_to_file = true;
    cmd::results_file_name = value;
  });

  try // parse the cli arguments
  {
    scout.parse_args(argc, argv);
  }
  catch (const std::runtime_error& e) 
  {
    std::cout << e.what() << '\n' << scout;
    
    // prematurely exit the application
    std::exit(0);
  }
 
  cmd::initialize();
  cmd::print_logo();

  web::begin_scouting(web::username);

  // re-show the cursor before close!
  cmd::set_console_cursor(true);
}