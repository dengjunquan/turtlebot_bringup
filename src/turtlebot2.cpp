#include <iostream>
#include <chrono>

#include <libkobuki.h>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <geometry_msgs/msg/twist.hpp>

using namespace rt_net;
using namespace std;

class Turtlebot : public rclcpp::Node {
	public : Turtlebot()
		 : Node("Turtlebot") {
			// Kobuki Device
			// const char *DeviceSpecial = "/dev/ttyUSB1";
			// Kobuki *kobuki = createKobuki(KobukiStringArgument(DeviceSpecial));

			// Velocity
			auto _cmd_vel = this->create_subscription<geometry_msgs::msg::Twist>("cmd_vel",
					[this](geometry_msgs::msg::Twist::SharedPtr msg){
					this->controleVelocity(msg);
					});
		 };

	private:
		 float velocity_x;
		 float velocity_y;
		 rclcpp::Subscription<geometry_msgs::msg::Twist>::SharedPtr _cmd_vel;

		 void controleVelocity(geometry_msgs::msg::Twist::SharedPtr msg) {
			 velocity_x = msg->linear.x;
			 velocity_y = msg->angular.z;

			 cout << velocity_x << endl;
		 }
};


int main(int argc, char *argv[]) {
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<Turtlebot>());
	rclcpp::shutdown();

	return 0;
}
