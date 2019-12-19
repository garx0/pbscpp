#include <iostream>
#include <map>
#include <chrono>

constexpr uint64_t N_ITER = 5000000;
constexpr int map_size = 65536-1;

// замеры см в комментах к коду
int main() {
    std::map<int, int> m;
    decltype(m.insert({1,1}).first) inserted;
    // заполняем дерево до полного двоичного дерева
    for (int i = 0; i < map_size; i++) {
        inserted = m.insert({i, 1}).first;
    }

    // замер без hint
    auto start = std::chrono::system_clock::now();
    for(int iter = 0; iter < N_ITER; iter++) {
        // вставляем макс. элемент который уже там есть
        m.insert({map_size - 1, 1});
    }
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;

    // -------- TIME WITHOUT HINT --------
    // 3.6s without opt flag
    // 0.5s with -O3
    std::cout << "w/o hint: " << elapsed_seconds.count() << "s\n";

    // замер с hint
    start = std::chrono::system_clock::now();
    for(uint64_t iter = 0; iter < N_ITER; iter++) {
        // вставляем макс. элемент который уже там есть
        m.insert(inserted, {map_size - 1, 1});
    }
    end = std::chrono::system_clock::now();
    elapsed_seconds = end-start;

    // -------- TIME WITH HINT --------
    // 0.4s without opt flag
    // 0.02s with -03
    std::cout << "w/ hint: " << elapsed_seconds.count() << "s\n";
}