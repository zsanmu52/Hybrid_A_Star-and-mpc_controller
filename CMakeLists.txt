cmake_minimum_required(VERSION 3.10)
project(hybrid_a_star_zm0612)

message(STATUS "Hybrid A star")
message(STATUS "Author: Zhang Zhimeng")

#set(CMAKE_VERBOSE_MAKEFILE "true")

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
set(CMAKE_BUILD_TYPE "Release")

# Eigen
include(cmake/FindEigen.cmake)
include_directories(${EIGEN_INCLUDE_DIR})

# glog
include(cmake/glog.cmake)
include_directories(${GLOG_INCLUDE_DIRS})

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(nav_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(visualization_msgs REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(tf2_geometry_msgs REQUIRED)
find_package(OpenCV 4.7.0 REQUIRED EXACT)

include_directories(
    include
    ${OpenCV_INCLUDE_DIRS}
)

add_library(
    PATH_SEARCHER_LIB SHARED
    src/rs_path.cpp
    src/costmap_subscriber.cpp
    src/goal_pose_subscriber.cpp
    src/init_pose_subscriber.cpp
    src/hybrid_a_star.cpp
    src/hybrid_a_star_flow.cpp
    src/dubins.cpp
    src/dynamicvoronoi.cpp
    src/bucketedqueue.cpp
    src/smoother.cpp
)

ament_target_dependencies(
    PATH_SEARCHER_LIB
    rclcpp
    nav_msgs
    geometry_msgs
    sensor_msgs
    visualization_msgs
    tf2
    tf2_ros
    tf2_geometry_msgs
)

target_link_libraries(
    PATH_SEARCHER_LIB
    ${GLOG_LIBRARIES}
    ${OpenCV_LIBS}
)

add_executable(hybrid_a_star_zm0612 app/hybrid_a_star_zm0612.cpp)
target_link_libraries(hybrid_a_star_zm0612 PATH_SEARCHER_LIB)

ament_target_dependencies(
    hybrid_a_star_zm0612
    rclcpp
)

install(TARGETS
    PATH_SEARCHER_LIB
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

install(TARGETS
    hybrid_a_star_zm0612
    DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
    launch
    maps
    rviz
    DESTINATION share/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
