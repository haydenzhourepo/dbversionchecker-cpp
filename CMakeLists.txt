cmake_minimum_required(VERSION 3.0.0)
project(dbversionchecker VERSION 0.1.0)

set(CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED True)


add_library(dbversionchecker SQLServerChecker.cpp)

add_executable(checker_test dbVersionChecker_test.cpp)
target_link_libraries(checker_test dbversionchecker)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
