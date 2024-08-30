/*lab01.cpp by Arina Vasileva*/

/*Assume that for the actions performed by the game (driving the AI, updating the game
world, etc.) there is a common superclass Game_Task defined. The class defines a pure
virtual function perform() that performs the action in question:
virtual void Game_Task::perform() = 0;
All actions are independent of each other (do not use the same data, etc.).
The game maintains a vector of actions. The actions are executed sequentially in a loop:
std::vector<Game_Task*> tasks;
...
int number_of_tasks = tasks.size();
for (int i = 0; i < number_of_tasks; i++)
{
 task[i]->perform();
}
// Continue only after all tasks are complete!*/

/*Outline how the loop above could be parallelized using
a) std::thread class (e.g.create two threads that pass through the operation vector in
half)
b) asynchronous function calls(no need to limit the number of calls)
*/

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>

//defining a common superclass Game_Task. The class defines a pure virtual function perform()

class Game_Task {

public:
	virtual void perform() = 0;
    virtual ~Game_Task() {} // a virtual destructor for correct object removal

};


// An example of a subclass that performs some kind of "long-running" task

class Task1 : public Game_Task {

public:

    void perform() override {

        std::cout << "Task1 is running\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulating a delay

    }

};


class Task2 : public Game_Task {

public:

    void perform() override {

        std::cout << "Task2 is running\n";

        std::this_thread::sleep_for(std::chrono::milliseconds(500)); // Simulating a delay

    }

};

// Parallelization using std::thread
void run_with_threads(std::vector<Game_Task*>& tasks) {
    std::thread t1([&tasks]() { tasks[0]->perform(); });
    std::thread t2([&tasks]() { tasks[1]->perform(); });
    t1.join();
    t2.join();
}

// Parallelization using std::async
void run_with_async(std::vector<Game_Task*>& tasks) {
    auto f1 = std::async(std::launch::async, [&tasks]() { tasks[0]->perform(); });
    auto f2 = std::async(std::launch::async, [&tasks]() { tasks[1]->perform(); });
    f1.get();
    f2.get();
}

int main() {
    std::vector<Game_Task*> tasks = { new Task1(), new Task2() };

    // Execution using std::thread
    auto start = std::chrono::high_resolution_clock::now();
    run_with_threads(tasks);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Time with threads: " << std::chrono::duration<double>(end - start).count() << " seconds\n";

    // Execution using std::async
    start = std::chrono::high_resolution_clock::now();
    run_with_async(tasks);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Time with async: " << std::chrono::duration<double>(end - start).count() << " seconds\n";

    for (auto task : tasks) delete task; // Freeing up memory

    return 0;
}




