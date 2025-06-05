# 🕒 Job Scheduling System – C++ Implementation

## 📌 Overview

This project is a **basic job scheduling system** written in C++. It allows users to define jobs that execute based on a configured schedule — either **hourly**, **daily**, or **weekly**.

Each job, when triggered, performs a simple task:  
**Print "Hello World" to the console** along with the current timestamp and job name.

---

## 🚀 Features

- Supports three types of scheduling:
  - **Hourly** – Run at a specific minute every hour
  - **Daily** – Run at a specific time every day
  - **Weekly** – Run at a specific day and time every week
- Efficient polling with checks every 30 seconds
- Prevents repeated execution within the same minute
- Thread-safe console output using `std::mutex`
- Logs output in the format:


---

## 🛠️ Tech Stack

- **Language**: C++
- **Standard Libraries Used**:
- `<chrono>` – Time handling
- `<thread>` – Sleep between checks
- `<ctime>` – Time formatting
- `<mutex>` – Thread safety for console output

---

## 🧠 How It Works

1. **Job Structure**:  
 Each job is represented by a `Job` struct which includes:
 - `ScheduleType` (HOURLY, DAILY, WEEKLY)
 - Minute, Hour, Day (depending on schedule)
 - Name of the job

2. **Main Loop**:  
 The `schedulerLoop()` runs indefinitely, checking the current system time and matching it with each job's schedule.

3. **Execution Logic**:  
 `shouldRunNow()` determines whether a job should execute in the current minute. If yes, `runJob()` prints the output and marks it as executed to prevent duplicate triggers in the same minute.

---

## 🧪 How to Run the Code

### 1. **Save the code**
Save the provided C++ code in a file, for example: `JobScheduling.cpp`

### 2. **Compile the code and run the code**
Open terminal or command prompt and compile using:

for macos: clang++ -std=c++14 -stdlib=libc++ -I. JobScheduling.cpp -o JobScheduling && ./JobScheduling
For windows: g++ JobScheduling.cpp -o scheduler && ./JobScheduling

---

## Pre Configured Jobs in this code:
vector<Job> jobList = {
    { ScheduleType::HOURLY, 0, 0, 0, "Job1" },          // Runs every hour at minute 0  
    { ScheduleType::DAILY, 15, 14, 0, "Job2" },         // Runs daily at 2:15 PM  
    { ScheduleType::WEEKLY, 30, 10, 1, "Job3" }         // Runs weekly on Tuesday at 10:30 AM
};

## Assumptions
1. The system checks every 30 seconds, ensuring minimal delay but avoiding performance overhead.
2. Job actions are simulated by printing output. In a real system, this can be extended to run shell commands, update databases, or trigger APIs.
3. All jobs are hardcoded in the vector, but this can be extended with file or DB-based configurations.

## Conclusion
This project demonstrates a simple but effective approach to job scheduling, using C++ system libraries to simulate real-world cron-like behavior. It covers hourly, daily, and weekly scheduling logic with proper code structure and modular functions.


