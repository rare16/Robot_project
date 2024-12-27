#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <string>
#include <atomic>


struct SharedData {
    std::atomic<double> left_rpm;
    std::atomic<double> right_rpm;
    std::atomic<double> linear_velocity;
    std::atomic<double> angular_velocity;
    std::atomic<long> timestamp;
};

// Declare the shared data variable
extern SharedData shared_data;

// Function declarations
void saveVelocityData(const std::string& filename, double velocity);
void saveRPMData(const std::string& filename, double leftRPM, double rightRPM);

#endif // SHARED_DATA_H