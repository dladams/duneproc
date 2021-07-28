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
  const string myname = "ibRunPeriod: ";
  Index ilev = 1;
  if ( narg < 2 || argv[1] == "-h" ) {
    cout << "Usage: " << argv[0] << " RUN [LEVEL]" << endl;
    return 0;
  }
  Index irun = std::atoi(argv[1]);
  if ( narg > 2 ) ilev = std::atoi(argv[2]);
  string sper = IcebergHelper::runPeriod(irun, ilev);
  cout << sper << endl;
  return 0;
}
