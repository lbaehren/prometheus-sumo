/*!
  \file TestBoostTokenizerCSV.cc
  \brief Parse CSV file with Boost Tokenizer

  Boost provides tokenizers that are easy to construct and use. To setup a
  tokenizer you select one of the provided tokenizer functions. Tokenizer is
  instantiated with the string that is to be parsed. You can then use standard
  iterator interface to access parsed tokens, tokenizer and tokenizer function
  take care of parsing the string. Optionaly you can use other standard
  algorithms that operate on iterators, example below uses
  \c std::vector initialization using \c begin() and \c end() iterators.

  \li [Parse CSV File With Boost Tokenizer In C++](http://mybyteofcode.blogspot.de/2010/02/parse-csv-file-with-boost-tokenizer-in.html)
  \li [Boost C++ libraries](http://www.boost.org)
  \li [Boost Tokenizer package](http://www.boost.org/doc/libs/1_50_0/libs/tokenizer)
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>

#include <boost/tokenizer.hpp>

int main(int argc, char *argv[])
{
  using namespace std;
  using namespace boost;
  
  std::string data      = "data.csv";
  unsigned int nofLines = 0;
  
  //________________________________________________________
  // Process parameters from the command line
  
  if (argc < 2) {
    std::cerr << "ERROR - missing name of input file!" << std::endl;
  } else {
    data = argv[1];
  }

  //________________________________________________________
  // Open input data file
  
  ifstream in(data.c_str());
  if (!in.is_open()) return 1;
  
  typedef tokenizer< escaped_list_separator<char> > Tokenizer;
  
  vector< string > vec;
  string line;

  cout << "\n------------------------------------------------------------" << endl;
  
  while (getline(in,line))
    {
      Tokenizer tok(line);
      vec.assign(tok.begin(),tok.end());
      
      if (vec.size() < 3) continue;
      
      copy(vec.begin(), vec.end(),
	   ostream_iterator<string>(cout, "|"));

      // Increment line counter
      ++nofLines;
      
      cout << "\n------------------------------------------------------------" << endl;
    }

  std::cout << "-- Completed scanning input file - processed " << nofLines
	    << " lines of data." 
	    << std::endl;
}
