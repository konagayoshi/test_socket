set( TARGET test_server )

set( SOCKET_SRC_DIR ../common/src )

cmake_minimum_required( VERSION 2.8 )
project(ProjectName)

include_directories( ${SOCKET_SRC_DIR} src )
link_directories( )

file( GLOB SRCS src/*.cpp )

# to enable debug mode (!!Note: Clean build directory before changing mode)
#  > cmake -Ddebug=1 ..
if( debug )
  set( CMAKE_BUILD_TYPE Debug )
else()
  set( CMAKE_BUILD_TYPE Release )
endif()

set( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -DNDEBUG -march=native" )
set( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3" )

add_executable( ${TARGET} ${SRCS} ${SOCKET_SRC_DIR}/comm_socket.cpp )
target_link_libraries( ${TARGET} pthread )
