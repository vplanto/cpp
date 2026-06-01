#include <iostream>
#include <vector>
#include <string>
#include "Maze.h"
#include "BFS.h"
#include "DFS.h"

void printMaze(const Maze& maze, const std::vector<Position>& path) {
    auto grid = maze.getGrid();
    
    for (const auto& pos : path) {
        if (!(pos == maze.getStart()) && !(pos == maze.getEnd())) {
            grid[pos.row][pos.col] = 2; // 2 = шлях
        }
    }
    
    Position start = maze.getStart();
    Position end = maze.getEnd();
    
    for (int r = 0; r < (int)grid.size(); ++r) {
        for (int c = 0; c < (int)grid[r].size(); ++c) {
            Position pos = {r, c};
            if (pos == start) {
                std::cout << "S ";
            } else if (pos == end) {
                std::cout << "E ";
            } else if (grid[r][c] == 0) {
                std::cout << ". ";
            } else if (grid[r][c] == 1) {
                std::cout << "# ";
            } else if (grid[r][c] == 2) {
                std::cout << "* ";
            }
        }
        std::cout << std::endl;
    }
}

int main() {
    // Приклад 1: Звичайний лабіринт (шлях існує)
    std::vector<std::vector<int>> grid1 = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0},
        {1, 1, 1, 0, 0}
    };
    Maze maze1(grid1, {0, 0}, {3, 4});

    // Приклад 2: Немає шляху (вихід заблоковано стінами)
    std::vector<std::vector<int>> grid2 = {
        {0, 0, 1, 0, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 1},
        {1, 1, 1, 1, 0}
    };
    Maze maze2(grid2, {0, 0}, {3, 4});

    // Приклад 3: Більший лабіринт (декілька шляхів різної довжини)
    std::vector<std::vector<int>> grid3 = {
        {0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 1},
        {0, 0, 0, 1, 0, 0},
        {1, 1, 0, 0, 0, 0}
    };
    Maze maze3(grid3, {0, 0}, {5, 5});

    std::vector<std::pair<std::string, Maze>> test_cases = {
        {"Приклад 1: Стандартний лабіринт", maze1},
        {"Приклад 2: Непрохідний лабіринт", maze2},
        {"Приклад 3: Більший лабіринт", maze3}
    };

    for (const auto& [name, maze] : test_cases) {
        std::cout << "\n========================================\n";
        std::cout << name << "\n";
        std::cout << "========================================\n";

        std::cout << "\n=== BFS ===\n";
        auto bfs_path = BFS(maze);
        if (bfs_path.empty()) {
            std::cout << "Шлях не знайдено!\n";
        } else {
            std::cout << "Довжина шляху: " << bfs_path.size() << "\n";
            printMaze(maze, bfs_path);
        }

        std::cout << "\n=== DFS ===\n";
        auto dfs_path = DFS(maze);
        if (dfs_path.empty()) {
            std::cout << "Шлях не знайдено!\n";
        } else {
            std::cout << "Довжина шляху: " << dfs_path.size() << "\n";
            printMaze(maze, dfs_path);
        }
    }
    return 0;
}
