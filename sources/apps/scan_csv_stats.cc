/*!
  \file scan_csv_stats.cc
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
#include <set>
#include <map>

#include <lib/StatisticsReaderHBZ.h>

// === Main routine =============================================================

int main(int argc, char *argv[])
{
  using namespace std;
  using namespace boost;
  using namespace prometheus;
  
  std::string filename = "data.csv";

  //________________________________________________________
  // Process parameters from the command line
  
  if (argc < 2) {
    std::cerr << "ERROR - missing name of input file!" << std::endl;
  } else {
    filename = argv[1];
  }

  //________________________________________________________
  // Process the data file

  StatisticsReaderHBZ reader (filename);

  if (reader.processFile()) {

    std::cout << "[StatisticsReaderHBZ] Completed scanning input file." << std::endl;

    std::cout << "-- nof. data columns = " << reader.nofColumns() << std::endl;
    std::cout << "-- nof. data entries = " << reader.nofEntries() << std::endl;
    std::cout << "-- nof. institutions = " << reader.institutions().size() << std::endl;

    std::cout << "-- Data columns      = " << reader.columns()      << std::endl;
    std::cout << "-- Institutions      = " << reader.institutions() << std::endl;
  }
  
}
