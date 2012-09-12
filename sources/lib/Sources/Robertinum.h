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

#ifndef SOURCES_ROBERTINUM_H
#define SOURCES_ROBERTINUM_H

#include <SourceDump.h>

namespace prometheus {  //  namespace prometheus -- BEGIN

  namespace source {  //  namespace source -- BEGIN

    /*!
      \file Robertinum.h
      \class Robertinum
      \ingroup prometheus
      \ingroup source
      \brief Dump from Robertinum database.
      \author Lars Baehren
    */
    class Robertinum : public SourceDump {

    public:

      // === Construction =======================================================

      //! Argumented constructor
      Robertinum (std::string const &rootNode="database",
                  std::string const &imageNode="row");

      // === Public methods =====================================================

    private:

      //! Initialize internal attributes
      void init () {
        itsAttributes["path"]           = "grossbildnummer";
        itsAttributes["artist"]         = "werkstatt";
        itsAttributes["title"]          = "titel";
        itsAttributes["date"]           = "datierung";
        itsAttributes["genre"]          = "form";
        itsAttributes["location"]       = "standort";
        itsAttributes["discoveryplace"] = "fundort";
        itsAttributes["credits"]        = "bildrecht";
      }

    };  //  class Robertinum -- END

  }   //  namespace source -- END

}  //  namespace prometheus -- END

#endif
