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

#include "Institution.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    // ==========================================================================
    //
    //  Construction
    //
    // ==========================================================================

    Institution::Institution ()
      : ConfigFileBase()
    {
    }

    Institution::Institution (std::string const &filename)
      : ConfigFileBase(filename)
    {
    }

    // ==========================================================================
    //
    //  Parameter access
    //
    // ==========================================================================

    //___________________________________________________________________________
    //                                                                columnNames

    std::set<std::string> Institution::columnNames ()
    {
      std::set<std::string> names;
      std::map<std::string, std::vector<std::string> >::iterator it;

      for (it=itsColumns.begin(); it!=itsColumns.end(); ++it) {
	names.insert(it->first);
      }

      return names;
    }

    // ==========================================================================
    //
    //  Public functions
    //
    // ==========================================================================

    //___________________________________________________________________________
    //                                                                    summary

    /*!
      \param os -- Output stream to which the summary will be written.
    */
    void Institution::summary (std::ostream &os)
    {
      os << "[Institution] Summary of internal parameters"  << std::endl;
      os << "-- Configuration file = " << itsConfigFile     << std::endl;
      os << "-- nof. columns       = " << itsColumns.size() << std::endl;
      os << "-- Column names       = " << columnNames()     << std::endl;
    }

    // ==========================================================================
    //
    //  Private methods
    //
    // ==========================================================================

    bool Institution::storeNode (YAML::Iterator const &it)
    {
      bool status = true;
      std::string sequenceName;
      std::vector<std::string> sequenceValues;
      std::string buffer;
      
      try {
	/* Acces the node holding the actual configuration data... */
	const YAML::Node & node = it.second();
	/* ... and iterate through the node attached to it */
	for (YAML::Iterator iter=node.begin();iter!=node.end();++iter) {
	  /* Store the name of the sequence ... */
	  iter.first() >> sequenceName;
	  /* ... and parse the parameter values in the list */
	  for (unsigned int n=0; n<iter.second().size(); ++n) {
	    iter.second()[n] >> buffer;
	    sequenceValues.push_back(buffer);
	  }
	  // Store the extracted data
	  itsColumns[sequenceName] = sequenceValues;
	  sequenceValues.clear();
	}
	
      } catch (std::exception &e) {
        std::cout << "[Gems::storeNode] ERROR : " << e.what() << std::endl;
        status = false;
      }

      return status;
    }

  }   // namespace config -- BEGIN

}   // namespace prometheus -- END
