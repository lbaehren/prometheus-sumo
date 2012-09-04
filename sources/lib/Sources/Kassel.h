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

#ifndef SOURCES_KASSEL_H
#define SOURCES_KASSEL_H

/*!
  \file Kassel.h
  \ingroup prometheus
  \brief Dump from Kassel database.
  \author Lars Baehren
*/

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  /*!
    \brief Item in the collection Kassel
    
    \verbatim
    <row>
    <bild_nr>G8001</bild_nr>
    <datierung>1783-1786</datierung>
    <gattung>Gartenarchitektur</gattung>
    <inventar_nr>GS 6258</inventar_nr>
    <kuenstler>Jussow, Heinrich Christoph (Zeichner)</kuenstler>
    <objekt>Tempel</objekt>
    <objekt_id>11846</objekt_id>
    <titel>Entwurf zu einem Gartentempel, Aufriß</titel>
    </row>
    \endverbatim
  */
  struct ItemKassel {
    //! bild_nr
    std::string image;
    //! datierung
    std::string date;
    //! gattung
    std::string category;
    //! inventar_nr
    std::string inventary;
    //! kuenstler
    std::string artist;
    //! objekt
    std::string object;
    //! objekt_id
    std::string objectID;
    //! titel
    std::string title;
  };
  
  
}  //  namespace prometheus -- END

#endif
