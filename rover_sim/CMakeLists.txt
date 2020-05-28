project(rover_sim)
cmake_minimum_required(VERSION 2.8)

find_package(catkin_simple REQUIRED)
catkin_simple(ALL_DEPS_REQUIRED)

cs_add_executable(velcontroller src/velocitycontrol.cpp)


cs_install()
cs_export()

