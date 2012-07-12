
#include "StatisticsReaderHBZ.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================

  StatisticsReaderHBZ::StatisticsReaderHBZ (std::string const &filename)
    : StatisticsReader (filename)
  {
  }

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
    std::vector<std::string> data;

    /* Open stream for the input data ... */
    std::ifstream in (itsFilename.c_str());
    /* ... and check if the stream is ok */
    if (!in.is_open()) return false;
    /* Reset the internal storage for the actual entries */
    itsEntries.clear();

    //______________________________________________________
    // Extract the first line with the column headers

    status *= extactColumnHeaders (in);

    //______________________________________________________
    // Process the rows containing the actual data
    
    while (getline(in,line)) {
      /* Pass the line to the Tokenizer */
      Tokenizer tok(line);
      /* Retrieve the individual tokens */
      data.assign(tok.begin(),tok.end());
      
      if (data.size() < 3) {
	continue;
      }
      
      itsEntries.push_back(StatisticsHBZ(data[0],data[1],data[2],data[3]));
    }
    
    return status;
  }

  //_____________________________________________________________________________
  //                                                                      summary

  std::set<std::string> StatisticsReaderHBZ::institutions ()
  {
    std::vector<StatisticsHBZ>::iterator it;
    std::set<std::string> data;

    for (it=itsEntries.begin(); it!=itsEntries.end(); ++it) {
      data.insert(it->consortium());
    }

    return data;
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

    if (itsColumns.empty()) {
      std::cerr << "[StatisticsReaderHBZ::extactColumnHeaders]"
		<< " No column headers extracted!"
		<< std::endl;
    }

    return status;
  }
  
}  //  namespace prometheus -- END
