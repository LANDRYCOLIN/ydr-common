#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <vector>

class Methane {
private:
    int hydrogenCount;
    int carbonCount;
    int hydrogenRelease;
    int carbonRelease;
    std::mutex mtx;
    std::condition_variable cv;

public:
    Methane() : hydrogenCount(0), carbonCount(0), hydrogenRelease(0), carbonRelease(0) {}

    void hydrogen(std::function<void()> releaseHydrogen) {
        std::unique_lock<std::mutex> lock(mtx);
        hydrogenCount++;

        if (hydrogenCount >= 4 && carbonCount >= 1) {
            // 有足够的氢和碳，可以生成甲烷分子
            hydrogenRelease = 4;
            carbonRelease = 1;
            hydrogenCount -= 4;
            carbonCount -= 1;
            cv.notify_all();
        }
        else {
            // 等待直到可以生成甲烷分子
            cv.wait(lock, [this]() { return hydrogenRelease > 0; });
        }

        // 释放氢原子
        hydrogenRelease--;
        releaseHydrogen();

        if (hydrogenRelease == 0 && carbonRelease == 0) {
            // 本组所有线程已释放，通知等待的线程
            cv.notify_all();
        }
    }

    void carbon(std::function<void()> releaseCarbon) {
        std::unique_lock<std::mutex> lock(mtx);
        carbonCount++;

        if (hydrogenCount >= 4 && carbonCount >= 1) {
            // 有足够的氢和碳，可以生成甲烷分子
            hydrogenRelease = 4;
            carbonRelease = 1;
            hydrogenCount -= 4;
            carbonCount -= 1;
            cv.notify_all();
        }
        else {
            // 等待直到可以生成甲烷分子
            cv.wait(lock, [this]() { return carbonRelease > 0; });
        }

        // 释放碳原子
        carbonRelease--;
        releaseCarbon();

        if (hydrogenRelease == 0 && carbonRelease == 0) {
            // 本组所有线程已释放，通知等待的线程
            cv.notify_all();
        }
    }
};

void releaseHydrogen() {
    std::cout << "H";
}

void releaseCarbon() {
    std::cout << "C";
}

int main() {
    Methane methane;
    std::vector<std::thread> threads;

    std::string x;
    std::cin >> x;

    std::string input = x;
    for (char c : input) {
        if (c == 'H') {
            threads.emplace_back(&Methane::hydrogen, &methane, releaseHydrogen);
        }
        else if (c == 'C') {
            threads.emplace_back(&Methane::carbon, &methane, releaseCarbon);
        }
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
