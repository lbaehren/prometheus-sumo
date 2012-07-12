
#include "StatisticsReader.h"

namespace prometheus {  //  namespace prometheus -- BEGIN
  
  // ============================================================================
  //
  //  Construction
  //
  // ============================================================================

  StatisticsReader::StatisticsReader (std::string const &filename)
  {
    itsFilename = filename;

    if (!checkFile()) {
      std::cerr << "Failed to open file " << filename
		<< " for read access!"
		<< std::endl;
    }
  }
  
  // ============================================================================
  //
  //  Public methods
  //
  // ============================================================================


  // ============================================================================
  //
  //  Private methods
  //
  // ============================================================================
  
  bool StatisticsReader::checkFile ()
  {
    /* Open stream for the input data ... */
    std::ifstream in (itsFilename.c_str());
    /* ... and check if the stream is ok */
    if (in.is_open()) {
      if (in.good()) {
	in.close();
	return true;
      } else {
	in.close();
	return false;
      }
    } else {
      return false;
    }
  }
  
}  //  namespace prometheus -- END

