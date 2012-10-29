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

#include <iomanip>
#include <Config/Source.h>

/*!
  \file testConfigSource.cc
  \ingroup prometheus
  \ingroup tests
  \brief A collection of tests for the prometheus::config::Source class
  \author Lars Baehren
*/

// === Test procedures ==========================================================

int test_direct_read (std::string const &filename)
{
  std::cout << "\n[testSource::test_direct_read]\n" << std::endl;

  int status      = 0;
  size_t nofNodes = 0;
  std::map<std::string,std::vector<std::string> > configNodes;
  std::map<std::string,std::vector<std::string> >::iterator configIter;

  // Open the input file
  std::ifstream infile (filename.c_str());

  if (infile.is_open()) {
    // Local variables
    std::string buffer;
    std::vector<std::string> bufferSeq;
    YAML::Node node;
    YAML::Parser parser (infile);
    /* Load the data file into the parser */
    parser.GetNextDocument(node);
    // Node characteristics
    nofNodes = node.size();

    for (YAML::Iterator it=node.begin();it!=node.end();++it) {

      it.first() >> buffer;

      if (it.second().Type() == YAML::NodeType::Scalar) {
        bufferSeq.resize(1);
        it.second() >> bufferSeq[0];
        // Store contents of node
        configNodes[buffer] = bufferSeq;
      } else if (it.second().Type() == YAML::NodeType::Sequence) {
        bufferSeq.resize(it.second().size());
        for (unsigned int n=0; n<it.second().size(); ++n) {
          it.second()[n] >> bufferSeq[n];;
        }
        // Store contents of node
        configNodes[buffer] = bufferSeq;
      }
    }
  } else {
    std::cerr << "Failed to open file " << filename << std::endl;
  }

  std::cout << "-- Finished parsing input file - " << nofNodes << " nodes found." << std::endl;

  for (configIter=configNodes.begin();configIter!=configNodes.end(); ++configIter) {
    std::cout << "-->  " << configIter->first << std::endl;
  }

  return 0;
}

//_______________________________________________________________________________
//                                                              test_constructors

/*!
  \brief Test constructors for a new object
  \param filename -- Name of the configuration file.
  \return status  -- Returns non-zero value in case an error was encountered.
*/
int test_constructors (std::string const &filename="source.yml")
{
  std::cout << "\n[testSource::test_constructors]\n" << std::endl;

  int status = 0;

  std::cout << "[1] Testing Source() ..." << std::endl;
  try {
    prometheus::config::Source inst;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing Source(std::string) ..." << std::endl;
  try {
    prometheus::config::Source inst (filename);
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  return status;
}

//_______________________________________________________________________________
//                                                              test_constructors

/*!
  \brief Test reading list of Ruby gems from configuration file
*/
int test_read_config (std::string const &filename)
{
  std::cout << "\n[testSource::test_read_config]\n" << std::endl;

  int status = 0;
  prometheus::config::Source inst;
  std::set<std::string> columnNames;

  std::cout << "[1] Testing Source::readConfig(std::string) ..." << std::endl;
  try {
    inst.readConfig(filename);
    inst.summary();
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing Source::columnNames() ..." << std::endl;
  try {
    columnNames = inst.columnNames();
    std::cout << "--> Column names = " << columnNames << std::endl;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[3] Testing Source::columnNamesFor(std::string) ..." << std::endl;
  try {
    std::set<std::string>::iterator it;

    for (it=columnNames.begin(); it!=columnNames.end(); ++it) {
      std::cout << "--> " << (*it) << std::endl;
      std::cout << "\t" << inst.columnNamesFor( (*it) ) << std::endl;
    }
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  return status;
}

// === Program main function ====================================================

//! Program main function
int main (int argc, char **argv)
{
  int status = 0;

  if (argc >1) {
    status += test_direct_read (argv[1]);
    status += test_constructors (argv[1]);
    status += test_read_config (argv[1]);
  } else {
    status += test_constructors ();
  }

  return status;
}
