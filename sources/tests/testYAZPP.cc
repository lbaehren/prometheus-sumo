
/*!
  \file testYAZPP.cc
  \brief Test using functionality of the \ref yaz toolkit
  \ingroup prometheus
  \author Lars Baehren
*/

#include <iostream>
#include <yazpp/zoom.h>

using namespace ZOOM;

// ==============================================================================
//
//  Helper functinos
//
// ==============================================================================

/*!
  \brief Show results from Z39.50 database search
  \param rs    -- Result set to display.
  \param index -- Index of the entry within the result set to display (if the set
                  is not empty).
 */
int show_results (resultSet &rs,
		  size_t const &index=0)
{
  if (rs.size()) {
    try {
      record rec (rs, index);
      std::cout << rec.render() << std::endl;
    } catch (systemException &e) {
      std::cerr << "System error " << e.errcode() << " (" << e.errmsg() << ")"
		<< std::endl;
      return 1;
    } catch (bib1Exception &e) {
      std::cerr << "BIB-1 error " << e.errcode() << " (" << e.errmsg() << "): " << e.addinfo()
		<< std::endl;
      return 2;
    } catch (queryException &e) {
      std::cerr << "Query error " << e.errcode() << " (" << e.errmsg() << "): " << e.addinfo()
		<< std::endl;
      return 3;
    } catch (exception &e) {
      std::cerr << "Error " << e.errcode() << " (" << e.errmsg() << ")"
		<< std::endl;
      return 4;
    }
  } else {
    std::cout << "--> No records to show." << std::endl;
  }
  
  return 0;
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
  
  try {
    /* Retrieve data from server */
    resultSet rs (conn, prefixQuery("@attr 1=4 Frankenstein"));
    /* Display results */
    show_results (rs);
  } catch (systemException &e) {
    std::cerr << "System error " << e.errcode() << " (" << e.errmsg() << ")"
	      << std::endl;
    ++status;
  } catch (bib1Exception &e) {
    std::cerr << "BIB-1 error " << e.errcode() << " (" << e.errmsg() << "): " << e.addinfo()
	      << std::endl;
    ++status;
  } catch (queryException &e) {
    std::cerr << "Query error " << e.errcode() << " (" << e.errmsg() << "): " << e.addinfo()
	      << std::endl;
    ++status;
  } catch (exception &e) {
    std::cerr << "Error " << e.errcode() << " (" << e.errmsg() << ")"
	      << std::endl;
    ++status;
  }
  
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
  
  try {
    /* Retrieve data from server */
    resultSet rs (conn, prefixQuery("@attr 1=4 Frankenstein"));
    std::cout << "--> nof. result sets = " << rs.size() << std::endl;
    /* Display results */
    show_results (rs);
  } catch (systemException &e) {
    std::cerr << "System error " << e.errcode() << " (" << e.errmsg() << ")"
	      << std::endl;
    ++status;
  } catch (bib1Exception &e) {
    std::cerr << "BIB-1 error " << e.errcode() << " (" << e.errmsg() << "): " << e.addinfo()
	      << std::endl;
    ++status;
  } catch (queryException &e) {
    std::cerr << "Query error " << e.errcode() << " (" << e.errmsg() << "): " << e.addinfo()
	      << std::endl;
    ++status;
  } catch (exception &e) {
    std::cerr << "Error " << e.errcode() << " (" << e.errmsg() << ")"
	      << std::endl;
    ++status;
  }
  
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
 */
int test_PPO (std::string const &server="193.175.194.50",
	      int const &port=2020)
{
  std::cout << "\n[testYAZPP::test_PPO]\n" << std::endl;

  int status = 0;

  /* Configuration of server connection */
  connection conn(server.c_str(), port);
  // conn.option("base", "bil");
  // conn.option("format", "mab");
  
  try {
    /* Retrieve data from server */
    resultSet rs(conn, prefixQuery("@attr 1=12 b0019532berl"));
    /* Process the results received from the server and display them */
    record rec (rs, 0);
    std::cout << rec.render() << std::endl;
  } catch (systemException &e) {
    std::cerr << "System error " << e.errcode() << " (" << e.errmsg() << ")"
	      << std::endl;
    ++status;
  } catch (bib1Exception &e) {
    std::cerr << "BIB-1 error " << e.errcode() << " (" << e.errmsg() << "): " << e.addinfo()
	      << std::endl;
    ++status;
  } catch (queryException &e) {
    std::cerr << "Query error " << e.errcode() << " (" << e.errmsg() << "): " << e.addinfo()
	      << std::endl;
    ++status;
  } catch (exception &e) {
    std::cerr << "Error " << e.errcode() << " (" << e.errmsg() << ")"
	      << std::endl;
    ++status;
  }
  
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

  status += test_LoC ();
  status += test_NLA ();
  status += test_PPO ();

  return status;
}
