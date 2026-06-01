#pragma once

#include <vector>
#include <string>
#include <functional>

struct Position {
    int row, col;
    
    bool operator==(const Position& other) const {
        return row == other.row && col == other.col;
    }
};

// Хеш-функція для Position (щоб використовувати в unordered_set та unordered_map)
struct PositionHash {
    size_t operator()(const Position& p) const {
        return std::hash<int>()(p.row) ^ (std::hash<int>()(p.col) << 1);
    }
};

class Maze {
private:
    std::vector<std::vector<int>> grid;
    Position start, end;
    int rows, cols;

public:
    Maze(const std::vector<std::vector<int>>& maze_grid, 
         Position s, Position e) 
        : grid(maze_grid), start(s), end(e) {
        rows = grid.size();
        cols = grid[0].size();
    }
    
    bool isValid(const Position& pos) const {
        return pos.row >= 0 && pos.row < rows &&
               pos.col >= 0 && pos.col < cols &&
               grid[pos.row][pos.col] == 0;
    }
    
    Position getStart() const { return start; }
    Position getEnd() const { return end; }
    std::vector<std::vector<int>> getGrid() const { return grid; }
};
