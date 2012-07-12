
#ifndef STATISTICS_READER_H
#define STATISTICS_READER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>
#include <map>

#ifdef WITH_BOOST
#include <boost/tokenizer.hpp>
typedef boost::tokenizer< boost::escaped_list_separator<char> > Tokenizer;
#endif


namespace prometheus {  //  namespace prometheus -- BEGIN
  
  /*!
    \class StatisticsReader
    \ingroup prometheus
    \brief Base class for reading statistics files
    \author Lars Baehren
    \date 2012-07-12
  */
  class StatisticsReader {

  protected:

    //! Name of the input data file
    std::string itsFilename;

  public:
    
    //! Argumented constructor
    StatisticsReader (std::string const &filename);
    
    // === Parameter access =====================================================
    
    //! Get the name of the input data file
    inline std::string filename () {
      return itsFilename;
    }
    //! Set the name of the input data file
    inline void setFilename (std::string const &filename) {
      itsFilename = filename;
    }

    // === Public methods =======================================================

    //! Read and process the input data file
    virtual bool processFile () = 0;

    //! Provide a summary of the object's internal parameters and status
    inline void summary () {
      summary (std::cout);
    }

    //! Provide a summary of the object's internal parameters and status
    void summary (std::ostream &os);

  private:

    // === Private methods ======================================================

  };
  
}  //  namespace prometheus -- END

#endif

