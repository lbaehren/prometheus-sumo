/*!
  \file tParseFixtures.cc
  \author Lars Baehren
*/

#include <fstream>
#include <yaml-cpp/yaml.h>

int main (int argc, char *argv[])
{
  std::string filename;

  /* Check parameter provided from the command line */
  if ( argc>1 ) {
    filename    = std::string(argv[1]);
  } else {
    std::cerr << "Missing name of input file - aborting!" << std::endl;
    return 1;
  }
  
  /* Open input stream */
  try {
  std::ifstream fin(filename.c_str());
  YAML::Parser parser(fin);
  
  YAML::Node doc;
  parser.GetNextDocument(doc);

  } catch(YAML::ParserException& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
