/***************************************************************************
 *   Copyright (C) 2012                                                    *
 *   Lars B"ahren (lbaehren@gmail.com)                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

/*!
  \file testApacheLogs.cc
  \ingroup prometheus
  \ingroup tests
  \author Lars Baehren
  \date 2012-10-16

  For further examples see e.g.

  \li [Regular Expressions in C++ with Boost.Regex](http://onlamp.com/pub/a/onlamp/2006/04/06/boostregex.html)
  \li [regex_split example: spit out linked URL's](http://www.boost.org/doc/libs/1_41_0/libs/regex/example/snippets/regex_split_example_2.cpp)
  \li [Introduction to boost::spirit](http://www.boost.org/doc/libs/1_34_0/libs/spirit/doc/introduction.html)
*/

#include <Statistics/ApacheCombinedLog.h>

//_______________________________________________________________________________
//                                                                 parse_examples

/*!
  \brief Parse the text in the \c examples for a regular expression
  \param examples   -- Array with example text strings to be inspected.
  \param expression -- Array with regular expressions used for matching operation.
*/
int parse_examples (std::vector<std::string> const &examples,
                    std::vector<std::string> const &expression)
{
  /* Check input data */
  if (examples.empty() || expression.empty()) {
    std::cerr << "[testApacheLogs::parse_examples] ERROR"
              << " Empty text examples or regex expressions"
              << std::endl;
    return -1;
  }

  /* Local variables */
  int status        = 0;
  int numExample    = 0;
  int numExpression = 0;

  /* Go through the combination of text examples and matching expressions */
  try {
    for (numExample=0; numExample<examples.size(); ++numExample) {
      std::cout << "-- string = \"" << examples[numExample] << "\"" << std::endl;
      for (numExpression=0; numExpression<expression.size(); ++numExpression) {
        boost::regex e (expression[numExpression]);
	std::cout << "--> regex = \"" << expression[numExpression] << "\"";
        if (regex_match(examples[numExample], e)) {
	  std::cout << "  =>  OK" << std::endl;
        } else {
	  std::cout << "  =>  Not found!" << std::endl;
        }
      }
    }
  } catch (std::exception &e) {
    std::cerr << "" << e.what() << std::endl;
    ++status;
  }

  return status;
}

//_______________________________________________________________________________
//                                                               test_boost_regex

/*!
  \brief Test working with the boost::regex library
*/
int test_boost_regex ()
{
  std::cout << "\n[testApacheLogs::test_boost_regex]\n" << std::endl;

  int status = 0;
  std::vector<std::string> examples;
  std::vector<std::string> expressions;
  boost::cmatch what;

  /* Strings to be used as test input */
  std::string stringLatex  = "The following word will be set in \textbf{bold}.";
  std::string stringApache = "127.0.0.1 - - [15/Oct/2012:13:58:21 +0200] \"GET /phpmyadmin/index.php HTTP/1.1\" 200 3051";

  // ---[Parse credit card number]------------------------------------

  std::cout << "[1] Parse credit card number ..." << std::endl;
  try {
    /* Text examples to parse */
    examples.clear();
    examples.push_back("1234-2345-3456-4567");
    examples.push_back("1234-2345-3456-456a");
    examples.push_back("1234-2345-3456-45678");
    examples.push_back("1234-2345-3456-4567-5678");
    /* Parser expression */
    expressions.clear();
    expressions.push_back ("([[:digit:]]{4}[- ]){3}[[:digit:]]{4}");
    expressions.push_back ("([[:digit:]]{4}[- ]){3}[[:digit:]]{5}");
    /* Parse the examples*/
    status += parse_examples (examples, expressions);
  } catch (std::exception &e) {
    std::cerr << "" << e.what() << std::endl;
    ++status;
  }

  // ---[Parse example string from documentation]---------------------

  std::cout << "[2] Parse example string from documentation ..." << std::endl;
  try {
    /* Text examples to parse */
    examples.clear();
    examples.push_back("@abc def--");
    examples.push_back("aa");
    examples.push_back("ab");
    examples.push_back("ba");
    examples.push_back("aa aab aabbaa aabbaaa");
    examples.push_back("aa aab aabb aaab aaabb");
    /* Parser expression */
    expressions.clear();
    expressions.push_back ("a+|b+");
    expressions.push_back ("b+|a+");
    /* Parse the examples*/
    status += parse_examples (examples, expressions);
  } catch (std::exception &e) {
    std::cerr << "" << e.what() << std::endl;
    ++status;
  }

  // ---[Parse HTML code]----------------------------

  std::cout << "[3] Parse HTML code ..." << std::endl;
  try {
    /* Text examples to parse */
    examples.clear();
    examples.push_back("Use <a href=\"http:/www.google.com\">Google</a> for search.");
    /* Parser expression */
    expressions.clear();
    expressions.push_back ("<a\\s+href=\"([\\-:\\w\\d\\.\\/]+)\">");
    /* Parse the examples*/
    status += parse_examples (examples, expressions);
  } catch (std::exception &e) {
    std::cerr << "" << e.what() << std::endl;
    ++status;
  }

  // ---[Parse Apache log file entry line]----------------------------

  std::cout << "[4] Parse Apache log file entry line ..." << std::endl;
  try {
    /* Text examples to parse */
    examples.clear();
    examples.push_back("ftp://downloads.foo.com/apps/linux/patch.gz");
    /* Parser expression */
    expressions.clear();
    expressions.push_back ("(ftp|http|https):\\/\\/([[:word:]]+\\.)*([[:word:]]*)\\/([[[:word:]][[:digit:]]]+\\/{0,1})+");
    /* Parse the examples*/
    status += parse_examples (examples, expressions);
  } catch (std::exception &e) {
    std::cerr << "" << e.what() << std::endl;
    ++status;
  }

  return status;
}

//_______________________________________________________________________________
//                                                               test_boost_regex

/*!
  \brief Test processing log file entry using boost::regex library
 */
int test_boost_regex (std::string const &logline)
{
  std::cout << "\n[testApacheLogs::test_boost_regex]\n" << std::endl;

  int status = 0;
  boost::cmatch what;

  std::cout << "--> Input string = " << logline << std::endl;

  // if (regex_match(logline.c_str(), what, e)) {
  //   std::cout << "-- Remote host = " << what[1] << std::endl;
  // } else {
  //   std::cout << "--> No match found!" << std::endl;
  // }

  return status;
}

//_______________________________________________________________________________
//                                                              test_boost_spirit

/*!
  \brief Test processing log file entry using boost::spirit library
 */
int test_boost_spirit (std::string const &logline)
{
  int status = 0;

  return status;
}

// ==============================================================================
//
//  Program main routine
//
// ==============================================================================

//! Program main routine
int main (int argc, char **argv)
{
  int status = 0;

  return test_boost_regex ();

  /* Check command line options */
  if (argc>1) {

    std::string filename = argv[1];
    std::string buffer;

    /* Open input file-stream */
    std::ifstream infile (argv[1]);

    /* Check input file stream */
    if (infile.is_open()) {
      std::cout << "--> Start reading data from file " << filename << std::endl;
      while (infile.good()) {
        /* Get line from the input file ... */
        std::getline (infile, buffer);
        /* ... and process it */
        test_boost_regex (buffer);
      }
    } else {
      std::cerr << "ERROR: Failed to open input file." << std::endl;
      ++status;
    }

  } else {
    std::cerr << "[testApacheLogs] Missing name of logfile to process!"
              << std::endl;
    status = -1;
  }

  return status;
}
