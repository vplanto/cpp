#pragma once

#include "Maze.h"
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <algorithm>

inline std::vector<Position> reconstructPath(
    const std::unordered_map<Position, Position, PositionHash>& parent,
    const Position& start,
    const Position& end) {
    
    std::vector<Position> path;
    Position current = end;
    
    while (!(current == start)) {
        path.push_back(current);
        current = parent.at(current);
    }
    
    path.push_back(start);
    std::reverse(path.begin(), path.end());
    return path;
}

inline std::vector<Position> BFS(const Maze& maze) {
    std::queue<Position> q;
    std::unordered_set<Position, PositionHash> visited;
    std::unordered_map<Position, Position, PositionHash> parent; // Для відновлення шляху
    
    Position start = maze.getStart();
    Position end = maze.getEnd();
    
    q.push(start);
    visited.insert(start);
    
    // Напрямки руху: вгору, вниз, ліворуч, праворуч
    std::vector<Position> directions = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
    
    while (!q.empty()) {
        Position current = q.front();
        q.pop();
        
        if (current == end) {
            // Знайшли! Відновлюємо шлях
            return reconstructPath(parent, start, end);
        }
        
        // Перевіряємо всіх сусідів
        for (const auto& dir : directions) {
            Position neighbor = {current.row + dir.row, current.col + dir.col};
            
            if (maze.isValid(neighbor) && visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent[neighbor] = current;
                q.push(neighbor);
            }
        }
    }
    
    return {}; // Шлях не знайдено
}
