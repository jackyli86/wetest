cmake_minimum_required(VERSION 3.23)

project(weconsole VERSION 1.0)

file( GLOB_RECURSE PROTOBUF_FILES  "*.pb.h" "*.pb.cc")
file( GLOB_RECURSE CLASS_FILES  "class_*.h" "class_*.cpp")
file( GLOB_RECURSE TEST_FILES  "test_*.cpp")

# filter
source_group("src/proto" FILES ${PROTOBUF_FILES})
source_group("src/class" FILES ${CLASS_FILES})
source_group("src/test" FILES ${TEST_FILES})

# root filter
source_group("" FILES main.cpp common.h stdafx.cpp stdafx.h)

add_executable(we_test ${CPP_FILES} ${PROTOBUF_FILES} ${CLASS_FILES} ${TEST_FILES} main.cpp common.h stdafx.cpp stdafx.h)

target_include_directories(we_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../3rd/include")
target_link_directories(we_test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../3rd/libs/${CMAKE_BUILD_TYPE}/")
target_link_libraries(we_test gtest.lib gmock.lib libprotobuf.lib)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")