#include "utils.hpp"

int main(int argc, char* argv[])
{
  // prematurely close if invalid params
  if(!cmd::check_parameters(argc, argv))
    std::exit(-1);
 
  cmd::initialize();
 
  cmd::print_logo();

  web::begin_scouting(web::username);

  // re-show the cursor before close!
  cmd::set_console_cursor(true);
}