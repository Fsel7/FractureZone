#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Manually inserted because paths are off!
get_filename_component(PARENT_DIR ${_IMPORT_PREFIX} DIRECTORY)
get_filename_component(GRANDPARENT_DIR ${PARENT_DIR} DIRECTORY)

message(_IMPORT_PREFIX=${_IMPORT_PREFIX})
message(GRANDPARENT_DIR=${GRANDPARENT_DIR})

# Import targets
set_property(TARGET sfml-system APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-system PROPERTIES
  IMPORTED_LOCATION_RELEASE "${GRANDPARENT_DIR}/sfml-system.framework/Versions/2.6.1/sfml-system"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-system.framework/Versions/2.6.1/sfml-system"
  )

set_property(TARGET sfml-window APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-window PROPERTIES
  IMPORTED_LOCATION_RELEASE "${GRANDPARENT_DIR}/sfml-window.framework/Versions/2.6.1/sfml-window"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-window.framework/Versions/2.6.1/sfml-window"
  )

set_property(TARGET sfml-network APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-network PROPERTIES
  IMPORTED_LOCATION_RELEASE "${GRANDPARENT_DIR}/sfml-network.framework/Versions/2.6.1/sfml-network"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-network.framework/Versions/2.6.1/sfml-network"
  )

set_property(TARGET sfml-graphics APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-graphics PROPERTIES
  IMPORTED_LOCATION_RELEASE "${GRANDPARENT_DIR}/sfml-graphics.framework/Versions/2.6.1/sfml-graphics"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-graphics.framework/Versions/2.6.1/sfml-graphics"
  )

set_property(TARGET sfml-audio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-audio PROPERTIES
  IMPORTED_LOCATION_RELEASE "${GRANDPARENT_DIR}/sfml-audio.framework/Versions/2.6.1/sfml-audio"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-audio.framework/Versions/2.6.1/sfml-audio"
  )

list(APPEND _cmake_import_check_files_for_sfml-system "${GRANDPARENT_DIR}/sfml-system.framework/Versions/2.6.1/sfml-system" )
list(APPEND _cmake_import_check_files_for_sfml-window "${GRANDPARENT_DIR}/sfml-window.framework/Versions/2.6.1/sfml-window" )
list(APPEND _cmake_import_check_files_for_sfml-network "${GRANDPARENT_DIR}/sfml-network.framework/Versions/2.6.1/sfml-network" )
list(APPEND _cmake_import_check_files_for_sfml-graphics "${GRANDPARENT_DIR}/sfml-graphics.framework/Versions/2.6.1/sfml-graphics" )
list(APPEND _cmake_import_check_files_for_sfml-audio "${GRANDPARENT_DIR}/sfml-audio.framework/Versions/2.6.1/sfml-audio" )

list(APPEND _cmake_import_check_targets sfml-system )
list(APPEND _cmake_import_check_targets sfml-window )
list(APPEND _cmake_import_check_targets sfml-network )
list(APPEND _cmake_import_check_targets sfml-graphics )
list(APPEND _cmake_import_check_targets sfml-audio )

message(_cmake_import_check_files_for_sfml-system="${_cmake_import_check_files_for_sfml-system}")
message(_cmake_import_check_files_for_sfml-window="${_cmake_import_check_files_for_sfml-window}")
message(_cmake_import_check_files_for_sfml-network="${_cmake_import_check_files_for_sfml-network}")
message(_cmake_import_check_files_for_sfml-graphics="${_cmake_import_check_files_for_sfml-graphics}")
message(_cmake_import_check_files_for_sfml-audio="${_cmake_import_check_files_for_sfml-audio}")

message(IMPORTED_SONAME_RELEASE="${_cmake_import_check_targets}")

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
