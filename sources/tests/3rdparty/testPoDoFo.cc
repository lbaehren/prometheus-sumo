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
  \file testPoDoFo.cc
  \brief Test working with PoDoFo library
  \ingroup prometheus
  \ingroup tests
  \author Lars Baehren
  \date 2012-11-26
 */

#include <iostream>
#include <string>
#include <podofo/doc/PdfMemDocument.h>

int main (int argc, char* argv[])
{
  int status = 0;
  std::string filename;

  if ( argc>1 ) {
    filename = std::string(argv[1]);

    PoDoFo::PdfMemDocument pdf (filename.c_str());
    PoDoFo::PdfInfo * info = pdf.GetInfo();

    std::cout << "-- Filename   = " << filename << std::endl;
    std::cout << "-- Title      = " << info->GetTitle().GetStringUtf8() << std::endl;
    std::cout << "-- Author     = " << info->GetAuthor().GetStringUtf8() << std::endl;
    std::cout << "-- Creator    = " << info->GetCreator().GetStringUtf8() << std::endl;
    std::cout << "-- nof. pages = " << pdf.GetPageCount() << std::endl;
  }

  return status;
}
