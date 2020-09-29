#include <chrono>
#include <memory>
#include <iostream>
#include <sys/time.h>
#include <algorithm>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sched_deadline.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
std::vector<bool> sub_flag;

class LeafNode : public rclcpp::Node
{
	public:
		LeafNode()
		: Node("leaf_node")
		{
			parameter_init();
			subscriber_init();
		}
		
	private:
		void parameter_init()
		{
			// parameter setting ; default value is second parameter
			this->declare_parameter<int>("parent_num", 0);
			rclcpp::Parameter parent_num_param = this->get_parameter("parent_num");
			parent_num_ = parent_num_param.as_int();

			this->declare_parameter("parent_idx");
			rclcpp::Parameter parent_idx_param = this->get_parameter("parent_idx");
			parent_idx_ = parent_idx_param.as_integer_array();

			this->declare_parameter<int>("waste_time", 1000);
			rclcpp::Parameter waste_time_param = this->get_parameter("waste_time");
			waste_time_ = waste_time_param.as_int();

			for(int i=0; i<parent_num_; i++){
				sub_flag.push_back(false);
			}
		}

		void subscriber_init()
		{
			for(int i=0; i<parent_num_; i++){
				std::string topic_name = rclcpp::Node::get_name();
				topic_name = "topic_node" + std::to_string(parent_idx_.at(i)) + "_" + topic_name;
				
				std::function<void(const std_msgs::msg::String::SharedPtr msg)> fnc = std::bind(&LeafNode::topic_callback, this, _1, i);
				subscriber_list.push_back(this->create_subscription<std_msgs::msg::String>(topic_name.c_str(), 10, fnc));

			}
		}

		void topic_callback(const std_msgs::msg::String::SharedPtr msg, int topic_idx) const
		{
			std::cout << msg->data.c_str() << topic_idx << "\n";

			sub_flag.at(topic_idx) = true;

			if(find(sub_flag.begin(), sub_flag.end(), false) == sub_flag.end()){
				for(int i=0; i<parent_num_; i++){
					sub_flag.push_back(false);
				}
				waste_time();
			}
		}

		void waste_time() const
		{
			int tmp=0;
			auto start = std::chrono::high_resolution_clock::now();
			for(long long int i=0; i<582500 * waste_time_; i++){
				tmp = 1 - tmp;
			}
			auto finish = std::chrono::high_resolution_clock::now();
			
			std::chrono::duration<double> elapsed = finish - start;
			std::cout << "Elapsed time: " << elapsed.count() << "s\n";
		}

		int parent_num_;
		std::vector<long int> parent_idx_;
		int waste_time_;

		std::vector<rclcpp::Subscription<std_msgs::msg::String>::SharedPtr> subscriber_list;
};

int main(int argc, char * argv[])
{
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<LeafNode>());
	rclcpp::shutdown();
	
	return 0;
}
