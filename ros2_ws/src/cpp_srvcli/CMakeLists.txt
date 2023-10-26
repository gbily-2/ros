cmake_minimum_required(VERSION 3.5)
project(cpp_srvcli)

#add packages
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(geometry_msgs REQUIRED)

#add custom interfaces files
set(msg_files
"msg/Num.msg"
"msg/Sphere.msg"
)
set(srv_files
"srv/AddThreeInts.srv"
)
rosidl_generate_interfaces(${PROJECT_NAME}
  ${msg_files}
  ${srv_files}
  LIBRARY_NAME ${PROJECT_NAME}
  DEPENDENCIES geometry_msgs # Add packages that above messages depend on, in this case geometry_msgs for Sphere.msg
)

#add exe
add_executable(server src/add_two_ints_server.cpp)
ament_target_dependencies(server rclcpp example_interfaces)

add_executable(client src/add_two_ints_client.cpp)
ament_target_dependencies(client rclcpp example_interfaces)

# install targets
install(TARGETS
  server
  client
  DESTINATION lib/${PROJECT_NAME})

# link custom interfaces
rosidl_get_typesupport_target(cpp_typesupport_target
  ${PROJECT_NAME} rosidl_typesupport_cpp)
target_link_libraries(client  "${cpp_typesupport_target}")
target_link_libraries( server "${cpp_typesupport_target}")


ament_export_dependencies(rosidl_default_runtime)



ament_export_dependencies(rosidl_default_runtime)
ament_package()