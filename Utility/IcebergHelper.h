// Iceberghelper.h
//
// David Adams
// July 2020
//
// Helper class for Iceberg.

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

};
