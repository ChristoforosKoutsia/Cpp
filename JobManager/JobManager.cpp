#include "JobManager.hpp"
#include "Logger.hpp"
#include <sstream>

// the job of the constructor is 
JobManager::JobManager() : done(false)
{
    Logger::getInstance().log("JobManager: Initializing...");

    for (int i = 0; i < MAX_THREADS; ++i)
    {
        // spawn threads
        thread_pool[i] = std::thread(&JobManager::worker_thread, this);
        Logger::getInstance().log("JobManager: Thread " + std::to_string(i) + " started.");
    }
}

JobManager::~JobManager()
{
    Logger::getInstance().log("JobManager: Shutting down...");

    done = true;
    cv_handle_job.notify_all();

    // wait for all threads to finish their task
    for (unsigned long i = 0; i < MAX_THREADS; ++i)
    {
        if (thread_pool[i].joinable())
        {
            thread_pool[i].join();
            Logger::getInstance().log("JobManager: Thread " + std::to_string(i) + " joined.");
        }
    }
}

bool JobManager::should_run_job()
{
    return (!pq_jobs.empty() && pq_jobs.top().execution_time <= std::chrono::system_clock::now());
}

void JobManager::add_jobs(const std::function<void(void)>& job, const std::chrono::system_clock::time_point& time_point,int id)
{
    Logger::getInstance().log("JobManager: Adding job...");

    // acquire the lock 
    std::lock_guard<std::mutex> lock(_mtx);
    pq_jobs.push(Job(job, time_point,id));
    cv_handle_job.notify_one();

    Logger::getInstance().log("JobManager: Job added.");
}

void JobManager::worker_thread()
{
    Logger::getInstance().log("JobManager: Worker thread started.");

    // the threads as soon as they enter here they are in a loop that checks
    // all the time whether there is job to do or not

    while (!done)
    {
        // acquire the lock just because we gonna use the shared resource ( the jobs queue)
        std::unique_lock<std::mutex> lock(_mtx);

        // if there are no jobs to be assigned do a conditional wait either because there are no free threads
        // or because there are no jobs to be executed
        if (pq_jobs.empty())
        {
            // do a wait and give release the lock
            Logger::getInstance().log("JobManager: No jobs available, waiting...");
            cv_handle_job.wait(lock); // wait indefinitely
        }
        else if (pq_jobs.top().execution_time > std::chrono::system_clock::now())
        {
            Logger::getInstance().log("JobManager: Waiting until job execution time...");
            cv_handle_job.wait_until(lock, pq_jobs.top().execution_time);
        }
        else
        {
            // assign the job to this thread
            Job current_job = pq_jobs.top();
            pq_jobs.pop(); // remove it from the queue
            auto id = std::this_thread::get_id();
            std::stringstream ss;
            ss << id;
            Logger::getInstance().log("JobManager Thread with id " + ss.str() + ": Executing job...");

            lock.unlock(); // unlock the mutex before executing the job
            current_job.job_func(); // execute the job

            Logger::getInstance().log("JobManager: Job executed.");
        }
    }

    Logger::getInstance().log("JobManager: Worker thread exiting.");
}



