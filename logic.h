#include "GRID.h"
#include "bernoulli.h"

class LOGIC
{
private:
    Grid grid; // main
    Grid tmp_grid; //tmp

    int offsetX;
    int offsetY;
    bool dragging;
    Vector2 lastMousePosition;
    bool isEditingPhase;

public:
    LOGIC(int width, int height, int cellsize) : grid(cellsize), tmp_grid(cellsize), offsetX(0), offsetY(0), dragging(false), isEditingPhase(true) {

        
        GridSetCell(1, 3, true);
        GridSetCell(1, 4, true);
        GridSetCell(1, 5, true);
        GridSetCell(2, 5, true);
        GridSetCell(3, 5, true);


        GridSetCell(2, 2, true);
        GridSetCell(4, 4, true);


        GridSetCell(3, 1, true);
        GridSetCell(4, 1, true);
        GridSetCell(5, 1, true);
        GridSetCell(5, 2, true);
        GridSetCell(5, 3, true);
        
        




        /*
        * // Glider Gun
        GridSetCell(5, 1, true);
        GridSetCell(5, 2, true);
        GridSetCell(6, 1, true);
        GridSetCell(6, 2, true);

        GridSetCell(5, 11, true);
        GridSetCell(6, 11, true);
        GridSetCell(7, 11, true);
        GridSetCell(4, 12, true);
        GridSetCell(8, 12, true);
        GridSetCell(3, 13, true);
        GridSetCell(9, 13, true);
        GridSetCell(3, 14, true);
        GridSetCell(9, 14, true);
        GridSetCell(6, 15, true);
        GridSetCell(4, 16, true);
        GridSetCell(8, 16, true);
        GridSetCell(5, 17, true);
        GridSetCell(6, 17, true);
        GridSetCell(7, 17, true);
        GridSetCell(6, 18, true);

        GridSetCell(3, 21, true);
        GridSetCell(4, 21, true);
        GridSetCell(5, 21, true);
        GridSetCell(3, 22, true);
        GridSetCell(4, 22, true);
        GridSetCell(5, 22, true);
        GridSetCell(2, 23, true);
        GridSetCell(6, 23, true);
        GridSetCell(1, 25, true);
        GridSetCell(2, 25, true);
        GridSetCell(6, 25, true);
        GridSetCell(7, 25, true);

        GridSetCell(3, 35, true);
        GridSetCell(4, 35, true);
        GridSetCell(3, 36, true);
        GridSetCell(4, 36, true);
        */
        
        
        
    }


    void GridDraw() { grid.Draw(offsetX, offsetY); }
    void GridSetCell(const int& row, const int& column, bool alive) { grid.SetCell(row, column, alive); }

    void Update(bool charts = false) {
        static CellChangeTracker tracker;
        static int stepCounter = 0;
        static bool isSimulating = false;

        if (IsKeyPressed(KEY_ENTER)) {
            isSimulating = !isSimulating;
        }

        if (!isSimulating) return;

        tmp_grid = grid;
        std::unordered_set<CellCoord> cellsToCheck = grid.GetAliveCells();


        for (const auto& cell : grid.GetAliveCells()) {
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    cellsToCheck.insert({ cell.row + i, cell.column + j });
                }
            }
        }


        for (const auto& cell : cellsToCheck) {
            int nNeighbors = grid.Kneighbors(cell.row, cell.column);
            bool currentlyAlive = grid.GetCell(cell.row, cell.column);

            if (currentlyAlive) {
                if (nNeighbors < 2 || nNeighbors > 3) tmp_grid.SetCell(cell.row, cell.column, false);
            }
            else {
                if (nNeighbors == 3 || nNeighbors == 6) tmp_grid.SetCell(cell.row, cell.column, true);
            }
        }

        
        grid = tmp_grid;
        if (charts) {

        
            tracker.TrackChanges(grid, tmp_grid);
            if (++stepCounter % 10 == 0) {
                tracker.plot();
            }
        }
    }





    void StartSimulation() {
        isEditingPhase = false;
    }
    void BreakSimulation() {
        isEditingPhase = true;
    }


    void MoveView(int dx, int dy) {
        offsetX += dx;
        offsetY += dy;
    }

    void HandleMouseInput() {
        if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            Vector2 mousePosition = GetMousePosition();
            int cellRow = offsetY + static_cast<int>(mousePosition.y / grid.GetCellSize());
            int cellColumn = offsetX + static_cast<int>(mousePosition.x / grid.GetCellSize());
            grid.SetCell(cellRow, cellColumn, true);
        }

        if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
            dragging = true;
            lastMousePosition = GetMousePosition();
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
            dragging = false;
        }
        if (dragging) {
            Vector2 currentMousePosition = GetMousePosition();
            Vector2 delta = { currentMousePosition.x - lastMousePosition.x, currentMousePosition.y - lastMousePosition.y };
            lastMousePosition = currentMousePosition;

            offsetX -= static_cast<int>(delta.x / grid.GetCellSize());
            offsetY -= static_cast<int>(delta.y / grid.GetCellSize());
        }

        double wheelMove = GetMouseWheelMove();
        if (wheelMove != 0) { // zoom where the mouse is 
            int oldCellSize = grid.GetCellSize();
            int newCellSize = oldCellSize + static_cast<int>(wheelMove);
            if (newCellSize > 2) {
                Vector2 mousePos = GetMousePosition();

                double worldX = offsetX + mousePos.x / oldCellSize;
                double worldY = offsetY + mousePos.y / oldCellSize;

                grid.SetCellSize(newCellSize);
                tmp_grid.SetCellSize(newCellSize);

                offsetX = worldX - mousePos.x / newCellSize;
                offsetY = worldY - mousePos.y / newCellSize;
            }
        }
    }
};
