#include <chrono> // Date and time
#include <functional> // Arithmetic, comparisons, and logical operations
#include <memory> // Dynamic memory management
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/laser_scan.hpp"
#include "std_msgs/msg/string.hpp"
#include <geometry_msgs/msg/twist.hpp>
//using std::placeholders::_1;
using namespace std::chrono_literals;
class ReadingLaser : public rclcpp::Node {

  public:
    ReadingLaser() : Node("reading_laser") {

      
      //auto sensor_qos = rclcpp::QoS(rclcpp::SensorDataQoS());
      //subscription_ = this->create_subscription("laser_scan", default_qos, std::bind(&ReadingLaser::topic_callback, this, _1));
      auto default_qos = rclcpp::QoS(rclcpp::SystemDefaultsQoS());
      cmd_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("cmd_vel", default_qos);
      timer_ = this->create_wall_timer(500ms, std::bind(&ReadingLaser::timer_callback, this));
      RCLCPP_INFO(this->get_logger(), "Hello");
      this->declare_parameter<std::string>("controller_name");
      this->declare_parameter<int>("time");
      this->declare_parameter<float>("lx");
      this->declare_parameter<float>("az");
      this->declare_parameter<bool>("bool");
      this->get_parameter("controller_name", parameter_string_);
      this->get_parameter("time", t);
      this->get_parameter("lx", goals1);
      this->get_parameter("az", goals2);
      this->get_parameter("bool", bool2);
      RCLCPP_INFO(this->get_logger(), "Hello %s", parameter_string_.c_str());
      RCLCPP_INFO(this->get_logger(), "Hello %d", t);
      RCLCPP_INFO(this->get_logger(), "Hello %f", goals1);
      

  }

  private:
    std::string parameter_string_;
    int t;
    float goals1;
    float goals2;
    bool bool2;
    void timer_callback() {
      if(bool2 == true){
        RCLCPP_INFO(this->get_logger(), "start driving");
        auto message = geometry_msgs::msg::Twist();
        message.linear.x = goals1;
        message.angular.z = 0;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%f.2' and %f.2",message.linear.x, message.angular.z);
        cmd_pub_->publish(message);
        std::this_thread::sleep_for(5s);
        message.linear.x = 0;
        message.angular.z = goals2;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%f.2' and %f.2",message.linear.x, message.angular.z);
        cmd_pub_->publish(message);
        std::this_thread::sleep_for(5s);
        message.angular.z = 0;
        message.linear.x = goals1;
        RCLCPP_INFO(this->get_logger(), "Publishing: '%f.2' and %f.2",message.linear.x, message.angular.z);
        cmd_pub_->publish(message);
        std::this_thread::sleep_for(5s);
      }
  }
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr cmd_pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    
};

int main(int argc, char *argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<ReadingLaser>());
  rclcpp::shutdown();
  return 0;
}
