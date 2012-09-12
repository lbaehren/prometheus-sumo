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

using prometheus::SourceDump;

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

      // === Construction =======================================================

      //! Argumented constructor
      TheolEik (std::string const &rootNode="FMPDSORESULT",
	        std::string const &imageNode="ROW");

    private:

      //! Initialize internal attributes
      void init ();

    };  //  class TheolEik -- END

  };  //  namespace source -- END

}  //  namespace prometheus -- END

#endif
