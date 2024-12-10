#include "pomodoro_timer.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Timer::Timer(int workDuration, int breakDuration)
    : workDuration(workDuration), breakDuration(breakDuration), timeRemaining(workDuration * 60), status("stopped") {}

void Timer::start(const std::string& sessionType) {
    status = sessionType == "work" ? "working" : "on break";
    timeRemaining = (sessionType == "work" ? workDuration : breakDuration) * 60;
}

void Timer::pause() {
    status = "paused";
}

void Timer::reset() {
    timeRemaining = workDuration * 60;
    status = "stopped";
}

std::string Timer::getStatus() const {
    std::ostringstream statusInfo;
    statusInfo << "Status: " << status << ", Time Remaining: " << timeRemaining / 60 << " mins";
    return statusInfo.str();
}

void Timer::setDurations(int work, int breakTime) {
    workDuration = work;
    breakDuration = breakTime;
}

int Timer::getWorkDuration() const {
    return workDuration;
}

int Timer::getBreakDuration() const {
    return breakDuration;
}

void SessionLog::logSession(const std::string& sessionType, int duration) {
    std::ostringstream logEntry;
    std::time_t now = std::time(nullptr);
    logEntry << sessionType << " session: " << duration << " mins at " << std::put_time(std::localtime(&now), "%F %T");
    sessionHistory.push_back(logEntry.str());
}

std::vector<std::string> SessionLog::getSessionHistory() const {
    return sessionHistory;
}
