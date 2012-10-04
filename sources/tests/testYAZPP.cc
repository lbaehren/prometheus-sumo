
/*!
  \file testYAZPP.cc
  \brief Test using functionality of the \ref yaz toolkit
  \ingroup prometheus
  \author Lars Baehren

  [Standard Option Values](http://zoom.z3950.org/api/zoom-current.html#3.9)

  \li Values for \c preferredRecordSyntax
  | Value   | Description |
  |---------|-------------|
  | USMARC  | USMARC records (OID 1.2.840.10003.5.10) |
  | SUTRS   | SUTRS records (OID 1.2.840.10003.5.101) |
  | XML     | XMLK records, corresponding to the MIME-type text/xml (OID 1.2.840.10003.5.109.10) |
  | SGML    | SGML records (OID 1.2.840.10003.5.109.9) |
  | GRS-1   | GRS-1 records (OID 1.2.840.10003.5.105) |
  | OPAC    | OPAC records (OID 1.2.840.10003.5.102) |
  | EXPLAIN | Explain records (OID 1.2.840.10003.5.100) |
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
//                                                                   show_results

/*!
  \brief Show results from Z39.50 database search
  \param rs  -- Result set to display.
  \param num -- Number of result sets to display.
 */
int show_results (resultSet &rs,
		  size_t const &num=5)
{
  size_t nofResults = rs.size();

  if (nofResults) {
    std::cout << "--> nof. result sets = " << nofResults << std::endl;
    for (size_t n=0; n<num; ++n) {
      try {
	record rec (rs, num);
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
    }
  } else {
    std::cout << "--> No results to display - empty set!" << std::endl;
  }

  return 0;
}

//_______________________________________________________________________________
//                                                                    get_results

/*!
  \brief Get results from Z39.50 database search
  \param conn -- object representing an open connection to a Z39.50 server.
  \param pg   -- object representing a query to be submitted to the Z39.50 server
                 configured via the \c conn object.
  \param num  -- Number of result sets to display.
 */
int get_results (connection &conn,
		 prefixQuery &pq,
		 size_t const &num=5)
{
  int status = 0;
  
  /* Define result set used as container to receive the data */
  try {
    /* Sent query to the database server ... */
    resultSet rs (conn, pq);
    /* ... and display the results */
    show_results (rs, num);
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
//                                                                       test_ADS

/*!
  \brief Test retrieving record from [Astrophysics Data System](http://adsabs.harvard.edu/abs_doc/ads_server.html) (ADS) database.
  \param server  -- Name of the Z39.50 server.
  \param port    -- Port number via which to establish the connection.
  \return status -- Status of the function; returns non-zero value in case and
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
  Result from online search:
  \verbatim
  http://bbf.dipf.de/cgi-opac/bil.pl?t_direct=x&f_IDN=b0009539berl&transit=f_art%3Dhoening%252C%2Bjohann%2Blorenz%2BAND%2BHoening%252C%2BJohann%2BLorenz%26getback%3Dexpmask%26t_kombi%3DSuche%2Bstarten
  \endverbatim
 */
int test_PPO (std::string const &server="193.175.194.50",
	      int const &port=2020)
{
  std::cout << "\n[testYAZPP::test_PPO]\n" << std::endl;

  int status = 0;

  /* Configuration of server connection */
  connection conn(server.c_str(), port);
  conn.option ("base",           "bil");
  conn.option ("format",         "mab");
  conn.option("preferredRecordSyntax", "BIS");

  /* Define query to post */
  prefixQuery pq ("@attr 1=12 b0009539berl");
  
  status += get_results (conn, pq);

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
  // status += test_ADS ();
  /* Test retrieving record from Library of Congress database */
  // status += test_LoC ();
  /* Test retrieving record from National Library of Australia database */
  // status += test_NLA ();
  /* Test retrieving record from berliner allegroCatalog (baC) database */
  status += test_baC ();
  /* Test retrieving record from Pictura Paedagogica Online database */
  status += test_PPO ();

  return status;
}
