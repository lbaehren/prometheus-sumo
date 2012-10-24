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

#ifndef CONFIG_TRUSTED_PROXIES_H
#define CONFIG_TRUSTED_PROXIES_H

#include "ConfigFileBase.h"

// ==============================================================================
//
//  Class definition
//
// ==============================================================================

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    /*!
      \file TrustedProxies.h
      \class TrustedProxies
      \ingroup prometheus
      \ingroup config
      \brief Configuration settings user roles inside the application
      \test testConfigTrustedProxies.cc

      \author Lars Baehren
      \date 2012-10-23

      This class provides an adapter to read configuration data on the trusted
      proxies:
      \include trusted_proxies.yml
    */
    class TrustedProxies : public ConfigFileBase {

    private:

      //! List of trusted proxies
      std::vector<std::string> itsProxies;

      //! Store the data from an individual node
      bool storeNode (YAML::Iterator const &it);

    public:

      // === Construction =======================================================

      //! Default constructor
      TrustedProxies ();

      //! Argumented constructor
      TrustedProxies (std::string const &filename);

      // === Parameter access ===================================================

      //! Get the number of gems for which parameters are kept
      inline size_t nofProxies () {
        return itsProxies.size();
      }

      //! Get the list of trusted proxies
      inline std::vector<std::string> proxies () {
       return itsProxies;
      }

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
