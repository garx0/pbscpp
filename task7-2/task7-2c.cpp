#include <iostream>
#include <map>
#include <chrono>

constexpr uint64_t N_ITER = 5000000;
constexpr int map_size = 65536-1;

int main() {
    std::map<int, int> m;
    auto inserted = m.insert({0, 1}).first;
    // заполняем дерево до полного двоичного дерева
    for (int i = 1; i < map_size; i++) {
        m.insert({i, 1});
    }

    // замер без hint
    auto start = std::chrono::system_clock::now();
    for(int iter = 0; iter < N_ITER; iter++) {
        // вставляем мин. элемент который уже там есть
        m.insert({0, 1});
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    // 2.0s without opt flag
    // 0.1s with -O3
    std::cout << "w/o hint: " << elapsed_seconds.count() << "s\n";

    // замер с hint
    start = std::chrono::system_clock::now();
    for(uint64_t iter = 0; iter < N_ITER; iter++) {
        // вставляем мин. элемент который уже там есть
        m.insert(inserted, {0, 1});
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
    // 0.062s without opt flag
    // 0.014s with -03
    std::cout << "w/ hint: " << elapsed_seconds.count() << "s\n";
}