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

#ifndef SOURCES_PPO_H
#define SOURCES_PPO_H

#include <SourceDump.h>

namespace prometheus {  //  namespace prometheus -- BEGIN

  namespace source {  //  namespace source -- BEGIN

    /*!
      \file PPO.h
      \class PPO
      \ingroup prometheus
      \ingroup source
      \brief Dump from Pictura Paedagogica Online (PPO) database.
      \test testSourcesPPO.cc
      \author Lars Baehren
    */
    class PPO : public SourceDump {

    public:

      // === Construction ======================================================

      //! Argumented constructor
      PPO (std::string const &rootNode="ppo",
           std::string const &imageNode="row");

      // === Public methods ====================================================

      //! Extract source IDs from input file
      std::vector<std::string> sourceIDs (std::string const &filename,
                                          std::string const &match);

    private:

      //! Initialize internal attributes
      void init () {
        itsAttributes["artist"]   = "kuenstler";
        itsAttributes["title"]    = "titel";
        itsAttributes["keyword"]  = "epochensw";
        itsAttributes["location"] = "Pictura Paedagogica Online";
        itsAttributes["genre"]    = "gattung";
        itsAttributes["date"]     = "datierung";
      }

    };   //   class PPO -- END

  }   //   namespace source -- END

}   //   namespace prometheus -- END

#endif
