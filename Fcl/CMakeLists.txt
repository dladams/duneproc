# duneproc/Fcl/CMakeLists.txt

# Install fcl files.
install(
  DIRECTORY .
  DESTINATION fcl
  FILES_MATCHING PATTERN "*.fcl"
)

add_subdirectory(Protodune)
add_subdirectory(Iceberg)
