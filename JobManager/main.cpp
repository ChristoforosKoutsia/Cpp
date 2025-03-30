#include <iostream>
#include <functional>
#include <chrono>
#include <thread>
#include "JobManager.hpp" // Make sure to include the JobManager header
#include "Logger.hpp"

void taskx(int x)
{
    Logger::getInstance().log("task: Executing task " + std::to_string(x));
    std::this_thread::sleep_for(std::chrono::seconds(10));
    Logger::getInstance().log("task: Task " + std::to_string(x) + " completed.");
}

int main()
{
    Logger::getInstance().log("main: Starting JobManager...");

    JobManager jobManager;

    // Add the job to the JobManager
    for (int i = 0; i < 150; ++i)
    {
        auto bound_task = std::bind(taskx, i);
        auto execution_time = std::chrono::system_clock::now();
        jobManager.add_jobs(bound_task, execution_time,i);
    }
    
    auto bound_task = std::bind(taskx, 1000);
    auto execution_time = std::chrono::system_clock::now() - std::chrono::seconds(15);
    jobManager.add_jobs(bound_task, execution_time,1000);

    // Keep the main thread alive for demonstration purposes
    std::this_thread::sleep_for(std::chrono::seconds(100));

    Logger::getInstance().log("main: JobManager execution completed.");
    return 0;
}