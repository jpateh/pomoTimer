#include "pomodoro_timer.h"
#include <crow.h>
#include <sstream>

Timer timer(25, 5);
SessionLog sessionLog;

void saveState() {
    std::ofstream file("state.txt");
    if (file.is_open()) {
        file << timer.getWorkDuration() << " " << timer.getBreakDuration() << "\n";
        for (const auto& log : sessionLog.getSessionHistory()) {
            file << log << "\n";
        }
    }
}

void loadState() {
    std::ifstream file("state.txt");
    if (file.is_open()) {
        int work, breakTime;
        file >> work >> breakTime;
        timer.setDurations(work, breakTime);

        std::string logEntry;
        while (std::getline(file, logEntry)) {
            if (!logEntry.empty()) {
                sessionLog.getSessionHistory().push_back(logEntry);
            }
        }
    }
}

int main() {
    crow::SimpleApp app;

    CROW_ROUTE(app, "/api/timers").methods(crow::HTTPMethod::POST)([](const crow::request& req) {
        std::istringstream iss(req.body);
        std::string sessionType;
        int duration;
        iss >> sessionType >> duration;

        timer.start(sessionType);
        sessionLog.logSession(sessionType, duration);

        return crow::response(201, "Timer started: " + sessionType);
    });

    CROW_ROUTE(app, "/api/timers").methods(crow::HTTPMethod::GET)([]() {
        return crow::response(200, timer.getStatus());
    });

    CROW_ROUTE(app, "/api/timers").methods(crow::HTTPMethod::PUT)([](const crow::request& req) {
        std::istringstream iss(req.body);
        int workDuration, breakDuration;
        iss >> workDuration >> breakDuration;

        timer.setDurations(workDuration, breakDuration);
        return crow::response(200, "Timer durations updated.");
    });

    CROW_ROUTE(app, "/api/timers").methods(crow::HTTPMethod::DELETE)([]() {
        timer.reset();
        return crow::response(204);
    });

    CROW_ROUTE(app, "/api/sessions").methods(crow::HTTPMethod::GET)([]() {
        std::ostringstream os;
        for (const auto& log : sessionLog.getSessionHistory()) {
            os << log << "\n";
        }
        return crow::response(200, os.str());
    });

    app.port(8080).multithreaded().run();
    return 0;
}
