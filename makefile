CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2


SRC = pomodoro_timer.cpp main.cpp
TEST_SRC = test_pomodoro_timer.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = pomodoro_timer
TEST_EXEC = test_pomodoro_timer

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(OBJ) -o $(EXEC) $(LDFLAGS)

test: $(TEST_EXEC)
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_SRC) pomodoro_timer.o
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC) $(TEST_EXEC)
