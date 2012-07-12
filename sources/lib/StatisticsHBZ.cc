
#include "StatisticsHBZ.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================

  /*!
    \param time       -- Time period for which the statistics have been generated.
    \param consortium -- Name of the consortium member.
    \param signum     -- Signum of the institution.
    \param user       -- Name of the user.
    \param customerID -- Customer ID.
  */
  StatisticsHBZ::StatisticsHBZ (std::string const &time,
				std::string const &consortium,
				std::string const &signum,
				std::string const &user,
				std::string const &customerID)
  {
    init (time,
	  consortium,
	  signum,
	  user,
	  customerID);
  }

  // ============================================================================
  //
  //  Private methods
  //
  // ============================================================================
  
  void StatisticsHBZ::summary (std::ostream &os)
  {
    os << "-- Time period        = " << itsTime       << std::endl;
    os << "-- Consortium member  = " << itsConsortium << std::endl;
    os << "-- Institution signum = " << itsSignum     << std::endl;
  }
  
  // ============================================================================
  //
  //  Private methods
  //
  // ============================================================================
  
  /*!
    \param time       -- Time period for which the statistics have been generated.
    \param consortium -- Name of the consortium member.
    \param signum     -- Signum of the institution.
    \param user       -- Name of the user.
    \param customerID -- Customer ID.
  */
  void StatisticsHBZ::init (std::string const &time,
			    std::string const &consortium,
			    std::string const &signum,
			    std::string const &user,
			    std::string const &customerID)
  {
    itsTime       = time;
    itsConsortium = consortium;
    itsSignum     = signum;
    itsUser       = user;
    itsCustomerID = customerID;
  }
  
}  //  namespace prometheus -- END
