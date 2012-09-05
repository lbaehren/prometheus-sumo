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

#include <SourceDump.h>

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  namespace source {  //  namespace source -- BEGIN
    
    /*!
      \file TheolEik.h
      \class TheolEik
      \ingroup prometheus
      \ingroup source
      \brief Dump from TheolEik database.
      \author Lars Baehren
    */
    class TheolEik : public SourceDump {

    public:

      // === Public data =======================================================

      /*!
        \brief Image attributes
	
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
      struct Attributes {
        bool missingAttributes;
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

      // === Static methods ====================================================
      
    /*!
      \param infile  -- Input stream connected to the XML dump for the
                     collection.
      \retval items  -- Array with the items listed in the database dump.
      \return status -- Indicator for status of internal operation: returns
                     \c -1 in case there was an error reading from the input stream,
                     \c N for the number of incomplete datasets (i.e. missing
                     attributes) and \c 0 otherwise.
    */
    static int readXML (std::istream & infile,
                        std::vector<TheolEik::Attributes> &items);
    
    };
    
  };  //  namespace source -- END

}  //  namespace prometheus -- END

#endif
