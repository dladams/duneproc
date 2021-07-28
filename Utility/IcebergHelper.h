// Iceberghelper.h
//
// David Adams
// July 2020
//
// Helper class for Iceberg.

#ifndef IcebegHelper_H
#define IcebegHelper_H

#include <string>
#include <vector>
#include <map>

class IcebergHelper {

public:

  using Name = std::string;
  using NameVector = std::vector<Name>;
  using Index = unsigned int;
  using IndexVector = std::vector<Index>;

  static void help();

  // Return the detector run.
  static unsigned int detectorRun(unsigned int run) {
    if ( run < 5700 ) return 3;
    if ( run > 5800 ) return 4;
    return 0;
  }

  // Odd/even for Iceberg 4.
  static bool isOdd(unsigned int icha) {
    if ( icha >= 400 && icha < 1040 ) return icha%2;
    return (icha + 1)%2;
  }

  // Return a map of date strings indexed by first run number in the range
  // [irun1, irun2).
  static std::map<unsigned int, Name>
  runDates(unsigned int irun1, unsigned int irun2i, int dbg =0);

  // Return all run periods that contain the given run period.
  // Return is ordered highest to lowest.
  // E.g. 5C22-cos2 is returns [5C22-cos, 5C22, 5].
  static std::vector<Name> runPeriodContainers(Name sper);

  // Return the run period at a given level that is or contains a given
  // run period.
  // E.g. level 1 for 5C22-cos2 returns 5C22.
  // Returns blank if the period is above the level, e.g. level 2 for 5C22.
  static Name runPeriodAtLevel(Name sper, Index ilev);

  // Return the run period  at a given level for a run.
  // Level 0 is the Iceberg run: 3, 4, 5, ...
  // Level 1 gives CE config, e.g. 5C22
  // Level 2 adds trigger/pulser/noise e.g. 5C22-cos
  // Level 3 adds more detail such as time period e.g. 5C22-cos2
  static Name runPeriod(unsigned int run, Index level =3);

  // Return the runs for a run period at any level.
  static IndexVector runPeriodRuns(Name sper);

  // TPC sampling rate in MHz.
  static double samplingRate(Index irun);

};

#endif
