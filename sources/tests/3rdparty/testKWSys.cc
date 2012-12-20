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
  \file testKWSys.cc
  \brief Test working with KWSys library
  \ingroup prometheus
  \ingroup tests
  \author Lars Baehren
  \date 2012-11-26
*/

#include <iostream>
#include <kwsys/Configure.hxx>
#include <kwsys/SystemInformation.hxx>

int test_Check ()
{
  std::cout << "\n[testKWSys::test_Check]\n" << std::endl;

  kwsys::SystemInformation sysInfo;

  sysInfo.RunCPUCheck ();
  sysInfo.RunOSCheck();
  sysInfo.RunMemoryCheck();

  std::cout << "-- Hostname ................ = " << sysInfo.GetHostname()    << std::endl;
  std::cout << "-- Processor clock frequency = " << sysInfo.GetProcessorClockFrequency()
	    << std::endl;
  std::cout << "-- OS name ................. = " << sysInfo.GetOSName ()            << "\n";
  std::cout << "-- OS Release .............. = " << sysInfo.GetOSRelease ()         << "\n";
  std::cout << "-- OS Version .............. = " << sysInfo.GetOSVersion ()         << "\n";
  std::cout << "-- OS platform ............. = " << sysInfo.GetOSPlatform ()        << "\n";
  std::cout << "-- Total memory ............ = " << sysInfo.GetHostMemoryTotal()    << "\n";
  std::cout << "-- Total virtual memory .... = " << sysInfo.GetTotalVirtualMemory() << "\n";

  return 0;
}

int main (int argc, char* argv[])
{
  int status = 0;

  status += test_Check ();

  return status;
}

