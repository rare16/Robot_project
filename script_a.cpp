#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

// Data we want to share between programs
struct SharedData {
    double left_rpm;
    double right_rpm;
    double linear_vel;
    double angular_vel;
    long timestamp;
};

SharedData* shared_memory = new SharedData();  // Global variable to share data

int main() {
    // Robot parameters
    double wheel_distance = 0.443;  // meters
    double wheel_diameter = 0.181;  // meters
    const int iterations = 10;       // Number of iterations
    std::ofstream output_file("shared_data.txt"); // Output file for RPM data

    if (!output_file.is_open()) {
        std::cerr << "Error opening file for writing." << std::endl;
        return 1; // Exit if the file cannot be opened
    }

    for (int i = 0; i < iterations; ++i) {
        // Simulating receiving cmd_vel data
        double linear_velocity = 0.5;   // Example linear velocity (m/s)
        double angular_velocity = 0.2;  // Example angular velocity (rad/s)
        
        // Calculate wheel RPMs
        double right_velocity = (2 * linear_velocity + angular_velocity * wheel_distance) / 2;
        double left_velocity = (2 * linear_velocity - angular_velocity * wheel_distance) / 2;
        
        double left_rpm = (left_velocity * 60) / (3.14159 * wheel_diameter);
        double right_rpm = (right_velocity * 60) / (3.14159 * wheel_diameter);
        
        // Store in shared memory
        shared_memory->left_rpm = left_rpm;
        shared_memory->right_rpm = right_rpm;
        shared_memory->linear_vel = linear_velocity;
        shared_memory->angular_vel = angular_velocity;
        shared_memory->timestamp = std::chrono::system_clock::now().time_since_epoch().count();
        
        // Output to console
        std::cout << "Calculated RPMs - Left: " << left_rpm << " Right: " << right_rpm << std::endl;

        // Save RPM data to the file
        output_file << "Calculated RPMs - Left: " << left_rpm << " Right: " << right_rpm << std::endl;

        std::this_thread::sleep_for(std::chrono::milliseconds(100));  // Wait 100ms
    }

    output_file.close(); // Close the file after writing
    std::cout << "RPM data saved to shared_data.txt" << std::endl;

    delete shared_memory; // Clean up allocated memory
    return 0;
}