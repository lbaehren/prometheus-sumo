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

#include <boost/tokenizer.hpp>

#include <lib/StatisticsHBZ.h>

// === Main routine =============================================================

int main(int argc, char *argv[])
{
  using namespace std;
  using namespace boost;
  using namespace prometheus;
  
  std::string data          = "data.csv";
  unsigned int nofLines     = 0;
  unsigned int nofDownloads = 0;
  unsigned int nofSearches  = 0;
  std::vector<std::string> columns;
  std::set<std::string> dates;
  std::set<std::string> institutions;
  std::vector<StatisticsHBZ> entries;
  std::vector<StatisticsHBZ>::iterator it;

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
  
  std::vector<std::string> vec;
  std::string line;

  /* Extract the first line with the column headers */
  {
    getline(in,line);
    Tokenizer tok(line);
    columns.assign(tok.begin(),tok.end());
  }
  
  while (getline(in,line)) {
    Tokenizer tok(line);
    vec.assign(tok.begin(),tok.end());
    
    if (vec.size() < 3) continue;
    
    /* Display current line of data */
    // copy(vec.begin(), vec.end(),
    // 	   ostream_iterator<string>(cout, "|"));
    
    /* Book-keeping */
    institutions.insert(vec[1]);
    nofSearches  += atoi((vec[6]).c_str());
    nofDownloads += atoi((vec[7]).c_str());
    
    entries.push_back(StatisticsHBZ(vec[0],vec[1],vec[2],vec[3]));
    
    /* Increment line counter */
    ++nofLines;
  }

  //________________________________________________________
  // Accumulation of data

  for (it=entries.begin(); it!=entries.end(); ++it) {
    dates.insert(it->time());
  }
  
  //________________________________________________________
  // Processing summary

  std::cout << "-- Completed scanning input file."                << std::endl;
  std::cout << "  -- Lines of data     = " << entries.size()      << std::endl;
  std::cout << "  -- nof. data columns = " << columns.size()      << std::endl;
  std::cout << "  -- nof. institutions = " << institutions.size() << std::endl;
  std::cout << "  -- nof. searches     = " << nofSearches         << std::endl;
  std::cout << "  -- nof. downloads    = " << nofDownloads        << std::endl;
  std::cout << "  -- Data columns      = " << columns             << std::endl;
  std::cout << "  -- Periods in time   = " << dates               << std::endl;
  std::cout << "  -- Institution names = " << institutions        << std::endl;

}
