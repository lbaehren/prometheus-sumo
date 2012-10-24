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

#include "TrustedProxies.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    // ==========================================================================
    //
    //  Construction
    //
    // ==========================================================================

    TrustedProxies::TrustedProxies ()
      : ConfigFileBase ()
    {
    }

    TrustedProxies::TrustedProxies (std::string const &filename)
      : ConfigFileBase (filename)
    {
    }

    // ==========================================================================
    //
    //  Parameter access
    //
    // ==========================================================================

    //___________________________________________________________________________
    //                                                                  storeNode

    bool TrustedProxies::storeNode (YAML::Iterator const &it)
    {
      bool status = true;
      std::string buffer;

      try {
	/* Extract parameters from node ... */
	*it >> buffer;
	/* .. and store them internally */
	itsProxies.push_back(buffer);
      } catch (std::exception &e) {
	std::cout << "[TrustedProxies::storeNode] ERROR : " << e.what() << std::endl;
	status = false;
      }

      return status;
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
    void TrustedProxies::summary (std::ostream &os)
    {
      os << "[TrustedProxies] Summary of internal parameters" << std::endl;
      os << "-- Configuration file = " << itsConfigFile       << std::endl;
      os << "-- nof. proxies       = " << itsProxies.size() << std::endl;
    }

  }   // namespace config -- BEGIN

}   // namespace prometheus -- END

