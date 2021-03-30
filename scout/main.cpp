#include "utils.hpp"

int main(int argc, char* argv[])
{
  // prematurely close if invalid params
  if(!cmd::check_parameters(argc, argv))
    std::exit(-1);
 
  cmd::initialize();
  
  std::cout << cmd::blue << logo << cmd::white << '\n';

  // parse the username
  std::string username{ argv[1] };

  web::begin_scouting(username);
}