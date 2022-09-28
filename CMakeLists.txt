cmake_minimum_required(VERSION 3.5)

project(dolly_ignition)

# Fortress
if("$ENV{IGNITION_VERSION}" STREQUAL "fortress")
  find_package(ignition-gazebo6 REQUIRED)

  message(STATUS "Using Ignition Fortress")
# Default to Edifice
else()
  find_package(ignition-gazebo5 QUIET)

  if(NOT ignition-gazebo5_FOUND)
    # Skip if Ignition not present
    message(WARNING "Ignition Gazebo 5 or 6 not found, proceeding without that simulator.")
    return()
  else()
    message(STATUS "Using Ignition Edifice")
  endif()
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)



add_executable(reading_laser src/publishers.cpp)
ament_target_dependencies(reading_laser rclcpp std_msgs sensor_msgs geometry_msgs)
add_executable(publisher src/simple.cpp)
ament_target_dependencies(publisher rclcpp std_msgs sensor_msgs)
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()
install(TARGETS
  publisher
  reading_laser
  DESTINATION lib/${PROJECT_NAME})
install(
  DIRECTORY
    ign
    launch
    config
    models
    rviz
    worlds
    #reading_laser
  DESTINATION
    share/${PROJECT_NAME}/
)

ament_environment_hooks("${CMAKE_CURRENT_SOURCE_DIR}/env-hooks/${PROJECT_NAME}.sh.in")
ament_environment_hooks("${CMAKE_CURRENT_SOURCE_DIR}/env-hooks/${PROJECT_NAME}.dsv.in")

ament_package()
