#include "IcebergHelper.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "TSystem.h"

using std::string;
using std::cout;
using std::endl;
using std::map;
using std::vector;
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

std::vector<string> IcebergHelper::runPeriodContainers(string speri) {
  vector<string> spers;
  string spero = speri;
  while ( spero.size() > 1 ) {
    string::size_type len = spero.size();
    string::size_type ipos = spero.find("-");
    if ( ipos != string::npos ) {
      if ( std::isdigit(spero[len-1]) ) {
        spero = spero.substr(0, len-1);
      } else {
        spero = spero.substr(0, ipos);
      }
    } else {
      spero = spero.substr(0, 1);
    }
    spers.push_back(spero);
  }
  return spers;
}

string IcebergHelper::runPeriodAtLevel(string speri, Index ilev) {
  vector<string> scons = runPeriodContainers(speri);
  Index ncon = scons.size();
  if ( ilev > ncon ) return "";
  if ( ilev == ncon ) return speri;
  return scons[ncon - ilev - 1];
}

std::string IcebergHelper::runPeriod(unsigned int run, Index level) {
  if ( level < 3 ) {
    string sper3 = runPeriod(run, 3);
    if ( sper3.size() == 0 ) return "";
    if ( level == 0 ) return sper3.substr(0,1);  // Fix this if we reach run 10
    Index ipos = sper3.find("-");
    if ( level == 1 ) return sper3.substr(0, ipos);
    if ( ipos != string::npos ) {
      string::size_type len = sper3.size();
      if ( std::isdigit(sper3[len-1]) ) return sper3.substr(0, len-1);
    }
    return sper3;
  }
  // Level 3 reponses follow.
  if ( run < 5360 ) return "3";
  if ( run < 6100 ) return "4a";
  if ( run < 8002 ) return "4b";
  if ( run < 8249 ) return "test";
  if ( run < 8409 ) return "5a";
  if ( run < 8216 ) return "test";
  if ( run < 8432 ) return "5b";
  if ( run < 8453 ) return "5c";
  if ( run < 8474 ) return "5d";
  if ( run < 8620 ) return "5c";
  if ( run < 8630 ) return "5d";
  if ( run < 8635 ) return "5c";
  if ( run < 8639 ) return "5e";
  if ( run < 8640 ) return "5c";
  if ( run < 8645 ) return "5e";
  if ( run < 8646 ) return "5c";
  if ( run < 8655 ) return "5d";
  if ( run < 8658 ) return "5c";
  if ( run < 8662 ) return "5e";
  if ( run < 8663 ) return "5d";
  if ( run < 8670 ) return "5e";
  if ( run < 8671 ) return "5c";
  if ( run < 8677 ) return "5e";
  if ( run < 8680 ) return "5c";
  if ( run < 8820 ) return "5f";
  if ( run < 8826 ) return "5g";
  if ( run < 8832 ) return "5h";
  if ( run < 8838 ) return "5i";
  if ( run < 8844 ) return "5f";
  if ( run < 8850 ) return "5d";
  if ( run < 8856 ) return "5j";
  if ( run < 8862 ) return "5e";
  if ( run < 8868 ) return "5f";
  if ( run < 8874 ) return "5k";
  if ( run < 8880 ) return "5l";
  if ( run < 8886 ) return "5m";
  if ( run < 8892 ) return "5n";
  if ( run < 8898 ) return "5o";
  if ( run < 8951 ) return "5f";
  if ( run < 9048 ) return "5p";
  if ( run < 9050 ) return "5f";
  if ( run < 9074 ) return "5p";
  if ( run < 9105 ) return "5q";
  if ( run < 9113 ) return "5p";
  if ( run < 9143 ) return "test";
  if ( run < 9158 ) return "5C22-pul1";
  if ( run < 9168 ) return "5C21-pul1";
  if ( run < 9179 ) return "5C22-cos1";
  if ( run < 9190 ) return "5C02-cos1";
  if ( run < 9201 ) return "5C12-cos1";
  if ( run < 9212 ) return "5C32-cos1";
  if ( run < 9223 ) return "5C22-cos2";
  if ( run < 9234 ) return "5C21-cos1";
  if ( run < 9245 ) return "5C20-cos1";
  if ( run < 9256 ) return "5C23-cos1";
  if ( run < 9267 ) return "5C22-cos3";
  if ( run < 9278 ) return "5C22l-cos1";
  if ( run < 9289 ) return "5C31-cos1";
  if ( run < 9300 ) return "5C33-cos1";
  if ( run < 9311 ) return "5C11-cos1";
  if ( run < 9322 ) return "5C13-cos1";
  if ( run == 9322 ) return "test";
  if ( run < 9338 ) return "5C22-pul2";
  if ( run < 9348 ) return "5C21-pul2";
  if ( run < 9357 ) return "5C22-mix2";
  if ( run == 9357 ) return "none";
  if ( run < 9411 ) return "5C22-cos4";
  if ( run < 9431 ) return "5C22-test1";
  if ( run < 9436 ) return "5C01-cos1";
  if ( run < 9441 ) return "5C03-cos1";
  if ( run < 9446 ) return "5C02-cos2";
  if ( run < 9451 ) return "5C11-cos2";
  if ( run < 9456 ) return "5C13-cos2";
  if ( run < 9461 ) return "5C12-cos2";
  if ( run < 9466 ) return "5C21-cos2";
  if ( run < 9471 ) return "5C20-cos2";
  if ( run < 9476 ) return "5C23-cos2";
  if ( run < 9479 ) return "5C22-cos5";
  if ( run < 9488 ) return "5C22-test2";
  if ( run < 9491 ) return "5C33-test2";
  if ( run < 9496 ) return "5C22-test3";
  if ( run < 9507 ) return "empty";
  if ( run < 9518 ) return "5C22-pul3";
  if ( run < 9526 ) return "5C21-pul3";
  if ( run < 9537 ) return "5C02-pul1";
  if ( run < 9548 ) return "5C01-pul1";
  if ( run < 9559 ) return "5C12-pul1";
  if ( run < 9570 ) return "5C11-pul1";
  if ( run < 9580 ) return "5C23-pul1";
  if ( run < 9591 ) return "5C20-pul1";
  if ( run < 9602 ) return "5C31-pul1";
  if ( run < 9613 ) return "5C32-pul1";
  if ( run < 9683 ) return "5C22-cos6";
  if ( run < 9692 ) return "test";
  if ( run < 9712 ) return "5C22-ar39";
  if ( run < 9714 ) return "5C22-mix2";
  if ( run < 9717 ) return "5C01-cos2";
  if ( run < 9719 ) return "5C03-cos2";
  if ( run < 9721 ) return "5C02-cos3";
  if ( run < 9723 ) return "5C11-cos3";
  if ( run < 9725 ) return "5C13-cos3";
  if ( run < 9727 ) return "5C12-cos3";
  if ( run < 9729 ) return "5C21-cos3";
  if ( run < 9731 ) return "5C20-cos3";
  if ( run < 9733 ) return "5C23-cos3";
  if ( run < 9744 ) return "5C22-cos7";
  if ( run < 9738 ) return "5C22-cos7";
  if ( run < 9744 ) return "5C22-cos7";
  if ( run < 9744 ) return "5C22-test4";
  return "end";
}

vector<unsigned int> IcebergHelper::runPeriodRuns(string sperIn) {
  //const string myname = "IcebergHelper::runPeriodRuns: ";
  static std::map<Name, IndexVector> runs;
  if ( runs.size() == 0 ) {
    for ( Index irun=5000; irun<100000; ++irun )  {
      Name sper = runPeriod(irun, 3);
      if ( sper == "end" ) break;
      runs[sper].push_back(irun);
      NameVector scons = runPeriodContainers(sper);
      for ( Name scon : scons ) runs[scon].push_back(irun);
    }
  }
  runs["3test"] = {5010, 5011, 5012, 5013, 5014, 5015, 5016, 5017, 5018, 5019};
  runs["4test"] = {7100, 7101, 7102, 7103, 7104, 7105, 7106, 7107, 7108, 7109};
  runs["5test"] = {9650, 9651, 9652, 9653, 9654, 9655, 9656, 9657, 9658, 9659};

  return runs[sperIn];
}
 
double IcebergHelper::samplingRate(unsigned int run) {
  if ( run < 8430 ) return 2.0;
  return 62.5/32.0;
}
