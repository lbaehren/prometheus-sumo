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
#include <fstream>
/* Project */
#include <Common.h>
#include <ConfigFileInstitution.h>

/*!
  \file testYAML.cc
  \ingroup prometheus
  \ingroup test
  \brief Test reading in configuration data from \ref yaml files
  \author Lars Baehren
*/

// =============================================================================
//
//  Helper functions
//
// =============================================================================

void showPackageList (std::map<std::string,std::string> &attributes)
{
  std::string name;
  std::string source;
  std::string version;
  std::map<std::string,std::string>::iterator it;

  // Extract the name of the package
  it=attributes.find("name");
  if (it==attributes.end()) {
    name = "~";
  } else {
    name = it->second;
  }
  
  // Extract the source of the package
  it=attributes.find("source");
  if (it==attributes.end()) {
    source = "~";
  } else {
    source = it->second;
  }
  
  // Extract the version of the package
  it=attributes.find("version");
  if (it==attributes.end()) {
    version = "~";
  } else {
    version = it->second;
  }
  
  std::cout << std::setw(25) << name
            << "  ::"   << std::setw(12) << version
	    << "  ::  " << source
	    << std::endl;
}

// =============================================================================
//
//  Tests functions
//
// =============================================================================

//_______________________________________________________________________________
//                                                                    hello_world

//! Emit a simple message
int hello_world ()
{
  std::cout << "\n[tEmitting::hello_world]\n" << std::endl;

  YAML::Emitter out;
  out << "Hello, World!";

  std::cout << "Here's the output YAML:\n" << out.c_str() << std::endl;

  return 0;
}

//_______________________________________________________________________________
//                                                                      emit_list

//! Emit a simple list of elements
int emit_list ()
{
  std::cout << "\n[tEmitting::emit_list]\n" << std::endl;

  YAML::Emitter out;

  /* Assemble the sequence */
  out << YAML::BeginSeq;
  out << "eggs";
  out << "bread";
  out << "milk";
  out << YAML::EndSeq;

  /* Write out the sequence */
  std::cout << out.c_str() << std::endl;

  return 0;
}

//_______________________________________________________________________________
//                                                                       emit_map

//! Emit a simple map of elements
int emit_map ()
{
  std::cout << "\n[tEmitting::emit_map]\n" << std::endl;

  YAML::Emitter out;

  /* Assemble the map */
  out << YAML::BeginMap;
  out << YAML::Key   << "name";
  out << YAML::Value << "Barack Obama";
  out << YAML::Key   << "children";
  out << YAML::Value << YAML::BeginSeq << "Sasha" << "Malia" << YAML::EndSeq;
  out << YAML::EndMap;

  /* Write the map to standard output */
  std::cout << out.c_str() << std::endl;

  return 0;
}

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

  struct Movie {
    std::string title;
    unsigned int release;
    std::string director;
  };

  std::ifstream infile (filename.c_str());

  if (infile.is_open()) {
    YAML::Node node;
    YAML::Parser parser(infile);
    size_t counter (0);
    // Parse data into node
    parser.GetNextDocument(node);
    std::cout << "--> nof. nodes = " << node.size() << std::endl;
    /* Parse the contents of the node */
    for (YAML::Iterator it=node.begin();it!=node.end();++it) {
      Movie movie;
      // Extract node data ...
      (*it)["title"]    >> movie.title;
      (*it)["release"]  >> movie.release;
      (*it)["director"] >> movie.director;
      // ... and display them
      std::cout << " ["<< counter << "] " << movie.director
		<< " (" << movie.release << ") "
		<< movie.title
		<< std::endl;
      // increment counter
      ++counter;
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

//______________________________________________________________________________
//                                                               readPackageList

/*!
  \brief Read list of software packages from configuration data file
  \param filename - Path to the configuration file.
  \return Status of the function; returns non-zero value in case an error was
          encountered.
*/
int readPackageList (std::string const &filename)
{
  std::cout << "\n[YamlReader::readPackageList]\n" << std::endl;

  std::map<std::string,std::string> attributes;
  std::map<std::string,std::string>::iterator itAttr;
  attributes["name"]        = "";
  attributes["source"]      = "";
  attributes["version"]     = "";
  attributes["homepage"]    = "";
  attributes["description"] = "";

  std::ifstream infile (filename.c_str());

  if (infile.is_open()) {
    YAML::Node node;
    YAML::Parser parser(infile);
    std::string tmpKey;
    std::string tmpVal;
    // Parse data into node
    parser.GetNextDocument(node);
    std::cout << "--> nof. nodes = " << node.size() << std::endl;
    /* Parse the contents of the node */
    for (YAML::Iterator it=node.begin();it!=node.end();++it) {

      for (itAttr=attributes.begin();itAttr!=attributes.end();++itAttr) {
	/* Extract node data */
	if(const YAML::Node *pName = it->FindValue(itAttr->first)) {
	  *pName >> tmpVal;
	} else {
	  tmpVal = "~";
	}
	/* Store data extracted from node */
	attributes[itAttr->first] = tmpVal;
      }

      showPackageList (attributes);

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
int main (int argc, char *argv[])
{
  int retval = 0;

  /* Check parameter provided from the command line */
  if ( argc>2 ) {
    // Extract the path to the input test file
    std::string selection = std::string(argv[1]);
    std::string filename  = std::string(argv[2]);
    // show command line options
    std::cout << "-- Selection = " << selection << std::endl;
    std::cout << "-- Filename  = " << filename  << std::endl;
    // Extract the test case selection
    if (selection == "--list") {
      retval +=  readList(filename);
    } else if (selection == "--array") {
      retval +=  readAssociativeArray(filename);
    } else if (selection == "--sequence") {
      retval +=  readScalarsToSequences(filename);
    } else if (selection == "--packages") {
      retval +=  readPackageList(filename);
    } else {
      retval += hello_world();
      retval += emit_list();
      retval += emit_map();
    }
  } else {
    std::cerr << "[ERROR] No path to directory with test data!" << std::endl;
    return 1;
  }

  return retval;
}
