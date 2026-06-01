#pragma once

#include "Maze.h"
#include <vector>
#include <unordered_set>

inline bool DFSRecursive(const Maze& maze, 
                  Position current, 
                  const Position& end,
                  std::unordered_set<Position, PositionHash>& visited,
                  std::vector<Position>& path) {
    
    if (current == end) {
        path.push_back(current);
        return true; // Знайшли!
    }
    
    visited.insert(current);
    path.push_back(current);
    
    std::vector<Position> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    
    for (const auto& dir : directions) {
        Position neighbor = {current.row + dir.row, current.col + dir.col};
        
        if (maze.isValid(neighbor) && visited.find(neighbor) == visited.end()) {
            if (DFSRecursive(maze, neighbor, end, visited, path)) {
                return true; // Шлях знайдено
            }
        }
    }
    
    // Backtracking: цей шлях не працює
    path.pop_back();
    return false;
}

inline std::vector<Position> DFS(const Maze& maze) {
    std::unordered_set<Position, PositionHash> visited;
    std::vector<Position> path;
    
    DFSRecursive(maze, maze.getStart(), maze.getEnd(), visited, path);
    return path;
}
