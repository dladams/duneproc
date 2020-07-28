#include "IcebergHelper.h"

#include <iostream>

using std::cout;
using std::endl;

void IcebergHelper::help() {
  cout << "IcebergHelper provides: " << endl;
  cout << "  detectorRun(run): Returns the run period for a run." << endl;
  cout << "  isOdd(chan): Returns true if a channel is odd." << endl;
  cout << "               Odd means odd in v and z1 and even in u and z2." << endl;
}
