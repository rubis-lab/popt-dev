#include <chrono>
#include <functional>
#include <memory>
#include <string>
#include <iostream>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sched_deadline.hpp"

using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
* member function as a callback from the timer. */

class EntryNode : public rclcpp::Node
{
	public:
		EntryNode()
		: Node("entry_node"), count_(0)
		{
			parameter_init();

			publisher_init();

			timer_ = this->create_wall_timer(2000ms, std::bind(&EntryNode::waste_time, this));
		}
		
	private:
		void parameter_init()
		{
			// parameter setting ; default value is second parameter
			this->declare_parameter<int>("child_num", 0);
			rclcpp::Parameter child_num_param = this->get_parameter("child_num");
			child_num_ = child_num_param.as_int();

			this->declare_parameter("child_idx");
			rclcpp::Parameter child_idx_param = this->get_parameter("child_idx");
			child_idx_ = child_idx_param.as_integer_array();

			this->declare_parameter<int>("waste_time", 1000);
			rclcpp::Parameter waste_time_param = this->get_parameter("waste_time");
			waste_time_ = waste_time_param.as_int();
		}

		void publisher_init()
		{
			for(int i=0; i<child_num_; i++){
				std::string topic_name = rclcpp::Node::get_name();
				topic_name = "topic_" + topic_name + "_node" + std::to_string(child_idx_.at(i));
				publisher_list.push_back(this->create_publisher<std_msgs::msg::String>(topic_name.c_str(), 10));
			}
		}

		void publish_message()
		{
			auto message = std_msgs::msg::String();
			message.data = "Entry Node Finished " + std::to_string(count_++);

			for(int i=0; i<child_num_; i++){
				publisher_list[i]->publish(message);
			}
		}

		void waste_time()
		{
			int tmp=0;
			auto start = std::chrono::high_resolution_clock::now();
			for(long long int i=0; i<582500 * waste_time_; i++){
				tmp = 1 - tmp;
			}
			auto finish = std::chrono::high_resolution_clock::now();
			
			std::chrono::duration<double> elapsed = finish - start;
			std::cout << "Elapsed time: " << elapsed.count() << "s\n";

			publish_message();
		}

		int child_num_;
		std::vector<long int> child_idx_;
		int waste_time_;

		rclcpp::TimerBase::SharedPtr timer_;
		std::vector<rclcpp::Publisher<std_msgs::msg::String>::SharedPtr> publisher_list;
		size_t count_;
};

int main(int argc, char * argv[])
{	
	/*
	int tid = gettid();
	unsigned int _tperiod = 10000000;
        unsigned int _tdeadline = 1000000;
        unsigned int _texec_time = 100000;
        set_sched_deadline(tid, _texec_time, _tdeadline, _tperiod);
	*/

	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<EntryNode>());
	rclcpp::shutdown();

    return 0;
}
