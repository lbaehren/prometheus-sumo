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

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  namespace source {
    
    /*!
      \class Beeskow
      \ingroup prometheus
      \ingroup source
      \brief Dump from Beeskow database.
      \author Lars Baehren
    */
    
    class Beeskow {
      
    public:
      
      /*!
	\brief Image attributes
	
	\code
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
      
    };
    
  
  }   //  namespace source -- END
  
}  //  namespace prometheus -- END

#endif
