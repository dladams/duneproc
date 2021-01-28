// ibRunDates.C
//
// David Adams
// September 2020
//
// Return a map of date strings indexed by first run number in the range
// [irun1, irun2).
map<unsigned int, string> ibRunDates(unsigned int irun1, unsinged int irun2) {
  const string myname = "ibRunDates: ";
  map<unsigned int, string> rundates;
  string sdir = gSystem::Getenv("DUNEPROC_DIR");
  if ( sdir.size() == 0 ) {
    cout << "ERROR: Undefined package location DUNEPROC_DIR." << endl;
    return rundates;
  }
  string sfil = sdir + "/doc/ibRunDates.txt";
  ifstream fin(sfil.c_str());
  if ( ! fin ) {
    cout << myname << "File not found: " << sfil << endl;
    return;
  }
}
