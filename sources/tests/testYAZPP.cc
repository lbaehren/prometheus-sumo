
/*!
  \file testYAZPP.cc
  \ingroup prometheus
  \author Lars Baehren
*/

#include <iostream>
#include <yazpp/zoom.h>

using namespace ZOOM;

int main(int argc, char **argv)
{
  std::string server = "z3950.loc.gov";
  int port           = 7090;

  /* Configuration of server connection */
  connection conn(server.c_str(), port);
  conn.option("databaseName", "Voyager");
  conn.option("preferredRecordSyntax", "USMARC");

  /* Retrieve data from server */
  resultSet rs(conn, prefixQuery("@attr 1=7 0253333490"));

  // const record *rec = rs.getRecord(0);
  // std::cout << rec->render() << std::endl;
}
