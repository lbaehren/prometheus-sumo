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

#ifndef CONFIG_REPOSITORIES_H
#define CONFIG_REPOSITORIES_H

#include "ConfigFileBase.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    /*!
      \file Repositories.h
      \class Repositories
      \ingroup prometheus
      \ingroup config
      \brief Configuration settings for required software repositories
      \test testConfigRepositories.cc

      \author Lars Baehren
      \date 2012-11-13

      This class provides an adapter to read configuration data on list of
      repositories hosting source code or documentation.
    */
    class Repositories : public ConfigFileBase {

      //! Parameters for the repository node of the configuration file
      struct RepositoryParameters {
        //! Name of the repository
        std::string name;
        //! Description of the repository
        std::string description;
        //! Type of the repository (Git, Subversion, Mercurial, etc.)
        std::string type;
        //! URL for repository's project page
        std::string url;
      };

      //! List of repositories for which parameters are kept
      std::vector<RepositoryParameters> itsRepositoryList;

      //! Store the data from an individual node
      bool storeNode (YAML::Iterator const &it);

    public:

      // === Construction =======================================================

      //! Default constructor
      Repositories ();

      //! Argumented constructor
      Repositories (std::string const &filename);

      // === Parameter access ===================================================

      //! Get the number of repositories for which parameters are kept
      inline size_t size () {
        return itsRepositoryList.size();
      }

      //! Get the name of the repositories
      std::set<std::string> names ();

      //! Get description of the repositories
      std::map<std::string,std::string> descriptions ();

      //! Get type information for the repositories
      std::map<std::string,std::string> types ();

      //! Get URL for repository's project page
      std::map<std::string,std::string> urls ();

      // === Public functions ===================================================

      //! Provide a summary of the object's internal parameters and status
      inline void summary () {
        summary (std::cout);
      }

      //! Provide a summary of the object's internal parameters and status
      void summary (std::ostream &os);

    };

  }   // namespace config -- BEGIN

}   // namespace prometheus -- END

#endif
