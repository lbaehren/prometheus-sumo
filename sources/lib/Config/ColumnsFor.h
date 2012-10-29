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

#ifndef CONFIG_COLUMNS_FOR_H
#define CONFIG_COLUMNS_FOR_H

#include "ConfigFileBase.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    /*!
      \file ColumnsFor.h
      \class ColumnsFor
      \ingroup prometheus
      \ingroup config
      \brief Configuration settings for columns for a given model
      \author Lars Baehren
      \date 2012-10-25
    */
    class ColumnsFor : public ConfigFileBase {

    protected:

      //! Parameters available for list display, search and user
      std::map<std::string, std::vector<std::string> > itsColumns;

      //! Store the data from an individual node
      bool storeNode (YAML::Iterator const &it);

    public:

      // === Construction =======================================================

      //! Default constructor
      ColumnsFor ();

      //! Argumented constructor
      ColumnsFor (std::string const &filename);

      // === Parameter access ===================================================

      //! Get the number of parameter columns
      inline size_t nofColumns () {
        return itsColumns.size();
      }

      //! Get the names of the paramer columns
      std::set<std::string> columnNames ();

      //! Get the column names for a given \c name
      std::vector<std::string> columnNamesFor (std::string const &name);

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
