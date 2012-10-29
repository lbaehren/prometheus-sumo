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

#ifndef CONFIG_SOURCE_H
#define CONFIG_SOURCE_H

#include "ColumnsFor.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    /*!
      \file Source.h
      \class Source
      \ingroup prometheus
      \ingroup config
      \brief Configuration settings for an source
      \test testConfigSource.cc
      \author Lars Baehren
      \date 2012-10-29

      This class provides an adapter to read configuration data for a source
      inside the \ref pandora web application.
      \include source.yml

    */
    class Source : public ColumnsFor {

      //! Kinds of databases
      std::set<std::string> itsKinds;

    public:

      // === Construction =======================================================

      //! Default constructor
      Source ();

      //! Argumented constructor
      Source (std::string const &filename);

      // === Parameter access ===================================================

      //! Get the kinds of databases
      inline std::set<std::string> kinds () {
	return itsKinds;
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
