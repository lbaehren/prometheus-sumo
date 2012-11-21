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

#ifndef CONFIG_ATTRIBUTES_MAP_H
#define CONFIG_ATTRIBUTES_MAP_H

#include <iostream>
#include <map>
#include <set>

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    /*!
      \class AttributesMap
      \ingroup prometheus
      \ingroup config
      \brief A wrapper around generic `map<K,V>` for attributes
      \test testAttributesMap.cc

      \author Lars Baehren
      \date 2012-11-19
    */
    template <class K, class V>
      class AttributesMap {

      //! Map with the attributes as <key,value> pairs
      std::map<K,V> itsAttributes;
      //! Iterator for navigation through the attributes map
      typedef typename std::map<K,V>::iterator itsIterator;

    public:

      // === Construction =======================================================

      //! Default constructor
      AttributesMap () {};

      //! Argumented constructor
      AttributesMap (K const &key,
		     V const &value) {
        set(key,value);
      }

      // === Public methods =====================================================

      //! Size of the attributes map
      inline size_t size () {
        return itsAttributes.size();
      }

      //! Get the number of attributes
      inline size_t nofAttributes () {
        return itsAttributes.size();
      }

      /*!
        \brief Get the value of an attribute
        \retval value  -- Attribute value.
        \param key     -- Key of the attribute for which to retrieve the value.
        \return status -- Return status of the method; return \c false in case
                          no attribute for the given \c key can be found.
      */
      inline bool get (V &value,
		       K const &key)
      {
        itsIterator it = itsAttributes.find(key);

        if (it==itsAttributes.end()) {
          return false;
        } else {
          value = it.second;
          return true;
        }
      }

      /*!
        \brief Set the value of a new attribute
        \param key       -- Attribute key.
        \param value     -- Attribute value.
        \param overwrite -- Overwrite existing entry?
        \return status   -- Return status of the method; returns \c false in
                            case an error occured while trying to write the new
                            value.
      */
      inline bool set (K const &key,
                       V const &value,
                       bool const &overwrite=false)
      {
        bool status = true;
        itsIterator it = itsAttributes.find(key);

        if (it==itsAttributes.end()) {
          itsAttributes[key] = value;
        } else {
          if (overwrite) {
            itsAttributes[key] = value;
          } else {
            status = false;
          }
        }

        return status;
      }

      /*!
        \brief Provide a summary of the object's internal parameters and status
        \param os -- Output stream to which the summary will be written.
      */
      void summary (std::ostream &os=std::cout)
      {
        os << "[AttributesMap] Summary of internal parameters" << std::endl;
        os << "-- nof. stored attributes = " << size() << std::endl;
      }

      /*!
        \param Show the stored attributes
        \param os -- Output stream to which the summary of stored attributes will
                     be written.
      */
      void show (std::ostream &os=std::cout)
      {
        if (!itsAttributes.empty()) {
          for (itsIterator it=itsAttributes.begin(); it!=itsAttributes.end(); ++it) {
            os << it->first << " => " << it->second << std::endl;
          }
        }
     }

    };

  }   // namespace config -- BEGIN

}   // namespace prometheus -- END

#endif
