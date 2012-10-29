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

#include "Account.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    // ==========================================================================
    //
    //  Construction
    //
    // ==========================================================================

    Account::Account ()
      : ColumnsFor()
    {
    }

    Account::Account (std::string const &filename)
      : ColumnsFor(filename)
    {
    }

    // ==========================================================================
    //
    //  Parameter access
    //
    // ==========================================================================

    //___________________________________________________________________________
    //                                                                columnNames

    std::set<std::string> Account::columnNames ()
    {
      std::set<std::string> names;
      std::map<std::string, std::vector<std::string> >::iterator it;

      for (it=itsColumns.begin(); it!=itsColumns.end(); ++it) {
	names.insert(it->first);
      }

      return names;
    }

    //___________________________________________________________________________
    //                                                             columnNamesFor

    std::vector<std::string> Account::columnNamesFor (std::string const &name)
    {
      std::vector<std::string> names;
      std::map<std::string, std::vector<std::string> >::iterator it;

      it = itsColumns.find(name);

      if (it!=itsColumns.end()) {
	names = it->second;
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
    void Account::summary (std::ostream &os)
    {
      os << "[Account] Summary of internal parameters"  << std::endl;
      os << "-- Configuration file = " << itsConfigFile     << std::endl;
      os << "-- nof. columns       = " << itsColumns.size() << std::endl;
      os << "-- Column names       = " << columnNames()     << std::endl;
    }

  }   // namespace config -- BEGIN

}   // namespace prometheus -- END
