#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Manually inserted because paths are off!
get_filename_component(PARENT_DIR ${_IMPORT_PREFIX} DIRECTORY)
get_filename_component(GRANDPARENT_DIR ${PARENT_DIR} DIRECTORY)
set(_IMPORT_PREFIX ${GRANDPARENT_DIR})

# Import targets
set_property(TARGET sfml-system APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-system PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/sfml-system.framework/Versions/2.6.1/sfml-system"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-system.framework/Versions/2.6.1/sfml-system"
  )

set_property(TARGET sfml-window APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-window PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/sfml-window.framework/Versions/2.6.1/sfml-window"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-window.framework/Versions/2.6.1/sfml-window"
  )

set_property(TARGET sfml-network APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-network PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/sfml-network.framework/Versions/2.6.1/sfml-network"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-network.framework/Versions/2.6.1/sfml-network"
  )

set_property(TARGET sfml-graphics APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-graphics PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/sfml-graphics.framework/Versions/2.6.1/sfml-graphics"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-graphics.framework/Versions/2.6.1/sfml-graphics"
  )

set_property(TARGET sfml-audio APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(sfml-audio PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/sfml-audio.framework/Versions/2.6.1/sfml-audio"
  IMPORTED_SONAME_RELEASE "@rpath/sfml-audio.framework/Versions/2.6.1/sfml-audio"
  )

list(APPEND _cmake_import_check_files_for_sfml-system "${_IMPORT_PREFIX}/sfml-system.framework/Versions/2.6.1/sfml-system" )
list(APPEND _cmake_import_check_files_for_sfml-window "${_IMPORT_PREFIX}/sfml-window.framework/Versions/2.6.1/sfml-window" )
list(APPEND _cmake_import_check_files_for_sfml-network "${_IMPORT_PREFIX}/sfml-network.framework/Versions/2.6.1/sfml-network" )
list(APPEND _cmake_import_check_files_for_sfml-graphics "${_IMPORT_PREFIX}/sfml-graphics.framework/Versions/2.6.1/sfml-graphics" )
list(APPEND _cmake_import_check_files_for_sfml-audio "${_IMPORT_PREFIX}/sfml-audio.framework/Versions/2.6.1/sfml-audio" )

list(APPEND _cmake_import_check_targets sfml-system )
list(APPEND _cmake_import_check_targets sfml-window )
list(APPEND _cmake_import_check_targets sfml-network )
list(APPEND _cmake_import_check_targets sfml-graphics )
list(APPEND _cmake_import_check_targets sfml-audio )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
