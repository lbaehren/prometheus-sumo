/*!
  \file tParseFixtures.cc
  \author Lars Baehren
*/

#include <iostream>
#include <fstream>
#include <string>
#include <yaml-cpp/yaml.h>

// === Data structures ==========================================================

struct Role {
  std::string title;
  std::string id;
};

// === Main function ============================================================

int main (int argc, char *argv[])
{
  std::string filename;
  
  /* Check parameter provided from the command line */
  if ( argc>1 ) {
    filename    = std::string(argv[1]);
    std::cout << "--> Input file = " << filename << std::endl;
  } else {
    std::cerr << "Missing name of input file - aborting!" << std::endl;
    return 1;
  }

  YAML::Node doc;
  
  /* Open input stream */
  std::cout << "--> Opening input stream" << std::endl;
  try {
    std::ifstream fin(filename.c_str());
    YAML::Parser parser(fin);
    
    std::cout << "--> Parsing document" << std::endl;
    parser.GetNextDocument(doc);
    
    for (unsigned int i=0; i<doc.size(); i++) {
      std::cout << "--> Scanning role " << i << " ..." << std::endl;
      Role role;
      // doc[i] >> role;
    }
  } catch(YAML::ParserException& e) {
    std::cerr << e.what() << std::endl;
  }
  
  return 0;
}

