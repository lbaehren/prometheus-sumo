
#include <iostream>
#include <string>

#include <tinyxml2.h>

//______________________________________________________________________________
//                                                              test_char_buffer

/*!
  \brief Test parsing a simple string stored in character buffer
  \param teststring -- Simple string containing some \ref xml syntax.
  \return status -- Return status of the function; returns non-zero in case an
                    an error is caught.
*/
int test_char_buffer (std::string const &teststring="<element/>")
{
  std::cout << "\n[TestXML::test_char_buffer]\n" << std::endl;

  int status = 0;
  
  std::cout << "--> Input string = " << teststring << std::endl;
  
  tinyxml2::XMLDocument doc;
  doc.Parse(teststring.c_str());
  status = doc.ErrorID();
   
   return status;
}

// === Main function ===========================================================

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
