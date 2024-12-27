#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include "httplib.h" // Make sure this path is correct
#include "shared_data.h" // Ensure this header defines shared_data

// Function to simulate fetching and printing shared data
void fetch_and_print_data() {
    while (true) {
        std::cout << "Left RPM: " << shared_data.left_rpm.load() << std::endl;
        std::cout << "Right RPM: " << shared_data.right_rpm.load() << std::endl;
        std::cout << "Linear Velocity: " << shared_data.linear_velocity.load() << std::endl;
        std::cout << "Angular Velocity: " << shared_data.angular_velocity.load() << std::endl;
        std::cout << "Timestamp: " << shared_data.timestamp.load() << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // Print every second
    }
}

// Function to start the HTTP server
void start_http_server() {
    httplib::Server svr;

    svr.Get("/get_data", [](const httplib::Request &, httplib::Response &res) {
        std::string json_response = "{";
        json_response += "\"left_rpm\":" + std::to_string(shared_data.left_rpm.load()) + ",";
        json_response += "\"right_rpm\":" + std::to_string(shared_data.right_rpm.load()) + ",";
        json_response += "\"linear_velocity\":" + std::to_string(shared_data.linear_velocity.load()) + ",";
        json_response += "\"angular_velocity\":" + std::to_string(shared_data.angular_velocity.load()) + ",";
        json_response += "\"timestamp\":" + std::to_string(shared_data.timestamp.load());
        json_response += "}";
        res.set_content(json_response, "application/json");
    });

    svr.listen("localhost", 8080); // Listen on localhost:8080
}

int main() {
    // Start the data fetching thread
    std::thread fetch_thread(fetch_and_print_data);
    fetch_thread.detach(); // Detach the thread to run independently

    // Start the HTTP server
    start_http_server();

    return 0;
}
