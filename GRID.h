#pragma once
#include <unordered_set>
#include <utility>
#include <vector>
#include <raylib.h>

struct CellCoord {
    int row;
    int column;

    bool operator==(const CellCoord& other) const {
        return row == other.row && column == other.column;
    }
};

namespace std {
    template<>
    struct hash<CellCoord> {
        size_t operator()(const CellCoord& coord) const {
            return hash<int>()(coord.row) ^ (hash<int>()(coord.column) << 1);
        }
    };
}
class Grid {
private:
    std::unordered_set<CellCoord> aliveCells;
    int cellsize;

public:
    Grid(int cellsize) : cellsize(cellsize) {}

    void Draw(int offsetX, int offsetY) { // with round corners
        for (const auto& cell : aliveCells) {
            int x = (cell.column - offsetX) * cellsize;
            int y = (cell.row - offsetY) * cellsize;
            Rectangle rec = { static_cast<float>(x), static_cast<float>(y), static_cast<float>(cellsize - 1), static_cast<float>(cellsize - 1) };
            DrawRectangleRounded(rec, 0.2f, 4, Color{ 55, 95, 255, 255 });// blue Color{ 50, 65, 255, 255 })
        }
    }


    void SetCell(int row, int column, bool alive) {
        CellCoord coord = { row, column };
        if (alive) {
            aliveCells.insert(coord);
        }
        else {
            aliveCells.erase(coord);
        }
    }

    bool GetCell(int row, int column) const {
        return aliveCells.find({ row, column }) != aliveCells.end();
    }

    int Kneighbors(int row, int column) const {
        int count = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (i == 0 && j == 0) continue;
                if (GetCell(row + i, column + j)) {
                    count++;
                }
            }
        }
        return count;
    }


    const std::unordered_set<CellCoord>& GetAliveCells() const {
        return aliveCells;
    }

    int GetCellSize() const {
        return cellsize;
    }

    int GetAliveCount() const {
        return aliveCells.size();
    }


    void SetCellSize(int newCellSize) {
        cellsize = newCellSize;
    }
};
