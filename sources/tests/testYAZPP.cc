
/*!
  \file testYAZPP.cc
  \brief Test using functionality of the YAZ toolkit
  \ingroup prometheus
  \author Lars Baehren
*/

#include <iostream>
#include <yazpp/zoom.h>

using namespace ZOOM;

// === Helper functions =========================================================

/*!
  \param server = Name of the Z39.50 server.
  \param port   = Port number via which to establish the connection.
 */
int test_LoC (std::string const &server="z3950.loc.gov",
	      int const &port=7090)
{
  /* Configuration of server connection */
  connection conn(server.c_str(), port);
  conn.option("databaseName", "Voyager");
  conn.option("preferredRecordSyntax", "USMARC");

  /* Retrieve data from server */
  resultSet rs(conn, prefixQuery("@attr 1=7 0253333490"));

  /* Process the results received from the server and display them */
  record rec (rs, 0);
  std::cout << rec.render() << std::endl;

  return 0;
}

// === Program main function ====================================================

int main(int argc, char **argv)
{
  test_LoC ();

  return 0;
}
