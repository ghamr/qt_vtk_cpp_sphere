# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BallMover_autogen"
  "CMakeFiles/BallMover_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/BallMover_autogen.dir/ParseCache.txt"
  )
endif()
