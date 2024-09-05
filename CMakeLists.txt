# cmake_minimum_required(VERSION 3.28)

cmake_minimum_required(VERSION 3.26)
project(VeryCoolGame LANGUAGES CXX)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(SFML_SOURCE_DIR ${PROJECT_SOURCE_DIR}/external/SFML)
list(APPEND CMAKE_PREFIX_PATH ${SFML_SOURCE_DIR}/lib/cmake)
find_package(SFML COMPONENTS graphics audio network system window REQUIRED)

# Setup dependencies
include_directories(src)

file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS
    "src/**/*.cpp"
    "include/*.hpp"
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

add_custom_command(
    TARGET ${PROJECT_NAME}
    PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/resources $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
)

if(WIN32)
    add_custom_command(
        TARGET ${PROJECT_NAME}
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/lib/openal32.lib $<TARGET_FILE_DIR:${PROJECT_NAME}>
        VERBATIM)
endif()

add_custom_command(
    TARGET  ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SFML_SOURCE_DIR}/bin"
    $<TARGET_FILE_DIR:${PROJECT_NAME}>
)
