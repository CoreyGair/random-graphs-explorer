#pragma once

#include "JobSystem/JobTypes.h"

#include <atomic>
#include <vector>
#include <queue>
#include <condition_variable>
#include <thread>
#include <mutex>

class Graph;

class JobQueue
{
    public:
        JobQueue() : workers_exit(false) {}
        void EnqueueJob(Job j) { job_queue.push(j); }
        void ProcessAllJobs(int threads);

    private:
        std::queue<Job> job_queue;
        std::mutex job_queue_mu;
        std::atomic_int job_completed_count;

        std::vector<std::thread> worker_threads;
        std::atomic_bool workers_exit;
        std::condition_variable workers_cv;

        void UpdateProgress();
        int total_jobs;
        std::mutex log_mu;

        void WorkerThread();
};