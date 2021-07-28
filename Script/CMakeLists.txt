# duneproc/Script/CMakeLists.txt

# Install shell scripts.
install(PROGRAMS
  duneprocHelp
  duneproc
  formatInt
  runjobs
  savedqmapa7
  savedqmw
  savedqm2
  savedqm3
  findFilePnfs
  findFileXroot
  ibFindFiles
  ibGroupRuns
  ibStageFiles
  obsolete-ibRunPeriod
  ibDaqConfig
  ibSaveWfRaw
  ibSavePeds
  savedqmi
  showMetadata
  pdspRunFileCount
  pdspRunLfn
  pdspShowMetadata
  pdspDataStream
  pdspStartTime
  pdspWibCount
DESTINATION bin)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Build setup file for this package.
string(TOUPPER ${PROJECT_NAME} PROJECT_UPNAME)
configure_file(setup.sh.in setup.sh)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/setup.sh DESTINATION .)
