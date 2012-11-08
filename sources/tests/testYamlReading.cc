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

#include <fstream>
/* YAML support */
#include <yaml-cpp/yaml.h>
/* Project */
#include <Common.h>
#include <ConfigFileInstitution.h>

/*!
  \file testYamlReading.cc
  \brief Test reading in configuration data from \ref yaml files
  \author Lars Baehren
*/

// =============================================================================
//
//  Data stuctures
//
// =============================================================================

/*! Data structure to store a node representing a movie */
struct Movie {
  //! Title of the movie
  std::string title;
  //! Release year of the movie
  unsigned int release;
  //! Director of the movie
  std::string director;
};

// =============================================================================
//
//  Operator overloading
//
// =============================================================================

/*!
  \brief Overloading of the output operator for a node representing a movie.
  \param node  -- Object container for the node.
  \param movie -- Data structure into which the node's contents is being stored.
*/
void operator >> (const YAML::Node& node,
		  Movie& movie)
{
  node["title"]    >> movie.title;
  node["release"]  >> movie.release;
  node["director"] >> movie.director;
}

// =============================================================================
//
//  Tests functions
//
// =============================================================================

//______________________________________________________________________________
//                                                                      readList

/*!
  \brief Read data from list.
  \param filename - Path to the configuration file.
  \return Status of the function; returns non-zero value in case an error was
          encountered.
*/
int readList (std::string const &filename)
{
  std::cout << "\n[YamlReader::readList]\n" << std::endl;

  std::ifstream infile (filename.c_str());

  if (infile.is_open()) {
    std::vector<std::string> dataVector;
    std::set<std::string> dataSet;
    YAML::Node node;
    YAML::Parser parser(infile);
    // Parse data into node
    parser.GetNextDocument(node);
    /* Parse the contents of the node */
    std::cout << "--> Node data" << std::endl;
    for (YAML::Iterator it=node.begin();it!=node.end();++it) {
      std::string data;
      *it >> data;
      dataVector.push_back(data);
      dataSet.insert(data);
      std::cout << "- " << data << std::endl;
    }
    /* Display the data read from the file*/
    std::cout << "--> std::vector<std::string>\n" << dataVector << std::endl;
    std::cout << "--> std::set<std::string>\n"    << dataSet    << std::endl;
  } else {
    std::cerr << "--> Failed to open file " << filename << std::endl;
    return 1;
  }

  /* Close the input stream */
  infile.close();

  return 0;
}

//______________________________________________________________________________
//                                                          readAssociativeArray

/*!
  \brief Read data from asociative array.
  \param filename - Path to the configuration file.
  \return Status of the function; returns non-zero value in case an error was
          encountered.
*/
int readAssociativeArray (std::string const &filename)
{
  std::cout << "\n[YamlReader::readAssociativeArray]\n" << std::endl;

  std::ifstream infile (filename.c_str());

  if (infile.is_open()) {
    YAML::Node node;
    YAML::Parser parser(infile);
    // Parse data into node
    parser.GetNextDocument(node);
    std::cout << "--> nof. nodes = " << node.size() << std::endl;
    /* Parse the contents of the node */
    for (YAML::Iterator it=node.begin();it!=node.end();++it) {
      Movie movie;
      *it >> movie;
      /* Dispay contents of the node */
      std::cout << "- " << movie.title << " (" << movie.release << ")"
		<< "\t- " << movie.director
		<< std::endl;
    }
  } else {
    std::cerr << "--> Failed to open file " << filename << std::endl;
    return 1;
  }

  /* Close the input stream */
  infile.close();

  return 0;
}

//______________________________________________________________________________
//                                                        readScalarsToSequences

/*!
  \brief Read data from mapping of scalars to sequences.
  \param filename - Path to the configuration file.
  \return Status of the function; returns non-zero value in case an error was
          encountered.
*/
int readScalarsToSequences (std::string const &filename)
{
  std::cout << "\n[YamlReader::readScalarsToSequences]\n" << std::endl;

  std::ifstream infile (filename.c_str());

  if (infile.is_open()) {
    YAML::Node node;
    YAML::Parser parser(infile);
    // Parse data into node
    parser.GetNextDocument(node);
    std::cout << "--> nof. nodes = " << node.size() << std::endl;
    /* Parse the contents of the node */
    for (YAML::Iterator it=node.begin();it!=node.end();++it) {
      /* Get the key of the node */
      std::string director;
      it.first()>> director;
      std::cout << "  " << director << ":" << std::endl;
      for (size_t n=0; n<it.second().size(); ++n) {
        std::string movie;
        it.second()[n] >> movie;
        std::cout << "    - " << movie << std::endl;
      }
    }
  } else {
    std::cerr << "--> Failed to open file " << filename << std::endl;
    return 1;
  }

  /* Close the input stream */
  infile.close();

  return 0;
}

// =============================================================================
//
//  Main program function
//
// =============================================================================

/*! Program main function */
int main (int argc,
	  char *argv[])
{
  int retval = 0;
  std::string filename;
  std::string pathTestData;

  /* Check parameter provided from the command line */
  if ( argc>1 ) {
    pathTestData = std::string(argv[1]);
  } else {
    std::cerr << "[ERROR] No path to directory with test data!" << std::endl;
    return 1;
  }

  /*
   *  Basic parser testing
   */

  filename = pathTestData + "/yaml_List.yml";
  retval +=  readList(filename);

  filename = pathTestData + "/yaml_AssociativeArray.yml";
  retval +=  readAssociativeArray(filename);

  filename = pathTestData + "/yaml_ScalarsToSequences.yml";
  retval +=  readScalarsToSequences(filename);

  return retval;
}
