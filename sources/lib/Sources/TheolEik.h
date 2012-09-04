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

#ifndef SOURCES_THEOLEIK_H
#define SOURCES_THEOLEIK_H

/*!
  \file TheolEik.h
  \ingroup prometheus
  \author Lars Baehren
*/

namespace prometheus {  //  namespace prometheus -- BEGIN

/*!
  \brief Item in the collection theoleik.xml
  
  \code
  <ROW MODID="0" RECORDID="12640214">
    <bildreferenz>1000005.jpg</bildreferenz>
    <abbildungsnachweis>Marguerat, D., Das enfant terrible des Christentums, in: Paulus. Ein unbequemer Apostel. Welt und Umwelt der Bibel 20 (Stuttgart 2001) 4</abbildungsnachweis>
    <copyright></copyright>
    <freigabe>Prometheus</freigabe>
    <standort>Vatikan, Vatikanische Museen</standort>
    <titel>Gemme: Paulus. Ausschnitt: Paulus</titel>
    <herkunft>Rom (I), Grabstätte des Asellus</herkunft>
    <datierung>um 313</datierung>
    <kuenstlerin></kuenstlerin>
    <material></material>
    <gattung></gattung>
    <schlagwort></schlagwort>
    <masse></masse>
    <zusatz></zusatz>
  </ROW>
  \endcode
*/
  struct ItemTheolEik {
    //! bildreferenz
    std::string image;
    //! abbildungsnachweis
    std::string reference;
    //! copyright
    std::string copyright;
    //! freigabe
    std::string license;
    //! standort
    std::string location;
    //! titel
    std::string title;
    //! herkunft
    std::string origin;
    //! datierung
    std::string date;
    //! kuenstlerin
    std::string artist;
    //! material
    std::string material;
    //! gattung
    std::string category;
    //! schlagwort
    std::string keyword;
    //! masse
    std::string mass;
    //! zusatz
    std::string annex;
  };
  
  
}  //  namespace prometheus -- END

#endif
