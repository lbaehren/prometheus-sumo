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

#include "Common.h"

// ==============================================================================
//
//  String manipulation
//
// ==============================================================================

/*!
  \param in   -- Input string to convert to lower case.
  \return out -- String converted to lower case.
*/
std::string to_lower (std::string const &in)
{
  std::string out = in;

#ifdef WITH_BOOST
  boost::algorithm::to_lower(out);
#else
  std::transform( out.begin(), out.end(), out.begin(), lower_case );
#endif

  return out;
}
