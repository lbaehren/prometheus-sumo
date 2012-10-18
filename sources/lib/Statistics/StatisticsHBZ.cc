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

#include "StatisticsHBZ.h"

namespace prometheus {  //  namespace prometheus -- BEGIN

  namespace statistics {  //  namespace statistics -- BEGIN

    // ==========================================================================
    //
    //  Construction
    //
    // ==========================================================================

    /*!
      \param time       -- Time period for which the statistics have been generated.
      \param consortium -- Name of the consortium member.
      \param signum     -- Signum of the institution.
      \param user       -- Name of the user.
      \param customerID -- Customer ID.
    */
    StatisticsHBZ::StatisticsHBZ (std::string const &time,
                                  std::string const &consortium,
                                  std::string const &signum,
                                  std::string const &user,
                                  std::string const &customerID)
    {
      init (time,
            consortium,
            signum,
            user,
            customerID);
    }

    // ==========================================================================
    //
    //  Private methods
    //
    // ==========================================================================

    void StatisticsHBZ::summary (std::ostream &os)
    {
      os << "-- Time period        = " << itsTime       << std::endl;
      os << "-- Consortium member  = " << itsConsortium << std::endl;
      os << "-- Institution signum = " << itsSignum     << std::endl;
    }

    // ========================================================================
    //
    //  Private methods
    //
    // ========================================================================

    /*!
      \param time       -- Time period for which the statistics have been generated.
      \param consortium -- Name of the consortium member.
      \param signum     -- Signum of the institution.
      \param user       -- Name of the user.
      \param customerID -- Customer ID.
    */
    void StatisticsHBZ::init (std::string const &time,
                              std::string const &consortium,
                              std::string const &signum,
                              std::string const &user,
                              std::string const &customerID)
    {
      itsTime       = time;
      itsConsortium = consortium;
      itsSignum     = signum;
      itsUser       = user;
      itsCustomerID = customerID;
    }

  }  //  namespace statistics -- END

}  //  namespace prometheus -- END
