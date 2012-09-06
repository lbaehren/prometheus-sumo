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
      
      /*!
	\brief Image attributes
	
	\code
	<?xml version="1.0" encoding="iso-8859-1"?>
          <database>
            <row>
              <werkstatt></werkstatt>
              <titel>Alabastron, korinthisch, Sirene</titel>
              <standort>Halle/Saale ROBERTINUM, Arch<E4>ologisches Museum der Universit<E4>t Halle</standort>
              <fundort>Athen</fundort>
              <datierung>4. Viertel 7. Jahrhundert v. Chr.</datierung>
              <bildrecht>Foto ROBERTINUM</bildrecht>
              <grossbildnummer>B070a.jpg</grossbildnummer>
              <kleinbildnummer>C070a.jpg</kleinbildnummer>
              <form>Alabastron</form>
              <darstellung>Sirene, Kopf nach links, weitgespreizte Fl<FC>gel</darstellung>
              <gestaltung>auf dem M<FC>ndungsteller ein Blattkranz, an der Au<DF>enseite Punktreihe, auf dem Hals ein Blattkranz, auf der R<FC>ckseite Reste von Klecksrosetten, am Boden eine Blattrosette</gestaltung>
</row>
	\endcode
      */
      struct Attributes {
	bool missingAttributes;
	//! Path to the image, "grossbildnummer"
	std::string path;
	//! Artist for the image, "werkstatt";
	std::string artist;
	//! Title of the image, "titel"
	std::string title;
	//! (Creation) Date of the image, "datierung"
	std::string date;
	std::string genre;          // "form";
	//! Location of the image, "standort"
	std::string location;
	std::string discoveryplace; // "fundort";
	//! Image credits,  "bildrecht"
	std::string credits;
      };
      
      // === Construction =======================================================
      
      //! Argumented constructor
      Robertinum (std::string const &rootNode="database",
		  std::string const &imageNode="row");

      // === Public methods =====================================================

      //! Read data from XML dump of database
      int readXML (std::istream & infile,
                   std::vector<Robertinum::Attributes> &items);

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
      
    };
    
    
  }   //  namespace source -- END
  
}  //  namespace prometheus -- END

#endif
