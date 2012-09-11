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

#ifndef SOURCES_BEESKOW_H
#define SOURCES_BEESKOW_H

#include <SourceDump.h>

using prometheus::SourceDump;

namespace prometheus {  //  namespace prometheus -- BEGIN

  namespace source {

    /*!
      \file Beeskow.h
      \class Beeskow
      \ingroup prometheus
      \ingroup source
      \brief Dump from Beeskow database.
      \author Lars Baehren
    */
    class Beeskow : public SourceDump {

    public:

      // === Public data ========================================================

      /*!
        \brief Image attributes

        \code
        <?xml version="1.0" encoding="iso-8859-1" ?>
          <root>
            <row>
              <Höhe>97</Höhe>
              <Material>Öl auf Leinwand</Material>
              <KünstlerIn>Hegewald, Michael</KünstlerIn>
              <Gattung>Malerei</Gattung>
              <Ob_f41>284</Ob_f41>
              <Datierung>1989</Datierung>
              <Einheit>cm</Einheit>
              <Breite>138</Breite>
              <Titel>Berlin</Titel>
              <Standort>Kunstarchiv Beeskow</Standort>
            </row>
      \endcode
      */
      struct Attributes {
	bool missingAttributes;
        //! Height of the item, "Höhe"
        std::string height;
        //! Material used in the item, "Material"
        std::string material;
        //! Artist for the item, "KünstlerIn"
        std::string artist;
        //! Category for the item, "Gattung"
        std::string category;
        //! Object code, "Ob_f41"
        unsigned int object;
        //! (Creation) Date for the item, "Datierung"
        std::string date;
        //! Units in which the dimensions of the item are given, "Einheit"
        std::string units;
        //! Width of the item, "Breite"
        std::string width;
        //! Title of the item, "Titel"
        std::string title;
        //! Location of the item, "Standort"
        std::string location;
      };

      // === Construction =======================================================

      //! Argumented constructor
      Beeskow (std::string const &rootNode="root",
	       std::string const &imageNode="row");

      // === Public methods =====================================================

      //! Read data from XML dump of database
      int readXML (std::istream & infile,
                   std::vector<Beeskow::Attributes> &items);

      // === Private methods ====================================================

      void init ();

    };

  }   //  namespace source -- END

}  //  namespace prometheus -- END

#endif
