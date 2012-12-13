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

#include "Package.h"

namespace prometheus {   // namespace prometheus -- BEGIN

  namespace config {   // namespace config -- BEGIN

    std::string Package::name ()
    {
      std::string val = "";
      get (val,"name");
      return val;
    }

    std::string Package::version ()
    {
      std::string val = "";
      get (val,"version");
      return val;
    }

    std::string Package::source ()
    {
      std::string val = "";
      get (val,"source");
      return val;
    }

    std::string Package::description ()
    {
      std::string val = "";
      get (val,"description");
      return val;
    }

    void Package::summary (std::ostream &os)
    {
      os << "[Package] Summary of internal parameters" << std::endl;
      os << "-- Name    = "  << name()           << std::endl;
      os << "-- Version = '" << version() << "'" << std::endl;
      os << "-- Source  = "  << source()         << std::endl;
    }

  }   // namespace config -- BEGIN

}   // namespace prometheus -- END
