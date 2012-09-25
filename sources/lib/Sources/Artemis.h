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

#ifndef SOURCES_ARTEMIS_H
#define SOURCES_ARTEMIS_H

#include <SourceDump.h>

namespace prometheus {  //  namespace prometheus -- BEGIN

  namespace source {  //  namespace source -- BEGIN

    /*!
      \file Artemis.h
      \class Artemis
      \ingroup prometheus
      \ingroup source
      \brief Dump from Artemis database.
      \author Lars Baehren

      Structure of the database dump:
      \verbatim
      <?xml version="1.0" encoding="UTF-8"?>
        <datenbank standort="KHI München" inhalt="Gesamtausgabe der freigegebenen Datensätze">
          <datensatz nr="M000001">
            <gattung>Tafelmalerei</gattung>
            <bildgattung>Historienbild</bildgattung>
            <kuenstler>Rubens, Pieter Paul</kuenstler>
            <kuenstler>Snyders, Frans</kuenstler>
            <titel>Gefesselter Prometheus</titel>
            <datierung>1611-1612</datierung>
            <iconclass>91E4611</iconclass>
            <groesse>243.5 x 209.5 cm</groesse>
            <farbe>Öl</farbe>
            <traeger>Leinwand</traeger>
            <standort>Philadelphia (Pennsylvania)</standort>
            <einrichtung>Philadelphia Museum of Art</einrichtung>
          </datensatz>
      \endverbatim
    */
    class Artemis : public SourceDump {

    public:

      // === Construction ======================================================

      //! Argumented constructor
      Artemis (std::string const &rootNode="datenbank",
              std::string const &imageNode="datensatz");

    private:

      //! Initialize internal attributes
      void init () {
        itsAttributes["artist"]   = "kuenstler";
        itsAttributes["title"]    = "titel";
        itsAttributes["keyword"]  = "bildgattung";
        itsAttributes["location"] = "standort";
        itsAttributes["genre"]    = "gattung";
        itsAttributes["date"]     = "datierung";
        itsAttributes["comment"]  = "bemerkung";
      }

    };   //   class Artemis -- END

  }   //   namespace source -- END

}   //   namespace prometheus -- END

#endif
