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

#ifndef CONFIG_FILE_BASE_H
#define CONFIG_FILE_BASE_H

/* Standard header files */
#include <fstream>
/* Project header files */
#include <Common.h>

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    /*!
      \file ConfigFileBase.h
      \class ConfigFileBase
      \ingroup prometheus
      \ingroup config
      \brief Base class for dealing with (\ref yaml) cnofiguration files
      \author Lars Baehren
      \date 2012-10-22

      This class defines the basic interface for accessing configuration settings
      stored in (primarily) a \ref yaml data file. The main functions offered are:

      \li ConfigFileBase::readConfig - This handles the basic I/O on the input
      data file, such as opening an input file-stream and initializing the parser.

      \li ConfigFileBase::storeNode is defined as virtual function only and hence
      must be implemented by any derived class. This function will take the pointer
      to an extracted YAML data node and store the information contained therein.
    */
    class ConfigFileBase {

    protected:

      //! Name of the configuration file
      std::string itsConfigFile;

      //! Store the data from an individual node
      virtual bool storeNode (YAML::Iterator const &it) = 0;

    public:

      // === Construction =======================================================

      //! Default constructor
      ConfigFileBase ();

      //! Argumented constructor
      ConfigFileBase (std::string const &filename);

      // == Parameter access ====================================================

      //! Get the name of the configuration file
      inline std::string configFile () {
        return itsConfigFile;
      }

      // === Public functions ===================================================

      //! Read in data from configuration files
      virtual bool readConfig (std::string const &filename);

      //! Provide a summary of the object's internal parameters and status
      inline void summary () {
        summary (std::cout);
      }

      //! Provide a summary of the object's internal parameters and status
      virtual void summary (std::ostream &os);

    };

  }   // namespace config -- BEGIN

}   // namespace prometheus -- END

#endif
