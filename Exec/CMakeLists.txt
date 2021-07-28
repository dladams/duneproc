# myproj/Exec/CMakeLists.txt

# Build executables.
foreach(NAME ibRunPeriod ibRunPeriodRuns)
  add_executable(${NAME} ${NAME}.cxx)
  target_link_libraries(${NAME} ${PROJECT_NAME})
  install(TARGETS ${NAME} DESTINATION bin)
endforeach()
