#include "JobSystem/JobQueue.h"
#include "JobSystem/JobTypes.h"

#include <atomic>
#include <condition_variable>
#include <cstdlib>
#include <thread>
#include <mutex>

#include <iostream>



void JobQueue::ProcessAllJobs(int threads)
{
    total_jobs = job_queue.size();

    std::cout << "Starting " << threads << " worker thread" << (threads > 1 ? "s" : "") <<std::endl;
    std::cout << "\rCompleted " << job_completed_count << " of " << total_jobs<<" jobs" << std::flush;
    while(threads > 0)
    {
        worker_threads.emplace(worker_threads.end(), &JobQueue::WorkerThread, this);
        --threads;
    }

    workers_cv.notify_all();

    while(!job_queue.empty()){
        // Wait for all jobs to complete
    }

    workers_exit = true;

    workers_cv.notify_all();
    for(auto it = worker_threads.begin(); it != worker_threads.end(); ++it)
    {
        it->join();
    }

    std::cout<<std::endl;
}

void JobQueue::UpdateProgress()
{
    log_mu.lock();
    std::cout << "\rCompleted " << job_completed_count << " of " << total_jobs<<" jobs" << std::flush;
    log_mu.unlock();
}


void JobQueue::WorkerThread()
{
    std::unique_lock<std::mutex> queue_lock (job_queue_mu);

    while(!workers_exit)
    {
        workers_cv.wait(queue_lock, [this] { return !job_queue.empty() || workers_exit; });

        if (!job_queue.empty() && !workers_exit)
        {
            Job job = std::move(job_queue.front());
            job_queue.pop();

            queue_lock.unlock();

            job();

            ++job_completed_count;

            UpdateProgress();

            queue_lock.lock();
        }

    }
}