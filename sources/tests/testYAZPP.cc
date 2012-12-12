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
  \file testYAZPP.cc
  \brief Test using functionality of the \ref yaz toolkit
  \ingroup prometheus
  \author Lars Baehren
  \date 2012/09/26

  Original script based on which this code was developed:
  \li \c update_ppo.sh -- Bash script wrapper around yaz-client tool
  \li \c ppo2xml.pl -- Perl script to convert retrieved database records
*/

#include <Common.h>

#include <fstream>
#include <yaz/record_conv.h>

using namespace ZOOM;

// ==============================================================================
//
//  Helper functions
//
// ==============================================================================

//_______________________________________________________________________________
//                                                                convert_rawdata

/*!
  \brief Convert record rawdata to formatted output

  \param rawdata - String of raw data, as retrieved through the connection.

  \li [Unicode Character 'SYMBOL FOR RECORD SEPARATOR'](http://www.fileformat.info/info/unicode/char/241e/index.htm)
 */
int convert_rawdata (std::string const &rawdata)
{
  int status = 0;
  std::vector <std::string> fields;

#ifdef WITH_BOOST
  std::cout << "--> Splitting record into single lines ..." << std::endl;
  boost::split_regex( fields, rawdata, boost::regex( "\u241E" ) );

  std::cout << "--> nof. lines = " << fields.size() << std::endl;

  for (size_t n=0; n<fields.size(); ++n) {
    std::cout << fields[n] << std::endl;
  }
#else
  std::cout << "--> Skipping test - missing Boost library." << std::endl;
#endif

  return status;
}

//_______________________________________________________________________________
//                                                                convert_results

/*!
  \brief Convert dump of the records retrieved from the database.
  \param filename -- Name of the file containing a dump of the records retrieved
                     from the database.
  \return status  -- Status of the function; returns non-zero value in case and
                     error was encountered.
*/
int convert_results (std::string const &filename)
{
  std::cout << "\n[testYAZPP::convert_results]\n" << std::endl;

  int status = 0;
  int line   = 0;
  std::string buffer;
  std::ifstream infile (filename.c_str());

  /* Regular expression to look out for */
  boost::regex expression ( "[bil]Record type: MAB" ) ;

  if ( infile.is_open() ) {
    std::cout << "--> Start reading data from file " << filename << std::endl;
    while (infile.good()) {
      ++line;
      /* Read line from file into buffer */
      std::getline (infile, buffer);
      /* ... and display it */
      std::cout << line << " : " << buffer << std::endl;
    }
  } else {
    std::cerr << "[testYAZPP::convert_results] Failed to open file"
	      << filename
	      << std::endl;
    ++status;
  }

  return status;
}

//_______________________________________________________________________________
//                                                                   show_results

/*!
  \brief Show results from Z39.50 database search
  \param rs  -- Result set to display.
  \param num -- Number of result sets to display.
  \param rawdata -- Retrieve and subsequently process raw data?
*/
int show_results (resultSet &rs,
		  size_t const &num=5,
		  bool const &rawdata=false)
{
  int status        = 0;
  size_t nofResults = rs.size();

  if (nofResults) {
    for (size_t n=0; n<num; ++n) {
      /* Record result counter */
      std::cout << "--> Result record [" << n << "/" << nofResults <<  "]" << std::endl;
      /* Render the contents of the record */
      try {
	rs.option ("elementSetName", "F");
	record rec (rs, n);
	if (rawdata) {
	  convert_rawdata (rec.rawdata());
	} else {
	  std::cout << rec.render() << std::endl;
	}
      } catch (systemException &e) {
	std::cerr << "[show_results] System error " << e.errcode()
		  << " (" << e.errmsg() << ")"
		  << std::endl;
	return 1;
      } catch (bib1Exception &e) {
	std::cerr << "[show_results] BIB-1 error " << e.errcode()
		  << " (" << e.errmsg() << "): " << e.addinfo()
		  << std::endl;
	return 2;
      } catch (queryException &e) {
	std::cerr << "[show_results] Query error " << e.errcode()
		  << " (" << e.errmsg() << "): " << e.addinfo()
		  << std::endl;
	return 3;
      } catch (exception &e) {
	std::cerr << "[show_results] Error " << e.errcode()
		  << " (" << e.errmsg() << ")"
		  << std::endl;
	return 4;
      }
    }
  } else {
    std::cout << "--> No results to display - empty set!" << std::endl;
  }

  return status;
}

//_______________________________________________________________________________
//                                                                    get_results

/*!
  \brief Get results from Z39.50 database search
  \param conn -- object representing an open connection to a Z39.50 server.
  \param pg   -- object representing a query to be submitted to the Z39.50 server
                 configured via the \c conn object.
  \param num  -- Number of result sets to display.
  \param rawdata -- Retrieve and subsequently process raw data?
*/
int get_results (connection &conn,
		 prefixQuery &pq,
		 size_t const &num=5,
		 bool const &rawdata=false)
{
  int status = 0;

  /* Define result set used as container to receive the data */
  try {
    /* Sent query to the database server ... */
    resultSet rs (conn, pq);
    /* ... and display the results */
    show_results (rs, num, rawdata);
  } catch (systemException &e) {
    std::cerr << "[get_results] System error " << e.errcode()
	      << " (" << e.errmsg() << ")"
	      << std::endl;
    ++status;
  } catch (bib1Exception &e) {
    std::cerr << "[get_results] BIB-1 error " << e.errcode()
	      << " (" << e.errmsg() << "): " << e.addinfo()
	      << std::endl;
    ++status;
  } catch (queryException &e) {
    std::cerr << "[get_results] Query error " << e.errcode()
	      << " (" << e.errmsg() << "): " << e.addinfo()
	      << std::endl;
    ++status;
  } catch (exception &e) {
    std::cerr << "[get_results] Error " << e.errcode()
	      << " (" << e.errmsg() << ")"
	      << std::endl;
    ++status;
  }

  return status;
}

//_______________________________________________________________________________
//                                                                       test_ADS

/*!
  \brief Test retrieving record from [Astrophysics Data System](http://adsabs.harvard.edu/abs_doc/ads_server.html) (ADS) database.
  \param server  -- Name of the Z39.50 server.
  \param port    -- Port number via which to establish the connection.
  \return status -- Status of the function; returns non-zero value in case an
                    error was encountered.
*/
int test_ADS (std::string const &server="z3950.adsabs.harvard.edu",
	      int const &port=210)
{
  std::cout << "\n[testYAZPP::test_ADS]\n" << std::endl;

  int status = 0;

  /* Configuration of server connection */
  connection conn(server.c_str(), port);
  conn.option("databaseName", "AST");

  /* Define query to post */
  prefixQuery pq ("@attr 1=1003 Baehren");

  status += get_results (conn, pq);

  return status;
}

//_______________________________________________________________________________
//                                                                       test_LoC

/*!
  \brief Test retrieving record from Library of Congress database.
  \param server  -- Name of the Z39.50 server.
  \param port    -- Port number via which to establish the connection.
  \return status -- Status of the function; returns non-zero value in case and
                    error was encountered.
*/
int test_LoC (std::string const &server="z3950.loc.gov",
	      int const &port=7090)
{
  std::cout << "\n[testYAZPP::test_LoC]\n" << std::endl;

  int status = 0;

  /* Configuration of server connection */
  connection conn(server.c_str(), port);
  conn.option("databaseName", "Voyager");
  conn.option("preferredRecordSyntax", "USMARC");

  /* Define query to post */
  prefixQuery pq ("@attr 1=4 Frankenstein");

  status += get_results (conn, pq);

  return status;
}

//_______________________________________________________________________________
//                                                                       test_NLA

/*!
  \brief Test retrieving record from National Library of Australia database.
  \param server  -- Name of the Z39.50 server.
  \param port    -- Port number via which to establish the connection.
  \return status -- Status of the function; returns non-zero value in case and
                    error was encountered.
*/
int test_NLA (std::string const &server="catalogue.nla.gov.au",
	      int const &port=7090)
{
  std::cout << "\n[testYAZPP::test_NLA]\n" << std::endl;

  int status = 0;

  /* Configuration of server connection */
  connection conn (server.c_str(), port);
  conn.option ("databaseName", "voyager");
  conn.option ("preferredRecordSyntax", "USMARC");

  /* Define query to post */
  prefixQuery pq ("@attr 1=4 Frankenstein");

  status += get_results (conn, pq);

  return status;
}

//_______________________________________________________________________________
//                                                                       test_baC

/*!
  \brief Test retrieving record from berliner allegroCatalog (baC) database.
  \param server  -- Name of the Z39.50 server.
  \param port    -- Port number via which to establish the connection.
  \return status -- Status of the function; returns non-zero value in case and
                    error was encountered.
*/
int test_baC (std::string const &server="ubsun02.biblio.etc.tu-bs.de",
	      int const &port=2020)
{
  std::cout << "\n[testYAZPP::test_baC]\n" << std::endl;

  int status = 0;

  /* Configuration of server connection */
  connection conn (server.c_str(), port);
  conn.option ("databaseName", "bac");
  conn.option ("user",         "opac");
  conn.option ("password",     "opac");
  conn.option ("preferredRecordSyntax", "USMARC");

  /* Define query to post */
  prefixQuery pq ("@attr 1=4 Frankenstein");

  status += get_results (conn, pq);

  return status;
}

//_______________________________________________________________________________
//                                                                       test_PPO

/*!
  \brief Test retrieving record from Pictura Paedagogica Online database.
  \param server  -- Name of the Z39.50 server.
  \param port    -- Port number via which to establish the connection.
  \return status -- Status of the function; returns non-zero value in case and
                    error was encountered.

  Line from the original bash script:
  \verbatim
  echo -e "base $base\n$find $line\nformat $form\nshow" | $YAZ $HOST:$PORT >> "$file"
  \endverbatim
  Filliing in the parameter values this becomes:
  \verbatim
  echo -e "base bil\nf @attr 1=12 b0025835berl\nformat mab\nshow" | yaz-client 193.175.194.50:2020
  \endverbatim
*/
int test_PPO (std::string const &server="193.175.194.50",
	      int const &port=2020)
{
  std::cout << "\n[testYAZPP::test_PPO]\n" << std::endl;

  int status = 0;

  /* Configuration of server connection */
  connection conn(server.c_str(), port);
  conn.option ("databaseName",   "bil");
  conn.option ("preferredRecordSyntax", "mab");

  /* Define query to post */
  prefixQuery pq ("@attr 1=12 b0009539berl");
  /* Post the query */
  status += get_results (conn, pq, 5, true);

  return status;
}

// ==============================================================================
//
//  Program main function
//
// ==============================================================================

//! Program main function
int main (int argc, char **argv)
{
  int status = 0;

  /* Test retrieving record from Astrophysics Data System (ADS) database */
  status += test_ADS ();
  /* Test retrieving record from Library of Congress database */
  status += test_LoC ();
  /* Test retrieving record from National Library of Australia database */
  status += test_NLA ();
  /* Test retrieving record from berliner allegroCatalog (baC) database */
  status += test_baC ();
  /* Test retrieving record from Pictura Paedagogica Online database */
  status += test_PPO ();

  if (argc >1) {
    status += convert_results (argv[1]);
  }

  return status;
}
