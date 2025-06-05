#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <ctime>
#include <mutex>
using namespace std;

enum class ScheduleType {
    HOURLY,
    DAILY,
    WEEKLY
};

struct Job {
    ScheduleType type;
    int minute;         
    int hour;          
    int dayOfWeek;    
    string name;   
};

mutex coutMutex;

void runJob(const Job& job) {
    lock_guard<mutex> lock(coutMutex);
    cout << "[Job: " << job.name << "] Hello World at " << time(nullptr) << "\n";
}

bool shouldRunNow(const Job& job, const tm& timeinfo) {
    switch (job.type) {
        case ScheduleType::HOURLY:
            return timeinfo.tm_min == job.minute;
        case ScheduleType::DAILY:
            return timeinfo.tm_hour == job.hour && timeinfo.tm_min == job.minute;
        case ScheduleType::WEEKLY:
            return timeinfo.tm_wday == job.dayOfWeek &&
                   timeinfo.tm_hour == job.hour &&
                   timeinfo.tm_min == job.minute;
        default:
            return false;
    }
}

void schedulerLoop(vector<Job> jobs) {
    vector<bool> executed(jobs.size(), false);

    while (true) {
        auto now = chrono::system_clock::now();
        time_t tt = chrono::system_clock::to_time_t(now);
        tm timeinfo = *localtime(&tt);

        for (int i = 0; i < jobs.size(); ++i) {
            const Job& job = jobs[i];
            if (shouldRunNow(job, timeinfo)) {
                if (!executed[i]) {
                    runJob(job);
                    executed[i] = true;
                }
            } else {
                executed[i] = false;
            }
        }

       this_thread::sleep_for(chrono::seconds(30)); 
    }
}

int main() {
    vector<Job> jobList = {
        { ScheduleType::HOURLY, 0, 0, 0, "Job1" },          
        { ScheduleType::DAILY, 15, 14, 0, "Job2" },         
        { ScheduleType::WEEKLY, 30, 10, 1, "Job3" }         
    };

    cout << "Scheduler started...\n";
    schedulerLoop(jobList);

    return 0;
}
