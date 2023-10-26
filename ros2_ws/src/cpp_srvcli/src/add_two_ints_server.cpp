#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
#include "cpp_srvcli/srv/add_three_ints.hpp"

#include <memory>

void add(const std::shared_ptr<cpp_srvcli::srv::AddThreeInts::Request> request,
          std::shared_ptr<cpp_srvcli::srv::AddThreeInts::Response>      response)
{
  response->sum = request->a + request->b;
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Incoming request\na: %ld" " b: %ld",
                request->a, request->b);
  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "sending back response: [%ld]", (long int)response->sum);
}

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("add_three_ints_server");

  rclcpp::Service<cpp_srvcli::srv::AddThreeInts>::SharedPtr service =
    node->create_service<cpp_srvcli::srv::AddThreeInts>("add_three_ints", &add);

  RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Ready to add two ints.");

  rclcpp::spin(node);
  rclcpp::shutdown();
}