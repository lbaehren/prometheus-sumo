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

#ifndef COMMON_H
#define COMMON_H

/*!
  \file Common.h
  \ingroup prometheus
  \author Lars B&auml;hren

  \brief Collection of commly used routines and functionality
*/

#include <iostream>
#include <map>
#include <set>
#include <vector>

#include <Config/ConfigSettings.h>

// ==============================================================================
//
//  String manipulation
//
// ==============================================================================

//! Convert string to lower case
std::string to_lower (std::string const &in);

// ==============================================================================
//
//  Operator overloading
//
// ==============================================================================

//_______________________________________________________________________________
//                                                                           show

/*!
  \brief Write elements of an array/vector/set to an output stream

  \param os    -- Stream to which the output is written.
  \param start -- Iterator pointing to the first element.
  \param end   -- Iterator pointing to the position after the last element.
*/
template <typename T>
std::ostream& show (std::ostream& os,
                    T start,
                    T end)
{
  T it;

  os << "[";

  for (it=start; it!=end; ++it) {
    os << " " << *it;
  }

  os << " ]";

  return os;
}

//_______________________________________________________________________________
//                                                                     operator<<

/*!
  \brief Overloading of output operator to display std::vector<T>

  \param os  -- Output stream to which the result will be written to
  \param vec -- The vector to be displayed
*/
template <typename T>
std::ostream& operator<< (std::ostream &os,
                          const std::vector<T> &vec)
{
  return show (os, vec.begin(), vec.end());
}

//_______________________________________________________________________________
//                                                                     operator<<

/*!
  \brief Overloading of output operator to display std::set<T>

  \param os  -- Output stream to which the result will be written to
  \param vec -- The set to be displayed
*/
template <typename T>
std::ostream& operator<< (std::ostream &os,
                          const std::set<T> &s)
{
  return show (os, s.begin(), s.end());
}

//_______________________________________________________________________________
//                                                                     operator<<

/* template <typename K, typename V> */
/*   std::ostream& operator<< (std::ostream &os, */
/* 			    const std::map<K,V> &m) */
/* { */
/*   typename std::map<K,V>::iterator it; */

/*   os << "["; */

/*   for (it=m.begin(); it!=m.end(); ++it) { */
/*     os << " (" << it->first << "," << it->second << ")"; */
/*   } */

/*   os << " ]"; */

/*   return os; */
/* } */

#endif
