find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(../demo)
add_executable(runTests tests.cpp)

target_link_libraries(runTests lib ${GTEST_LIBRARIES} gmock pthread)
