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

#include <Common.h>

namespace prometheus {   //   namespace prometheus -- BEGIN

  /*!
    \brief Summary of configuration settings
    \param os -- Output stream to which the summary will be written.
  */
  void configuration_summary (std::ostream &os)
  {
    /*
     *  System configuration summary
     */
    os << " System configuration:" << std::endl;
    os << " .. CMake version   = " << CMAKE_VERSION        << std::endl;
    os << " .. System name     = " << CMAKE_SYSTEM         << std::endl;
    /*
     *  Project configuration summary
     */
    os << " Project configuration:" << std::endl;
    os << " .. Project name    = " << PROJECT_NAME         << std::endl;
    os << " .. Project version = " << PROJECT_VERSION      << std::endl;
    os << " .. Install prefix  = " << CMAKE_INSTALL_PREFIX << std::endl;
#ifdef GEM_VERSION
    os << " .. Gem version     = " << GEM_VERSION          << std::endl;
#endif
#ifdef RAKE_VERSION
    os << " .. Rake version    = " << RAKE_VERSION         << std::endl;
#endif
#ifdef RUBY_VERSION
    os << " .. Ruby version    = " << RUBY_VERSION         << std::endl;
#endif
  }

}   //   namespace prometheus -- END
