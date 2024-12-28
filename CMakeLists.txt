cmake_minimum_required(VERSION 3.26)
project(FractureZone LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

if(WIN32)
  set(OS "windows")
elseif(APPLE)
  set(OS "mac")
elseif(UNIX)
  set(OS "linux")
endif()

set(SFML_SOURCE_DIR ${PROJECT_SOURCE_DIR}/external/SFML/${OS})
if(APPLE)
  list(APPEND CMAKE_PREFIX_PATH ${SFML_SOURCE_DIR}/Frameworks/SFML.framework/Versions/2.6.1/Resources/CMake)
else()
  list(APPEND CMAKE_PREFIX_PATH ${SFML_SOURCE_DIR}/lib/cmake/SFML)
endif()

find_package(SFML 2.6.1 COMPONENTS graphics audio network system window REQUIRED)

set(TINYXML_SOURCE_DIR ${PROJECT_SOURCE_DIR}/external/tinyxml2)
list(APPEND CMAKE_PREFIX_PATH ${TINYXML_SOURCE_DIR}/cmake)

set(SIMPLEINI_SOURCE_DIR ${PROJECT_SOURCE_DIR}/external/simpleini)
list(APPEND CMAKE_PREFIX_PATH ${SIMPLEINI_SOURCE_DIR}/cmake)

# Setup dependencies
include_directories(include)
include_directories(src)

if(APPLE)
  set(CMAKE_MACOSX_RPATH 1)
  set(SFML_ROOT ${SFML_SOURCE_DIR})
  # find_library(SFML_AUDIO    sfml-audio    HINTS ${SFML_SOURCE_DIR}/Frameworks/sfml-audio.framework/Versions/2.6.1)
  # find_library(SFML_GRAPHICS sfml-graphics HINTS ${SFML_SOURCE_DIR}/Frameworks/sfml-graphics.framework/Versions/2.6.1)
  # find_library(SFML_SYSTEM   sfml-system   HINTS ${SFML_SOURCE_DIR}/Frameworks/sfml-system.framework/Versions/2.6.1)
  # find_library(SFML_WINDOW   sfml-window   HINTS ${SFML_SOURCE_DIR}/Frameworks/sfml-window.framework/Versions/2.6.1)
endif()

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "src/**/*.cpp"
    "src/**/*.hpp"
    "include/*.hpp"
    "external/tinyxml2/tinyxml2.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${TINYXML_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${SIMPLEINI_SOURCE_DIR})
# if(APPLE)
#   target_link_libraries(${PROJECT_NAME} ${SFML_GRAPHICS} ${SFML_AUDIO} ${SFML_WINDOW} ${SFML_SYSTEM})
# else()
  target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-window sfml-system)
# endif()

if(MSVC)
  target_compile_options(${PROJECT_NAME} PRIVATE /W3 /WX)
else()
  target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_custom_command(
    TARGET ${PROJECT_NAME}
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

if(WIN32)
  add_custom_command(
    TARGET  ${PROJECT_NAME}
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${SFML_SOURCE_DIR}/bin $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
elseif(APPLE)
  add_custom_command(
    TARGET  ${PROJECT_NAME}
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${SFML_SOURCE_DIR}/lib $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
elseif(UNIX)
  add_custom_command(
    TARGET  ${PROJECT_NAME}
    POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${SFML_SOURCE_DIR}/lib $<TARGET_FILE_DIR:${PROJECT_NAME}>
  )
endif()

