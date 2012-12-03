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

#include <Config/AttributesMap.h>

/*!
  \file testAttributesMap.cc
  \ingroup prometheus
  \ingroup tests
  \brief A collection of tests for the prometheus::config::AttributesMap class
  \author Lars Baehren
  \date 2012-11-21
*/

// === Test functions ===========================================================

//_______________________________________________________________________________
//                                                              test_construction

//! Test construction of a prometheus::config::AttributesMap object
int test_construction ()
{
  std::cout << "\n[testAttributesMap::test_construction]\n" << std::endl;

  int status = 0;

  // --- Tests for default constructor ---

  std::cout << "[1] Testing AttributesMap<int,T>() ..." << std::endl;
  try {
    prometheus::config::AttributesMap<int,int> map_int_int;
    prometheus::config::AttributesMap<int,short> map_int_short;
    prometheus::config::AttributesMap<int,long> map_int_long;
    prometheus::config::AttributesMap<int,float> map_int_float;
    prometheus::config::AttributesMap<int,double> map_int_double;
    prometheus::config::AttributesMap<int,std::string> map_int_string;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Testing AttributesMap<short,T>() ..." << std::endl;
  try {
    prometheus::config::AttributesMap<short,int> map_short_int;
    prometheus::config::AttributesMap<short,short> map_short_short;
    prometheus::config::AttributesMap<short,long> map_short_long;
    prometheus::config::AttributesMap<short,float> map_short_float;
    prometheus::config::AttributesMap<short,double> map_short_double;
    prometheus::config::AttributesMap<short,std::string> map_short_string;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[3] Testing AttributesMap<long,T>() ..." << std::endl;
  try {
    prometheus::config::AttributesMap<long,int> map_long_int;
    prometheus::config::AttributesMap<long,short> map_long_short;
    prometheus::config::AttributesMap<long,long> map_long_long;
    prometheus::config::AttributesMap<long,float> map_long_float;
    prometheus::config::AttributesMap<long,double> map_long_double;
    prometheus::config::AttributesMap<long,std::string> map_long_string;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[4] Testing AttributesMap<float,T>() ..." << std::endl;
  try {
    prometheus::config::AttributesMap<float,int> map_float_int;
    prometheus::config::AttributesMap<float,short> map_float_short;
    prometheus::config::AttributesMap<float,long> map_float_long;
    prometheus::config::AttributesMap<float,float> map_float_float;
    prometheus::config::AttributesMap<float,double> map_float_double;
    prometheus::config::AttributesMap<float,std::string> map_float_string;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[5] Testing AttributesMap<double,T>() ..." << std::endl;
  try {
    prometheus::config::AttributesMap<double,int> map_double_int;
    prometheus::config::AttributesMap<double,short> map_double_short;
    prometheus::config::AttributesMap<double,long> map_double_long;
    prometheus::config::AttributesMap<double,float> map_double_float;
    prometheus::config::AttributesMap<double,double> map_double_double;
    prometheus::config::AttributesMap<double,std::string> map_double_string;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[6] Testing AttributesMap<string,T>() ..." << std::endl;
  try {
    prometheus::config::AttributesMap<std::string,int> map_string_int;
    prometheus::config::AttributesMap<std::string,short> map_string_short;
    prometheus::config::AttributesMap<std::string,long> map_string_long;
    prometheus::config::AttributesMap<std::string,float> map_string_float;
    prometheus::config::AttributesMap<std::string,double> map_string_double;
    prometheus::config::AttributesMap<std::string,std::string> map_string_string;
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  // --- Tests for argumented constructor ---

  std::cout << "[7] Testing AttributesMap<int,T>(int,T) ..." << std::endl;
  try {
    prometheus::config::AttributesMap<int,int> map_int_int (0,1);
    prometheus::config::AttributesMap<int,short> map_int_short (0,2);
    prometheus::config::AttributesMap<int,long> map_int_long (0,3);
    prometheus::config::AttributesMap<int,float> map_int_float (0,4.5);
    prometheus::config::AttributesMap<int,double> map_int_double (0,5.5);
    prometheus::config::AttributesMap<int,std::string> map_int_string (0,"Hello");
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[8] Testing AttributesMap<short,T>(short,T) ..." << std::endl;
  try {
    prometheus::config::AttributesMap<short,int> map_short_int (0,1);
    prometheus::config::AttributesMap<short,short> map_short_short (0,2);
    prometheus::config::AttributesMap<short,long> map_short_long (0,3);
    prometheus::config::AttributesMap<short,float> map_short_float (0,4.5);
    prometheus::config::AttributesMap<short,double> map_short_double (0,5.5);
    prometheus::config::AttributesMap<short,std::string> map_short_string (0,"Hello");
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[9] Testing AttributesMap<long,T>() ..." << std::endl;
  try {
    prometheus::config::AttributesMap<long,int> map_long_int (0,1);
    prometheus::config::AttributesMap<long,short> map_long_short (0,2);
    prometheus::config::AttributesMap<long,long> map_long_long (0,3);
    prometheus::config::AttributesMap<long,float> map_long_float (0,4.5);
    prometheus::config::AttributesMap<long,double> map_long_double (0,5.5);
    prometheus::config::AttributesMap<long,std::string> map_long_string (0,"Hello");
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[10] Testing AttributesMap<float,T>(float,T) ..." << std::endl;
  try {
    prometheus::config::AttributesMap<float,int> map_float_int (0.5,1);
    prometheus::config::AttributesMap<float,short> map_float_short (0.5,2);
    prometheus::config::AttributesMap<float,long> map_float_long (0.5,3);
    prometheus::config::AttributesMap<float,float> map_float_float (0.5,4.5);
    prometheus::config::AttributesMap<float,double> map_float_double (0.5,5.5);
    prometheus::config::AttributesMap<float,std::string> map_float_string (0.5,"Hello");
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  return status;
}

//_______________________________________________________________________________
//                                                          test_parameter_access

//! Test access to the parameters stored in the attributes map
int test_parameter_access ()
{
  std::cout << "\n[testAttributesMap::test_parameter_access]\n" << std::endl;

  int status = 0;

  std::cout << "[1] Test accessing parameters of AttributesMap<string,int>" << std::endl;
  try {
    prometheus::config::AttributesMap<std::string,int> attr;

    attr.set("Battleship",2012);
    attr.set("Battle Los Angeles",2011);
    attr.set("Prometheus",2012);
    attr.set("The Abyss",1989);

    attr.summary();
    attr.show();
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "[2] Test accessing parameters of AttributesMap<string,string>" << std::endl;
  try {
    prometheus::config::AttributesMap<std::string,std::string> attr;

    attr.set("apache_image_resizer",">= 0.0.7");
    attr.set("apache_secure_download",">= 0.2.1");
    attr.set("blackwinter-ipaddress","= 0.8.0.1");
    attr.set("ferret","= 0.11.8.1");

    attr.summary();
    attr.show();
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  return status;
}

// === Test program main function ===============================================

//! Test program main function
int main ()
{
  int status = 0;
  
  status += test_construction ();
  status += test_parameter_access ();

  return status;
}
