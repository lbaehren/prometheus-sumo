
#include <iostream>
#include <string>

#include <tinyxml2.h>

int test_char_buffer (std::string const &teststring="<element/>")
{
  std::cout << "\n[TestXML::test_char_buffer]\n" << std::endl;

  int status = 0;
  
  tinyxml2::XMLDocument doc;
  doc.Parse(teststring.c_str());
  status = doc.ErrorID();
   
   return status;
}

/*!
  \file TestXML.cc
  \ingroup prometheus
  \author Lars Baehren
*/

int main(int argc, char* argv[])
{
  int status = 0;
  
  status += test_char_buffer();

  return 0;
}
