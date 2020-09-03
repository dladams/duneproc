// Iceberghelper.h
//
// David Adams
// July 2020
//
// Helper class for Iceberg.

#include <string>
#include <map>

class IcebergHelper {

public:

  static void help();

  // Return the detector run.
  static unsigned int detectorRun(unsigned int run) {
    if ( run < 5700 ) return 3;
    if ( run > 5800 ) return 4;
    return 0;
  }

  static bool isOdd(unsigned int icha) {
    if ( icha >= 400 && icha < 1040 ) return icha%2;
    return (icha + 1)%2;
  }

  // Return a map of date strings indexed by first run number in the range
  // [irun1, irun2).
  static std::map<unsigned int, std::string>
  runDates(unsigned int irun1, unsigned int irun2i, int dbg =0);

};
