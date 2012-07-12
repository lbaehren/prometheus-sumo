
#ifndef STATISTICS_HBZ_H
#define STATISTICS_HBZ_H

#include "Common.h"
#include "StatisticsReader.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  /*!
    \class StatisticsHBZ
    \ingroup prometheus
    \brief Access statistics provided to the HBZ
    \author Lars Baehren
    \date 2012-07-12

    The statistics overview provided to the Hochschulbibliothekszentrum des
    Landes Nordrhein-Westfalen ([HBZ](http://www.hbz-nrw.de/)) typically will
    be generated in the following (uman-readable) format:

    \verbatim
    Jahr_Monat,Konsortial-Mitglied,Sigel,Nutzer,Einzelkunden-Subidentifier,Sessions,Searches,Downloads
    2012_04,"Aachen, Arch.", 82/211  ,Aachen_Uni_RWTH_Kunstgeschichte,,33,485,298
    2012_04,Abteilung Geschichte der Universität Bielefeld,361,Bielefeld_Uni,,8,99,106
    2012_04,Alanus Hochschule für Kunst und Gesellschaft, DE-Aft1 ,Alfter_HS_KunstGesellschaft,,16,385,521
    2012_04,"Amsterdam, Uni", AMS425  ,Amsterdam_Uni,,0,0,0
    \endverbatim
  */
  class StatisticsHBZ {

    //! Time period for which the statistics have been generated
    std::string itsTime;
    //! Name of the consortium member
    std::string itsConsortium;
    //! Signum of the institution
    std::string itsSignum;
    //! Name of the user
    std::string itsUser;
    //! Customer ID
    std::string itsCustomerID;
    //! nof sessions during the covered time period
    unsigned int itsNofSessions;
    //! nof searches during the covered time period
    unsigned int itsNofSearches;
    //! nof downloads during the covered time period
    unsigned int itsNofDownloads;

  public:

    //! Argumented constructor
    StatisticsHBZ (std::string const &time,
		   std::string const &consortium="",
		   std::string const &signum="",
		   std::string const &user="",
		   std::string const &customerID="");

    // === Parameter access =====================================================

    //! Get the time period for which the statistics have been generated
    inline std::string time () {
      return itsTime;
    }
    //! Set the time period for which the statistics have been generated
    inline void setTime (std::string const &time) {
      itsTime = time;
    }

    //! Get the name of the consortium member
    inline std::string consortium () {
      return itsConsortium;
    }
    //! Set the name of the consortium member
    inline void setConsortium (std::string const &consortium) {
      itsConsortium = consortium;
    }

    //! Get the signum of the institution
    inline std::string signum () {
      return itsSignum;
    }
    //! Set the signum of the institution
    inline void signum (std::string const &signum) {
      itsSignum = signum;
    }

    //! Get the name of the user
    inline std::string user () {
      return itsUser;
    }
    //! Set the name of the user
    inline void setUser (std::string const &user) {
      itsUser = user;
    }

    //! Get the customer ID
    inline std::string customerID () {
      return itsCustomerID;
    }
    //! Set the customer ID
    inline void setCustomerID (std::string const &customerID) {
      itsCustomerID = customerID;
    }

    // === Public methods =======================================================

    //! Provide a summary of the object's internal parameters and status
    inline void summary () {
      summary (std::cout);
    }

    //! Provide a summary of the object's internal parameters and status
    void summary (std::ostream &os);

  private:

    // === Private methods ======================================================

    //! Initialize internal parameters
    void init (std::string const &time,
	       std::string const &consortium="",
	       std::string const &signum="",
	       std::string const &user="",
	       std::string const &customerID="");
    
  };
  
}  //  namespace prometheus -- END

#endif

