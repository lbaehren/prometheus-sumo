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

#include "ConfigFileBase.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    // ==========================================================================
    //
    //  Construction
    //
    // ==========================================================================

    ConfigFileBase::ConfigFileBase ()
    {
      itsConfigFile = "";
    }

    /*!
      \param filename -- Name of the configuration file from which to read the
                         data.
    */
    ConfigFileBase::ConfigFileBase (std::string const &filename)
    {
      itsConfigFile = filename;
    }

    // ==========================================================================
    //
    //  Public functions
    //
    // ==========================================================================

    //___________________________________________________________________________
    //                                                                 readConfig

    /*!
      \param filename -- Name of the configuration file from which to read the
                         data.
    */
    bool ConfigFileBase::readConfig (std::string const &filename)
    {
      bool status = true;
      std::ifstream infile (filename.c_str());

      if (infile.is_open()) {
        /* Book-keeping: store the filename */
        itsConfigFile = filename;
        /* Set up the parser */
        YAML::Node node;
        YAML::Parser parser (infile);
        /* Load the data file into the parser */
        parser.GetNextDocument(node);
        /* Parse the contents of the configuration file */
        for (YAML::Iterator it=node.begin();it!=node.end();++it) {
          storeNode (it);
        }
      } else {
        std::cerr << "[RubyGems::readConfig] Failed to open file "
                  << filename
                  << std::endl;
        status = false;
      }

      return status;
    }

    //___________________________________________________________________________
    //                                                                    summary

    /*!
      \param os -- Output stream to which the summary will be written.
    */
    void ConfigFileBase::summary (std::ostream &os)
    {
      os << "[ConfigFileBase] Summary of internal parameters" << std::endl;
      os << "-- Configuration file = " << itsConfigFile << std::endl;
    }

  }   // namespace config -- BEGIN

}   // namespace prometheus -- END
