
#include "StatisticsReaderHBZ.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  // ============================================================================
  //
  //  Public methods
  //
  // ============================================================================

  //_____________________________________________________________________________
  //                                                                  processFile

  bool StatisticsReaderHBZ::processFile ()
  {
    bool status = true;
    std::string line;
    
    //______________________________________________________
    // Open input data file
    
    std::ifstream in (itsFilename.c_str());
    if (!in.is_open()) return false;
    
    //______________________________________________________
    // Extract the first line with the column headers

    status *= extactColumnHeaders (in);

    return status;
  }

  //_____________________________________________________________________________
  //                                                                      summary

  void StatisticsReaderHBZ::summary (std::ostream &os)
  {
    os << "[StatisticsReaderHBZ] Summary of internal parameters." << std::endl;
    os << "-- Input data file  = " << itsFilename                 << std::endl;
    os << "-- nof data columns = " << itsColumns.size()           << std::endl;
  }
  
  // ============================================================================
  //
  //  Private methods
  //
  // ============================================================================

  bool StatisticsReaderHBZ::extactColumnHeaders (std::ifstream &in)
  {
    bool status = true;
    std::string line;

    getline(in,line);
    Tokenizer tok(line);
    itsColumns.assign(tok.begin(),tok.end());

    return status;
  }
  
  
}  //  namespace prometheus -- END

#endif

