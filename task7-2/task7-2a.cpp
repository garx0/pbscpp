#include <iostream>
#include <map>
#include <chrono>

constexpr uint64_t N_ITER = 200;
constexpr int map_size = 16384-1;

int main() {
    // замер с hint
    auto start = std::chrono::system_clock::now();
    for(int iter = 0; iter < N_ITER; iter++) {
        std::map<int, int> m;
        // добавляем элементы в порядке возрастания ключа
        for (int i = 1; i < map_size; i++) {
            m.insert({i, 1});
        }
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
    // 2.5s without opt flag
    // 0.3s with -O3
    std::cout << "w/o hint: " << elapsed_seconds.count() << "s\n";

    // замер без hint
    start = std::chrono::system_clock::now();
    for(uint64_t iter = 0; iter < N_ITER; iter++) {
        std::map<int, int> m;
        // добавляем элементы в порядке возрастания ключа
        auto inserted = m.insert({0, 1}).first;
        for (int i = 1; i < map_size; i++) {
            inserted = m.insert(inserted, {i, 1});
        }
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;
    // 0.8s without opt flag
    // 0.1s with -03
    std::cout << "w/ hint: " << elapsed_seconds.count() << "s\n";
}