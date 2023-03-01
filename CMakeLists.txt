cmake_minimum_required(VERSION 3.0.0)
project(dbversionchecker VERSION 0.1.0)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED True)


add_library(dbversionchecker SQLServerChecker.cpp)
target_include_directories(dbversionchecker INTERFACE
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
$<INSTALL_INTERFACE:include>
)

add_executable(checker_test dbVersionChecker_test.cpp)
target_link_libraries(checker_test dbversionchecker)


install(TARGETS dbversionchecker
EXPORT dbversioncheckerTargets
DESTINATION lib)

install(FILES SQLServerChecker.h DESTINATION include)

install(EXPORT dbversioncheckerTargets
FILE dbversioncheckerTargets.cmake
DESTINATION lib/cmake/dbversionchecker
)

include(CMakePackageConfigHelpers)
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
"${CMAKE_CURRENT_BINARY_DIR}/dbversioncheckerConfig.cmake"
INSTALL_DESTINATION "lib/cmake/dbversionchecker"
NO_SET_AND_CHECK_MACRO
NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/dbversioncheckerConfigVersion.cmake"
  VERSION "${dbversionchecker_VERSION_MAJOR}.${dbversionchecker_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/dbversioncheckerConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/dbversioncheckerConfigVersion.cmake
  DESTINATION lib/cmake/dbversionchecker
  )