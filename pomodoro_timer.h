#ifndef POMODORO_TIMER_H
#define POMODORO_TIMER_H

#include <string>
#include <vector>
#include <ctime>

class Timer {
public:
    Timer(int workDuration, int breakDuration);
    void start(const std::string& sessionType);
    void pause();
    void reset();
    std::string getStatus() const;
    void setDurations(int work, int breakTime);
    int getWorkDuration() const;
    int getBreakDuration() const;

private:
    int workDuration;
    int breakDuration;
    int timeRemaining;
    std::string status;
};

class SessionLog {
public:
    void logSession(const std::string& sessionType, int duration);
    std::vector<std::string> getSessionHistory() const;

private:
    std::vector<std::string> sessionHistory;
};

#endif
