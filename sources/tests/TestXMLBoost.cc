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

/*!
  \file TestXMLBoost.cc
  \ingroup prometheus
  \author Lars Baehren
 */

#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;

// === Data structures =========================================================

/*!
  \brief Item in the collection of the Beeskow Kunstarchiv
  
    \code{.xml}
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
struct ItemBeeskow {
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

/*!
  \brief Item in the collection kassel.xml

  \code{.xml}
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
  \endcode
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

// === Functions ===============================================================

//______________________________________________________________________________
//                                                      read_beeskow_kunstarchiv

/*!
  \brief Read database for Beeskow Kunstarchiv

  \param infile -- Input stream connected to the XML dump for the collection.
  \retval collection -- Array with the items in the colleciton
 */
int read_beeskow_kunstarchiv (std::istream & infile,
                              std::vector<ItemBeeskow> &collection)
{
  ptree pt;

  std::cout << "-- Reading XML input file ..." << std::endl;
  read_xml(infile, pt);

  std::cout << "-- Parsin XML document ..." << std::endl;
  BOOST_FOREACH( ptree::value_type const& v, pt.get_child("root") ) {
    if( v.first == "row" ) {
      ItemBeeskow r;
      // r.artist   = v.second.get<std::string>("KünstlerIn");
      r.location = v.second.get<std::string>("Standort");
      r.title    = v.second.get<std::string>("Titel");
      r.date     = v.second.get<std::string>("Datierung");
      r.category = v.second.get<std::string>("Gattung");
      r.units    = v.second.get<std::string>("Einheit");
      r.object   = v.second.get<unsigned int>("Ob_f41");
      r.height   = v.second.get<std::string>("Höhe");
      r.width    = v.second.get<std::string>("Breite");
      collection.push_back(r);
    }
  }

  return 0;
}

//______________________________________________________________________________
//                                                                 read_theoleik

/*!
  \brief Read database for Institut für Evangelische Theologie

  \param infile -- Input stream connected to the XML dump for the collection.
  \retval collection -- Array with the items in the colleciton
 */
int read_theoleik (std::istream & infile,
                   std::vector<ItemTheolEik> &collection)
{
  ptree pt;

  std::cout << "-- Reading XML input file ..." << std::endl;
  read_xml(infile, pt);

  std::cout << "-- Parsin XML document ..." << std::endl;
  BOOST_FOREACH( ptree::value_type const& v, pt.get_child("dataroot") ) {
    if( v.first == "row" ) {
      ItemTheolEik node;
      node.location = v.second.get<std::string>("Standort");
      node.title    = v.second.get<std::string>("Titel");
      node.date     = v.second.get<std::string>("Datierung");
      node.category = v.second.get<std::string>("Gattung");
      collection.push_back(node);
    }
  }

  return 0;
  return 0;
}
                              
// === Main function ===========================================================

/*!
  \brief Test program main function
*/
int main(int argc, char* argv[])
{
  int status = 0;
  std::string filename;

  /* Parse command line parameters */
  if ( argc>1 ) {
    /* Get the name of the testdata ... */
    filename = std::string(argv[1]);
    /* ... and run the actual tests. */
    std::ifstream infile (filename.c_str());
    
    if (infile.is_open()) {

      std::vector<ItemBeeskow> collection;

      /* Parse the contents of the document */
      read_beeskow_kunstarchiv (infile, collection);

      /* Summary of document contents */
      std::cout << "-- nof. collection items = " << collection.size() << std::endl;
      for (unsigned int n=0; n<collection.size(); ++n) {
	std::cout << " --> " << collection[n].title
		  << "\t(" << collection[n].date << ")"
		  << std::endl;
      }

    } else {
      std::cerr << "--> Failed to open file " << filename << std::endl;
      return 1;
    }
  }
  
  return status;
}
