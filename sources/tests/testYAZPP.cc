
/*!
  \file testYAZPP.cc
  \brief Test using functionality of the YAZ toolkit
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

//_______________________________________________________________________________
//                                                                       test_LoC

/*!
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
    resultSet rs(conn, prefixQuery("@attr 1=7 0253333490"));
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

//_______________________________________________________________________________
//                                                                       test_PPO

/*!
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

int main (int argc, char **argv)
{
  int status = 0;

  status += test_LoC ();
  status += test_PPO ();

  return status;
}
