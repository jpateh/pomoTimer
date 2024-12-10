#include "pomodoro_timer.h"
#include <iostream>
#include <cassert>

void testTimerFunctionality() {
    Timer timer(1); // 1 minute timer
    assert(timer.getTimeRemaining() == 60);

    timer.start();
    assert(timer.getTimeRemaining() == 0);

    timer.reset();
    assert(timer.getTimeRemaining() == 60);
    std::cout << "Timer tests passed.\n";
}

void testPomodoroTimerFunctionality() {
    PomodoroTimer timer(25, 5);
    assert(timer.getTimeRemaining() == 25 * 60);

    timer.startWorkSession("test_user");
    auto log = timer.getSessionLog();
    assert(!log.empty());
    assert(log[0].first < log[0].second);

    timer.startBreakSession();
    assert(timer.getTimeRemaining() == 5 * 60);
    std::cout << "Pomodoro Timer tests passed.\n";
}

int main() {
    testTimerFunctionality();
    testPomodoroTimerFunctionality();
    return 0;
}
