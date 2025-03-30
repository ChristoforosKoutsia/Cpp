#include <functional>
#include <chrono>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <atomic>

#define MAX_THREADS 4

struct Job
{
    // jobs shall be a complex data type
    // where the datetime to be executed shall be writen also some sort of id
    int id;
    std::chrono::system_clock::time_point execution_time;
    std::function<void(void)> job_func;

    // constructor
    Job(std::function<void(void)> _job_func,std::chrono::system_clock::time_point _execution_time,int _id) :
    job_func(_job_func),
    id(_id),
    execution_time(_execution_time){};
    
};

struct pq_compare
{
    bool operator()(const Job& lhs, const Job& rhs) const
    {
        return lhs.execution_time > rhs.execution_time; // Note: Use '>' for min-heap behavior
    }
};

class JobManager{
public:
    JobManager();
    ~JobManager();
    void add_jobs(const std::function<void(void)>& job, const std::chrono::system_clock::time_point& time_point,int id);
private:
    std::thread thread_pool[MAX_THREADS]; // initialize the thread pool

    std::mutex _mtx;
    std::condition_variable cv_handle_job; // a condition variable which indicates whether there are jobs that could be assigned
                                           //a job can be handled if there is at least one job in the queue and there is a free thread to handle
                                           // it

    
    std::atomic_bool done;
    // the priority will have a pair of function and datetime and will sort it based the time
    // so we need to create a custom comparator
    std::priority_queue<Job , std::vector<Job> , pq_compare > pq_jobs;

    // function that is assigned to the threads
    void worker_thread();

    // function to indicate weather there are free jobs to run or the execution time has come
    bool should_run_job();


};