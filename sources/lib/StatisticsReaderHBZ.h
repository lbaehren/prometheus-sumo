
#ifndef STATISTICS_READER_HBZ_H
#define STATISTICS_READER_HBZ_H

#include "StatisticsReader.h"
#include "StatisticsHBZ.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  /*!
    \class StatisticsReaderHBZ
    \ingroup prometheus
    \brief Class for reading statistics file for HBZ
    \author Lars Baehren
    \date 2012-07-12
  */
  class StatisticsReaderHBZ : public StatisticsReader {
    
    std::vector<std::string> itsColumns;
    std::vector<StatisticsHBZ> itsEntries;
    std::vector<StatisticsHBZ>::iterator itsEntriesIterator;
    
  public:
    
    //! Argumented constructor
    StatisticsReaderHBZ (std::string const &filename);
    
    // === Parameter access =====================================================
    

    // === Public methods =======================================================

    //! Read and process the input data file
    bool processFile ();

    //! Provide a summary of the object's internal parameters and status
    void summary (std::ostream &os);

  private:

    // === Private methods ======================================================

    bool extactColumnHeaders (std::ifstream &in);

  };
  
}  //  namespace prometheus -- END

#endif

