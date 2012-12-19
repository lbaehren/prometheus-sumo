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
  \file testCommon.cc
  \ingroup prometheus
  \brief Test common methods
  \author Lars Baehren
*/

#include <Common.h>

// ==============================================================================
//
//  Test functions
//
// ==============================================================================

//_______________________________________________________________________________
//                                                           test_system_commands

/*!
  \brief Test execution of system commands
  \return status -- Return status of the function; returns non-zero value in case
                    an error is caught.
*/
int test_system_commands ()
{
  std::cout << "\n[testCommon::test_system_commands]\n" << std::endl;

  int status = 0;
  std::vector<std::string> commands;

  // Line up the command to execute
  commands.push_back("date");
  commands.push_back("ls");
  commands.push_back("pwd");
  commands.push_back("apt-get update");
  commands.push_back("yum update");
#ifdef GEM_FOUND
  commands.push_back("gem list unicode");
  commands.push_back("gem list bliblablub");
#endif

  // --- Test 1 ----------------------------------

  std::cout << "[1] Testing execution via 'system()' ..." << std::endl;
  try {
    std::cout << "-- Checking if processor is available... ";

    if (system(NULL)) {
      std::cout << "OK" << std::endl;
    } else {
      std::cout << "FAIL" << std::endl;
      exit (EXIT_FAILURE);
    }

    for (size_t n=0; n<commands.size(); ++n) {
      // Run the command ...
      status = system (commands[n].c_str());
      // ... and report the exit status
      std::cout << "-- Command = " << commands[n] << std::endl;
      std::cout << "-- Status  = " << status      << std::endl;
    }
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  // --- Test 2 ----------------------------------

  std::cout << "[2] Testing execution via 'run_command()' ..." << std::endl;
  try {
    std::string output;

    for (size_t n=0; n<commands.size(); ++n) {
      // Run the command
      status = run_command (commands[n], output);
      // Report the results
      std::cout << "-- Command = " << commands[n] << std::endl;
      std::cout << "-- Status  = " << status      << std::endl;
      std::cout << "-- Output  = " << output      << std::endl;
    }
  } catch (std::exception &e) {
    std::cout << "ERROR : " << e.what() << std::endl;
  }

  return status;
}

//_______________________________________________________________________________
//                                                       test_string_manipulation

/*!
  \brief Test manipulation of strings
  \return status -- Return status of the function; returns non-zero value in case
                    an error is caught.
*/

int test_string_manipulation ()
{
  std::cout << "\n[testCommon::test_string_manipulation]\n" << std::endl;

  int status = 0;

  std::cout << "\n[1] Testing to_lower(std::string)" << std::endl;
  try {
    std::vector<std::string> testStrings;

    testStrings.push_back("Hello World");
    testStrings.push_back("HELLO WORLD");
    testStrings.push_back("Subversion");
    testStrings.push_back("SVN");

    for (size_t n=0; n<testStrings.size(); ++n) {
      std::cout << " - " << testStrings[n] << " -> "
		<< to_lower(testStrings[n])
		<< std::endl;
    }
  } catch (std::exception &e) {
    std::cerr << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  return status;
}

//_______________________________________________________________________________
//                                                      test_operator_overloading

/*!
  \brief Test overloading of operators
  \param nelem   -- Number of elememts for a `std::vector<T>` or `std::set<T>`
  \return status -- Return status of the function; returns non-zero value in case
                    an error is caught.
*/
int test_operator_overloading (size_t const &nelem=5)
{
  std::cout << "\n[testCommon::test_operator_overloading]\n" << std::endl;

  int status = 0;

  std::cout << "\n[1] Testing operator<<(std::vector<T>)" << std::endl;
  try {
    std::vector<bool> vec_bool (nelem,true);
    std::vector<int> vec_int (nelem,0);
    std::vector<long> vec_long (nelem,1);
    std::vector<short> vec_short (nelem,2);
    std::vector<float> vec_float (nelem,3.5);
    std::vector<double> vec_double (nelem,4.5);

    std::cout << "-- vector<bool>   = " << vec_bool   << std::endl;
    std::cout << "-- vector<int>    = " << vec_int    << std::endl;
    std::cout << "-- vector<long>   = " << vec_long   << std::endl;
    std::cout << "-- vector<short>  = " << vec_short  << std::endl;
    std::cout << "-- vector<float>  = " << vec_float  << std::endl;
    std::cout << "-- vector<double> = " << vec_double << std::endl;
  } catch (std::exception &e) {
    std::cerr << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  std::cout << "\n[2] Testing operator<<(std::set<T>)" << std::endl;
  try {
    bool array_bool[] = {true,false,true,false,true};
    std::set<bool> set_bool (&array_bool[0], &array_bool[5]);
    //
    int array_int[] = {0,1,2,3,4};
    std::set<int> set_int (&array_int[0], &array_int[5]);
    //
    long array_long[] = {0,1,2,3,4};
    std::set<long> set_long (&array_long[0], &array_long[5]);
    //
    short array_short[] = {0,1,2,3,4};
    std::set<short> set_short (&array_short[0], &array_short[5]);
    //
    float array_float[] = {0.0,0.1,0.2,0.3,0.4};
    std::set<float> set_float (&array_float[0], &array_float[5]);
    //
    double array_double[] = {0.1,0.12,0.123,0.1234,0.12345};
    std::set<double> set_double (&array_double[0], &array_double[5]);
    //
    std::string array_string[] = {"a","b","c","d","e"};
    std::set<std::string> set_string (&array_string[0], &array_string[5]);

    std::cout << "-- set<bool>   = " << set_bool   << std::endl;
    std::cout << "-- set<int>    = " << set_int    << std::endl;
    std::cout << "-- set<long>   = " << set_long   << std::endl;
    std::cout << "-- set<short>  = " << set_short  << std::endl;
    std::cout << "-- set<float>  = " << set_float  << std::endl;
    std::cout << "-- set<double> = " << set_double << std::endl;
    std::cout << "-- set<string> = " << set_string << std::endl;
  } catch (std::exception &e) {
    std::cerr << "ERROR : " << e.what() << std::endl;
    ++status;
  }

  // std::cout << "\n[3] Testing operator<<(std::map<T,S>)\n" << std::endl;
  // {
  //   std::map<int,std::string> mapIntString;
  //   mapIntString[0] = "Hello";
  //   mapIntString[1] = "World";

  //   std::cout << "-- map<int,string> = " << mapIntString << std::endl;
  // }

  return status;
}

// ==============================================================================
//
//  Program main function
//
// ==============================================================================

int main ()
{
  int status = 0;

  status += test_system_commands ();
  status += test_string_manipulation ();
  status += test_operator_overloading ();

  return status;
}
