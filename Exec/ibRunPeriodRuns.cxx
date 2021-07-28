#include <iostream>
#include <string>
#include <vector>
#include "../Utility/IcebergHelper.h"

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stoi;
using Index = unsigned int;
using IndexVector = std::vector<Index>;

int main(int narg, char** argv) {
  const string myname = "ibRunPeriodRuns: ";
  if ( narg < 2 || argv[1] == "-h" ) {
    cout << "Usage: " << argv[0] << " RUNPERIOD" << endl;
    return 0;
  }
  string sper = argv[1];
  IndexVector runs = IcebergHelper::runPeriodRuns(sper);
  if ( runs.size() == 0 ) {
    cerr << myname << "No runs found for period " << sper << endl;
    return 1;
  }
  //cout << myname << "Finding runs for period " << sper << endl;
  for ( Index irun : runs ) cout << irun << endl;
  return 0;
}
