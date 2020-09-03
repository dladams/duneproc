#include "IcebergHelper.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "TSystem.h"

using std::string;
using std::cout;
using std::endl;
using std::map;
using std::ifstream;
using std::istringstream;

void IcebergHelper::help() {
  cout << "IcebergHelper provides: " << endl;
  cout << "  detectorRun(run): Returns the run period for a run." << endl;
  cout << "  isOdd(chan): Returns true if a channel is odd." << endl;
  cout << "               Odd means odd in v and z1 and even in u and z2." << endl;
}

map<unsigned int, string>
IcebergHelper::runDates(unsigned int irun1, unsigned int irun2, int dbg) {
  const string myname = "IcebergHelper::runDates: ";
  map<unsigned int, string> rundates;
  string sdir = gSystem->Getenv("DUNEPROC_DIR");
  if ( sdir.size() == 0 ) {
    cout << "ERROR: Undefined package location DUNEPROC_DIR." << endl;
    return rundates;
  }
  string sfil = sdir + "/doc/ibRunDates.txt";
  ifstream fin(sfil.c_str());
  if ( ! fin ) {
    cout << myname << "File not found: " << sfil << endl;
    return rundates;
  }
  string sline;
  while ( getline(fin, sline) ) {
    if ( dbg >= 3 ) cout << myname << "Considering " << sline << endl;
    istringstream sin(sline);
    unsigned int irun = 0;
    sin >> irun;
    if ( irun == 0 ) continue;
    string sdat;
    sin >> sdat;
    if ( irun >= irun1 && irun < irun2 ) {
      rundates[irun] = sdat;
      if ( dbg >= 2 ) cout << myname << "Selected " << irun << ": " << sdat << endl;
    }
  }
  if ( dbg >= 1 ) cout << myname << "Selected run count is " << rundates.size() << endl;
  return rundates;
}
